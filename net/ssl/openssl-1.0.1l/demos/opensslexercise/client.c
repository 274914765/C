#include <openssl/rand.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <errno.h>
#include <curses.h>

#define PORT 443
#define SERVER "127.0.0.1"
#define CACERT "./demoCA/cacert.pem"
#define MYCERTF "./certs/ec_clientcert.pem"
#define MYKEYF "./certs/ec_clientkey.key"
#define MSGLENGTH 1024
int main () 
{
    

    

    
    
    
    

    
        //加载EVP cipher/digest算法
        OpenSSL_add_ssl_algorithms ();
    
        //加载crypto/ssl错误提示
        SSL_load_error_strings ();
    
        //为客户端构造TLSv1 SSL_METHOD结构
        meth = (SSL_METHOD *) TLSv1_client_method ();
    
        //建立新的SSL上下文
        ctx = SSL_CTX_new (meth);
    
        
    
    
        //加载可信任证书库: 为SSL_CTX对象提供一个默认的信任证书
        SSL_CTX_load_verify_locations (ctx, CACERT, NULL);
    
        //加载客户端证书
        if (0 == SSL_CTX_use_certificate_file (ctx, MYCERTF, SSL_FILETYPE_PEM))
        
    {
        
        
    
    
        //加载客户端私钥文件
        if (0 == SSL_CTX_use_PrivateKey_file (ctx, MYKEYF, SSL_FILETYPE_PEM))
        
    {
        
        
    
    
        //验证私钥与证书是否一致
        if (!SSL_CTX_check_private_key (ctx))
        
    {
        
        
    
    
    
        
    
    
        //提交一份自己能够支持的加密方法的列表
        SSL_CTX_set_cipher_list (ctx, "RC4-MD5");
    
        //设置SSL_MODE_AUTO_RETRY标记
        SSL_CTX_set_mode (ctx, SSL_MODE_AUTO_RETRY);
    
        //首先建立连接
        printf ("Begin tcp socket...\n");
    
    
        
    {
        
    
    
    
    
    
    

    
        
    {
        
        
    
    
        //安全连接要求在连接建立后进行握手
        ssl = SSL_new (ctx);
    
        
    
        
    {
        
        
    
    
        //请求SSL连接
    int k = SSL_connect (ssl);

    
        
    {
        
        
        
    
    
        //进行安全会话
        printf ("connect to server\n");
    

    

    

    
    
    
        
    {
        
        
        
        
        
            
        {
            
        
    
    
    
    
    
    
    


