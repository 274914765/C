#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <errno.h>
#ifndef _WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#else    /* 
#include <winsock2.h>
#include <windows.h>
#endif    /* 
#include "pthread.h"
#include <openssl/rsa.h>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#define CERTF "certs/ec_servercert.pem"
#define KEYF "certs/ec_serverkey.key"
#define CAFILE "demoCA/cacert.pem"
pthread_mutex_t mlock = PTHREAD_MUTEX_INITIALIZER;






#define CHK_NULL(x)  { if((x)==NULL) { printf("null\n"); } }
#define CHK_ERR(err,s) { if((err)==-1) { printf(" -1 \n"); } }
#define CHK_SSL(err) { if((err)==-1) { printf(" -1 \n");} }
//#define CAFILE "certs/cacert.pem"

{
    
    



{
    
    
    
    
    
    
        
    {
        
        
    
    
        
    {
        
        
    
    
    





{
    

    
#ifdef _WIN32
        
    
    
#endif    /* 
    

    

    
    
    
    
    

    

    
    
        //ȡ��socket
        s = SSL_get_fd (ssl);
    
        //����SSL����
        err = SSL_accept (ssl);
    
        
    {
        
        
    
    
    
        //����֤��
        client_cert = SSL_get_peer_certificate (ssl);
    
        
    {
        
        
            //��ÿͻ���֤��subject��ת����ַ���,�Ա���д�ӡ
            str = X509_NAME_oneline (X509_get_subject_name (client_cert), 0, 0);
        
        
        
        
            //��ÿͻ���֤��issuer��ת����ַ���,�Ա���д�ӡ
            str = X509_NAME_oneline (X509_get_issuer_name (client_cert), 0, 0);
        
        
        
        
    
    
    else
        
    
        //���а�ȫ�Ự
        memset (buf, 0, 1024);
    
    
        
    {
        
        
        
    
    
    
#if 0
        buf[err] = '\0';
    
    
#endif    /* 
        SSL_free (ssl);
    



//CHK_SSL(err);
    
{
    
    
    



{
    
        
    {
        
        
    
    
    else
        
    {
        
    



{
    

    

    

    
#ifdef _WIN32
        WORD wVersionRequested;
    
    
#endif    /* 
    struct sockaddr_in service;

    
    
    
    
    
    

    

    
    
        //����EVP cipher/digest�㷨
        SSLeay_add_ssl_algorithms ();
    
        //����crypto/ssl������ʾ
        SSL_load_error_strings ();
    
        //Ϊ����������TLSv1 SSL_METHOD�ṹ
        meth = SSLv3_server_method ();
    
        //�����µ�SSL������
        ctx = SSL_CTX_new (meth);
    
        
    {
        
        
    
    
        //���ؿ�����֤���: ΪSSL_CTX�����ṩһ��Ĭ�ϵ�����֤��
        if ((!SSL_CTX_load_verify_locations (ctx, CAFILE, NULL)) || (!SSL_CTX_set_default_verify_paths (ctx)))
        
    {
        
        
    
    
        //���ط�������֤��
        if (SSL_CTX_use_certificate_file (ctx, CERTF, SSL_FILETYPE_PEM) <= 0)
        
    {
        
        
    
    
        //���ط�����˽Կ�ļ�
        if (SSL_CTX_use_PrivateKey_file_pass (ctx, KEYF, "123456") <= 0)
        
    {
        
        
    
    
        //��֤˽Կ��֤���Ƿ�һ��
        if (!SSL_CTX_check_private_key (ctx))
        
    {
        
        
    
    
    
    
        //����Ҫ�ͻ�����֤��ʱ�򣬷�������CAfile����Ŀ�����CA֤�鷢���ͻ��ˡ�
        SSL_CTX_set_client_CA_list (ctx, SSL_load_client_CA_file (CAFILE));
    
#ifdef _WIN32
        wVersionRequested = MAKEWORD (2, 2);
    
    
        
    {
        
        
    
    
#endif    /* 
        
        //���Ƚ�������
        s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
        return -1;
    
    
    service.sin_port = htons (8888);
    
        
    {
        
        
        
    
    
        
    
    
        //openssl�ǲ�֧�ֶ��̵߳ģ���Ҫ�Լ�����������
        //�μ���http://blog.csdn.net/jaylong35/article/details/6988690
        lock_cs = OPENSSL_malloc (CRYPTO_num_locks () * sizeof (pthread_mutex_t));
    
    
        
    {
        
        
    
    
        //ͨ�����������þͿ��Խ��HTTPS���߳��������crash������
        CRYPTO_set_id_callback ((unsigned long (*)()) pthreads_thread_id);
    
    
        
    {
        

        
        

        
        
        
        
        
        
            
        {
            
            
            
                //�ύһ���Լ��ܹ�֧�ֵļ��ܷ������б�
                //SSL_set_cipher_list(ssl,"ECDH-RSA-AES256-SHA");
                SSL_set_cipher_list (ssl, "RC4-MD5");
            
            
                //��SSL��socket���й���
                err = SSL_set_fd (ssl, AcceptSocket);
            
                
            {
                
                
            
            
            else
                
        
    
    
    


