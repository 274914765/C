//server
#include <stdio.h>
#include <openssl/x509.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <curses.h>

#define MSGLENGTH 1024
#define PORT 443
#define CACERT "./demoCA/cacert.pem"
#define SVRCERTF "./certs/ec_servercert.pem"
#define SVRKEYF "./certs/ec_serverkey.key"
int main () 
{
    

    
    
    
    
        //加载EVP cipher/digest算法
        OpenSSL_add_ssl_algorithms ();
    
        //加载crypto/ssl错误提示
        SSL_load_error_strings ();
    
        //为服务器构造TLSv1 SSL_METHOD结构
        meth = (SSL_METHOD *) TLSv1_server_method ();
    
        //建立新的SSL上下文
        ctx = SSL_CTX_new (meth);
    
        
    
        //设置证书认证回调函数
        SSL_CTX_set_verify (ctx, SSL_VERIFY_PEER, NULL);
    
        //加载可信任证书库: 为SSL_CTX对象提供一个默认的信任证书
        SSL_CTX_load_verify_locations (ctx, CACERT, NULL);
    
        //加载服务器端证书
        if (0 == SSL_CTX_use_certificate_file (ctx, SVRCERTF, SSL_FILETYPE_PEM))
        
    {
        
        
    
    
        //加载服务器私钥文件
        if (0 == SSL_CTX_use_PrivateKey_file (ctx, SVRKEYF, SSL_FILETYPE_PEM))
        
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
        
        
    
    
    

    

    
        
    

    

    
        
    {
        
    
    
    
    
        //安全连接要求在连接建立后进行握手
        ssl = SSL_new (ctx);
    
        
    
        //将SSL与socket进行关联
        if (0 == SSL_set_fd (ssl, ss))
        
    {
        
        
    
    
        //接受SSL连接
    int k = SSL_accept (ssl);

    
        
    {
        
        
        
    
    
    
        //检索证书
        client_cert = SSL_get_peer_certificate (ssl);
    
    
        
    {
        
        
            //获得客户端证书subject并转变成字符型,以便进行打印
        char *str = X509_NAME_oneline (X509_get_subject_name (client_cert), 0, 0);

        
            
        {
            
            
        
        
        
            //获得客户端证书issuer并转变成字符型,以便进行打印
            str = X509_NAME_oneline (X509_get_issuer_name (client_cert), 0, 0);
        
            
        {
            
            
        
        
        
        
        
    
    
    else
        
    {
        
        
    
    
        //进行安全会话
    char buf[MSGLENGTH];

    
    
    
        
    {
        
        
        
        
            
        {
            
        
    
    
    
    
    
    


