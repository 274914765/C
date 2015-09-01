#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <errno.h>
#include "pthread.h"
#include <openssl/rsa.h>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#ifndef _WIN32
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <unistd.h>
#else
    #include <winsock2.h>
    #include <windows.h>
#endif

#define CERTF "certs/ec_servercert.pem"
#define KEYF "certs/ec_serverkey.key"
#define CAFILE "demoCA/cacert.pem"
#define CHK_NULL(x)  { if((x)==NULL) { printf("null\n"); } }
#define CHK_ERR(err,s) { if((err)==-1) { printf(" -1 \n"); } }
#define CHK_SSL(err) { if((err)==-1) { printf(" -1 \n");} }

pthread_mutex_t mlock=PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t *lock_cs;
static long *lock_count;

int verify_callback_server(int ok, X509_STORE_CTX *ctx)
{
    printf("verify_callback_server \n");
    return ok;
}

int SSL_CTX_use_PrivateKey_file_pass(SSL_CTX *ctx,char *filename,char *pass)
{
    EVP_PKEY *pkey=NULL;
    BIO *key=NULL;
    key=BIO_new(BIO_s_file());
    BIO_read_filename(key,filename);
    pkey=PEM_read_bio_PrivateKey(key,NULL,NULL,pass);
    if(pkey==NULL)
    {
        printf("PEM_read_bio_PrivateKey err");
        return -1;

    }
    if(SSL_CTX_use_PrivateKey(ctx,pkey) <= 0)
    {
        printf("SSL_CTX_use_PrivateKey err\n");
        return -1;
    }
    BIO_free(key);
    return 1;
}

static int s_server_verify=SSL_VERIFY_NONE;

void * thread_main(void *arg)
{
    int s,AcceptSocket;

#ifdef _WIN32

    WORD wVersionRequested;
    WSADATA wsaData;
#endif

    struct sockaddr_in service;
    int err;
    size_t client_len;
    SSL_CTX *ctx;
    SSL *ssl;
    X509 *client_cert;
    char *str;
    char buf[1024];
    BIO *bio_s_out = NULL;

    if (bio_s_out == NULL)
        bio_s_out = BIO_new_fp (stdout, BIO_NOCLOSE);

    ssl=(SSL*)arg;

    //ȡ��socket
    s=SSL_get_fd(ssl);

    //����SSL����
    err = SSL_accept(ssl);
    if(err<0)
    {
        printf("ssl accerr\n");
        return ;
    }
    printf("SSL connection using %s\n", SSL_get_cipher(ssl));

    //PEM_write_bio_SSL_SESSION (bio_s_out, SSL_get_session (ssl));
    //SSL_SESSION_print (bio_s_out, SSL_get_session (ssl));

    //����֤��
    client_cert = SSL_get_peer_certificate(ssl);
    if(client_cert != NULL)
    {
        printf("Client certificate:\n");
        //��ÿͻ���֤��subject��ת����ַ���,�Ա���д�ӡ
        str = X509_NAME_oneline(X509_get_subject_name(client_cert), 0, 0);
        CHK_NULL(str);
        printf("\t subject: %s\n", str);
        OPENSSL_free(str);

        //��ÿͻ���֤��issuer��ת����ַ���,�Ա���д�ӡ
        str = X509_NAME_oneline(X509_get_issuer_name(client_cert), 0, 0);
        CHK_NULL(str);
        printf("\t issuer: %s\n", str);
        OPENSSL_free(str);
        X509_free(client_cert);
    }
    else
        printf("Client does not have certificate.\n");

    //���а�ȫ�Ự
    memset(buf,0,1024);
    err = SSL_read(ssl, buf, sizeof(buf) - 1);
    if(err<0)
    {
        printf("ssl read err\n");
        close(s);
        return;
    }
    printf("get : %s\n",buf);
#if 0
    buf[err] = '\0';
    err = SSL_write(ssl, "I hear you.", strlen("I hear you."));
#endif
    if(ssl != NULL)
        SSL_free(ssl);
    if (bio_s_out != NULL)
    {
        BIO_free (bio_s_out);
        bio_s_out = NULL;
    }
    close(s);
}

//CHK_SSL(err);

pthread_t pthreads_thread_id(void)
{
    pthread_t ret;
    ret=pthread_self();
    return(ret);
}


void pthreads_locking_callback(int mode, int type, char *file, int line)
{
    if(mode & CRYPTO_LOCK)
    {
        pthread_mutex_lock(&(lock_cs[type]));
        lock_count[type]++;
    }
    else
    {
        pthread_mutex_unlock(&(lock_cs[type]));
    }

}


int main()
{
    int err;
    int i;
    int s,AcceptSocket;
#ifdef _WIN32
    WORD wVersionRequested;
    WSADATA wsaData;
#endif
    struct sockaddr_in service;
    pthread_t pid;
    size_t     client_len;
    SSL_CTX     *ctx;
    SSL *ssl;
    X509 *client_cert;
    char *str;
    char buf[1024];
    SSL_METHOD *meth;

    //����EVP cipher/digest�㷨
    SSLeay_add_ssl_algorithms();

    //����crypto/ssl������ʾ
    SSL_load_error_strings();

    //ָ��Э��汾��Ϊ����������TLSv1 SSL_METHOD�ṹ
    meth = SSLv3_server_method();

    //�����µ�SSL������
    ctx = SSL_CTX_new(meth);
    if(!ctx)
    {
        ERR_print_errors_fp(stderr);
        exit(2);
    }

    //���ؿ�����֤���: ΪSSL_CTX�����ṩһ��Ĭ�ϵ�����֤��
    if((!SSL_CTX_load_verify_locations(ctx,CAFILE,NULL)) ||(!SSL_CTX_set_default_verify_paths(ctx)))
    {
        printf("error load verify locations.\n");
        exit(1);
    }

    //���ط�������֤��
    if(SSL_CTX_use_certificate_file(ctx, CERTF, SSL_FILETYPE_PEM) <= 0)
    {
        ERR_print_errors_fp(stderr);
        exit(3);
    }

    //���ط�����˽Կ�ļ�
    if(SSL_CTX_use_PrivateKey_file_pass(ctx, KEYF, "123456") <= 0)
    {
        ERR_print_errors_fp(stderr);
        exit(4);
    }

    //��֤˽Կ��֤���Ƿ�һ��
    if(!SSL_CTX_check_private_key(ctx))
    {
        fprintf(stderr,"Private key does not match the certificate public key\n");
        exit(5);
    }

    s_server_verify=SSL_VERIFY_PEER|SSL_VERIFY_FAIL_IF_NO_PEER_CERT|SSL_VERIFY_CLIENT_ONCE;

    //ָ��֤����֤��ʽ
    SSL_CTX_set_verify(ctx,s_server_verify,verify_callback_server);
    //����Ҫ�ͻ�����֤��ʱ�򣬷�������CAfile����Ŀ�����CA֤�鷢���ͻ��ˡ�
    SSL_CTX_set_client_CA_list(ctx,SSL_load_client_CA_file(CAFILE));

#ifdef _WIN32
    wVersionRequested = MAKEWORD( 2, 2 );
    err = WSAStartup( wVersionRequested, &wsaData );
    if( err != 0 )
    {
        printf("err\n");
        return -1;
    }
#endif

    //���Ƚ�������
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(s<0) return -1;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY; //inet_addr("127.0.0.1");
    service.sin_port = htons(8888);
    if(bind( s,(struct sockaddr *) &service, sizeof(service)) <0 )
    {
        printf("bind() failed.\n");
        close(s);
        return -1;
    }
    if(listen( s, 1 ) < 0 )
        printf("Error listening on socket.\n");
    printf("recv .....\n");

    //openssl�ǲ�֧�ֶ��̵߳ģ���Ҫ�Լ�����������
    //�μ���http://blog.csdn.net/jaylong35/article/details/6988690
    lock_cs=OPENSSL_malloc(CRYPTO_num_locks() * sizeof(pthread_mutex_t));
    lock_count=OPENSSL_malloc(CRYPTO_num_locks() * sizeof(long));
    for(i=0; i<CRYPTO_num_locks(); i++)
    {
        lock_count[i]=0;
        pthread_mutex_init(&(lock_cs[i]),NULL);
    }

    //ͨ�����������þͿ��Խ��HTTPS���߳��������crash������
    CRYPTO_set_id_callback((unsigned long(*)())pthreads_thread_id);
    CRYPTO_set_locking_callback((void(*)())pthreads_locking_callback);
    while(1)
    {
        struct timeval tv;
        fd_set fdset;
        char *str="JDDH-JDECC3-JDCIPH-JDMD";

        tv.tv_sec = 1;
        tv.tv_usec = 0;
        FD_ZERO(&fdset);
        FD_SET(s, &fdset);
        select(s+1, &fdset, NULL, NULL,(struct timeval *)&tv);
        if(FD_ISSET(s, &fdset))
        {
            AcceptSocket=accept(s, NULL,NULL);
            ssl = SSL_new(ctx);

            //�㷨��ϣ��ύһ���Լ��ܹ�֧�ֵļ��ܷ������б�
            //SSL_set_cipher_list(ssl,"ECDH-RSA-AES256-SHA");
            SSL_set_cipher_list(ssl,"RC4-MD5");

            CHK_NULL(ssl);

            //��SSL��socket���й���
            err=SSL_set_fd(ssl, AcceptSocket);
            if(err>0)
            {
                err=pthread_create(&pid,NULL,&thread_main,(void *)ssl);
                pthread_detach(pid);
            }
            else
                continue;
        }
    }

    SSL_CTX_free(ctx);
    return 0;

}
