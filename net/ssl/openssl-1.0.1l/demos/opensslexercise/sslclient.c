#include <stdio.h>
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
#include <windows.h>
#endif    /* 
#include "pthread.h"
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#define MAX_T (1)

#define CLIENTCERT "certs/ec_clientcert.pem"
#define CLIENTKEY "certs/ec_clientkey.key"
#define CAFILE "demoCA/cacert.pem"





{
    
    
    



{
    
        
    {
        
        
    
    
    else
        
    {
        
    



{
    
    



{
    
    
    
    
    
    
        
    {
        
        
    
    
        //���ؿͻ���˽Կ
        if (SSL_CTX_use_PrivateKey (ctx, pkey) <= 0)
        
    {
        
        
    
    
    



{
    

    

    
    

    

    
#ifdef _WIN32
        PHOSTENT phe;
    
    
    
#endif    /* 
        
    
    

    

    
    
    
#ifdef _WIN32
        wVersionRequested = MAKEWORD (2, 2);
    
    
        
    {
        
        
    
    
#endif    /* 
        
        //���Ƚ�������
        sock = socket (AF_INET, SOCK_STREAM, 0);
    
    
    
  
    
        
    {
        
        
    
    
        //��ȫ����Ҫ�������ӽ������������
        ssl = SSL_new (ctx);
    
        
    {
        
        
    
    
    
        //����SSL����
        err = SSL_connect (ssl);
    
        
    {
        
        
    
    
    
        //
        server_cert = SSL_get_peer_certificate (ssl);
    
    
        //��÷����֤��subject��ת����ַ���,�Ա���д�ӡ
        str = X509_NAME_oneline (X509_get_subject_name (server_cert), 0, 0);
    
    
    
        //��ÿͻ���֤��issuer��ת����ַ���,�Ա���д�ӡ
        str = X509_NAME_oneline (X509_get_issuer_name (server_cert), 0, 0);
    
    
    
    
        //���а�ȫ�Ự
        err = SSL_write (ssl, "Hello World!", strlen ("Hello World!"));
    
        
    {
        
        
    
    
#if 0
        memset (buf, 0, ONE_BUF_SIZE);
    
    
        
    {
        
        
    
    
    
    
#endif    /* 
        
    
    
    
        /* send SSL/TLS close_notify */ 
}


{
    

    

    

    

    
#ifdef _WIN32
        PHOSTENT phe;
    
    
    
#endif    /* 
        
    
    
    

    

    
    

    
    
        //����EVP cipher/digest�㷨
        SSLeay_add_ssl_algorithms ();
    
        //����crypto/ssl������ʾ
        SSL_load_error_strings ();
    
        //Ϊ�ͻ��˹���TLSv1 SSL_METHOD�ṹ
        meth = SSLv3_client_method ();
    
        //�����µ�SSL������
        ctx = SSL_CTX_new (meth);
    
        
    {
        
        
    
    
        //���ؿͻ���֤��
        if (SSL_CTX_use_certificate_file (ctx, CLIENTCERT, SSL_FILETYPE_PEM) <= 0)
        
    {
        
        
    
    
        
    {
        
        
    
    
        //��֤˽Կ��֤���Ƿ�һ��
        if (!SSL_CTX_check_private_key (ctx))
        
    {
        
        
    
    
        //openssl�ǲ�֧�ֶ��̵߳ģ���Ҫ�Լ�����������
        //�μ���http://blog.csdn.net/jaylong35/article/details/6988690
        lock_cs = OPENSSL_malloc (CRYPTO_num_locks () * sizeof (pthread_mutex_t));
    
    
        
    {
        
        
    
    
        //ͨ�����������þͿ��Խ��HTTPS���߳��������crash������
        CRYPTO_set_id_callback ((unsigned long (*)()) pthreads_thread_id);
    
    
        
    {
        
        
            
        {
            
            
        
    
    
        
    {
        
    
    
    
    


