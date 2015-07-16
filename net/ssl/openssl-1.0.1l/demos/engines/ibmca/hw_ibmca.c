
/* crypto/engine/hw_ibmca.c */  

/* Written by Geoff Thorpe (geoff@geoffthorpe.net) for the OpenSSL
 * project 2000.
 */ 

/* ====================================================================
 * Copyright (c) 1999 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.OpenSSL.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    licensing@OpenSSL.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.OpenSSL.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).  This product includes software written by Tim
 * Hudson (tjh@cryptsoft.com).
 *
 */ 
    

/* (C) COPYRIGHT International Business Machines Corp. 2001 */ 
    
#include <stdio.h>
#include <openssl/crypto.h>
#include <openssl/dso.h>
#include <openssl/engine.h>
    
#ifndef OPENSSL_NO_HW
#ifndef OPENSSL_NO_HW_IBMCA
    
#ifdef FLAT_INC
#include "ica_openssl_api.h"
#else    /* 
#include "vendor_defns/ica_openssl_api.h"
#endif    /* 
    
#define IBMCA_LIB_NAME "ibmca engine"
#include "hw_ibmca_err.c"





















/* BIGNUM stuff */ 
static int ibmca_mod_exp (BIGNUM * r, const BIGNUM * a, const BIGNUM * p, 


                                const BIGNUM * dmq1, 

#ifndef OPENSSL_NO_RSA  

/* RSA stuff */ 
static int ibmca_rsa_mod_exp (BIGNUM * r0, const BIGNUM * I, RSA * rsa);


#endif    /* 
    

/* This function is aliased to mod_exp (with the mont stuff dropped). */ 
static int ibmca_mod_exp_mont (BIGNUM * r, const BIGNUM * a, const BIGNUM * p, 
                               BN_MONT_CTX * m_ctx);

#ifndef OPENSSL_NO_DSA 

/* DSA stuff */ 
static int ibmca_dsa_mod_exp (DSA * dsa, BIGNUM * rr, BIGNUM * a1, 
                              BIGNUM * p1, BIGNUM * a2, BIGNUM * p2, BIGNUM * m, 

                               const BIGNUM * p, const BIGNUM * m, BN_CTX * ctx, 

#endif    /* 
    
#ifndef OPENSSL_NO_DH 

/* DH stuff */ 

/* This function is alised to mod_exp (with the DH and mont dropped). */ 
static int ibmca_mod_exp_dh (const DH * dh, BIGNUM * r, 
                             BN_CTX * ctx, BN_MONT_CTX * m_ctx);

#endif    /* 
    

/* RAND stuff */ 
static int ibmca_rand_bytes (unsigned char *buf, int num);





/* WJH - check for more commands, like in nuron */ 
    

/* The definitions for control commands specific to this engine */ 
#define IBMCA_CMD_SO_PATH        ENGINE_CMD_BASE
static const ENGINE_CMD_DEFN ibmca_cmd_defns[] = { 
        {IBMCA_CMD_SO_PATH, 
    {0, NULL, NULL, 0} 
};


#ifndef OPENSSL_NO_RSA  

/* Our internal RSA_METHOD that we provide pointers to */ 
static RSA_METHOD ibmca_rsa = 
    { 

};


#endif    /* 
    
#ifndef OPENSSL_NO_DSA

/* Our internal DSA_METHOD that we provide pointers to */ 
static DSA_METHOD ibmca_dsa = 
        NULL, /* dsa_sign_setup */ 
        NULL, /* dsa_do_verify */ 
        ibmca_dsa_mod_exp, /* dsa_mod_exp */ 
        ibmca_mod_exp_dsa, /* bn_mod_exp */ 
        NULL, /* init */ 
        NULL, /* finish */ 
        0, /* flags */ 
        NULL /* app_data */  
};


#endif    /* 
    
#ifndef OPENSSL_NO_DH

/* Our internal DH_METHOD that we provide pointers to */ 
static DH_METHOD ibmca_dh = 
};


#endif    /* 

        /* "IBMCA RAND method", */ 
    NULL, 
};



/* Constants used when creating the ENGINE */ 
static const char *engine_ibmca_id = "ibmca";





/* This internal function is used by ENGINE_ibmca() and possibly by the
 * "dynamic" ENGINE support too */ 
static int bind_helper (ENGINE * e) 
{
    
#ifndef OPENSSL_NO_RSA
    const RSA_METHOD *meth1;

    
#endif    /* 
#ifndef OPENSSL_NO_DSA
    const DSA_METHOD *meth2;

    
#endif    /* 
#ifndef OPENSSL_NO_DH
    const DH_METHOD *meth3;

    
#endif    /* 
        if (!ENGINE_set_id (e, engine_ibmca_id) || 
#ifndef OPENSSL_NO_RSA
            !ENGINE_set_RSA (e, &ibmca_rsa) || 
#endif    /* 
#ifndef OPENSSL_NO_DSA
            !ENGINE_set_DSA (e, &ibmca_dsa) || 
#endif    /* 
#ifndef OPENSSL_NO_DH
            !ENGINE_set_DH (e, &ibmca_dh) || 
#endif    /* 
            !ENGINE_set_RAND (e, &ibmca_rand) || 
            || 
            || 
        
    
#ifndef OPENSSL_NO_RSA
        /* We know that the "PKCS1_SSLeay()" functions hook properly
         * to the ibmca-specific mod_exp and mod_exp_crt so we use
         * those functions. NB: We don't use ENGINE_openssl() or
         * anything "more generic" because something like the RSAref
         * code may not hook properly, and if you own one of these
         * cards then you have the right to do RSA operations on it
         * anyway! */ 
        meth1 = RSA_PKCS1_SSLeay ();
    
    
    
    
    
#endif    /* 
        
#ifndef OPENSSL_NO_DSA
        /* Use the DSA_OpenSSL() method and just hook the mod_exp-ish
         * bits. */ 
        meth2 = DSA_OpenSSL ();
    
    
    
    
#endif    /* 
        
#ifndef OPENSSL_NO_DH
        /* Much the same for Diffie-Hellman */ 
        meth3 = DH_OpenSSL ();
    
    
    
#endif    /* 
        
        /* Ensure the ibmca error handling is set up */ 
        ERR_load_IBMCA_strings ();
    



{
    
    
        
    
        
    {
        
        
    
    



#ifdef ENGINE_DYNAMIC_SUPPORT
static 
#endif    /* 
void ENGINE_load_ibmca (void) 
{
    
        /* Copied from eng_[openssl|dyn].c */ 
        ENGINE * toadd = engine_ibmca ();
    
        return;
    
    
    




/* Destructor (complements the "ENGINE_ibmca()" constructor) */ 
static int ibmca_destroy (ENGINE * e) 
{
    
        /* Unload the ibmca error strings so any error state including our
         * functs or reasons won't lead to a segfault (they simply get displayed
         * without corresponding string data because none will be found). */ 
        ERR_unload_IBMCA_strings ();
    




/* This is a process-global DSO handle used for loading and unloading
 * the Ibmca library. NB: This is only set (or unset) during an
 * init() or finish() call (reference counts permitting) and they're
 * operating with global locks, so this should be thread-safe
 * implicitly. */ 




/* These are the function pointers that are (un)set when the library has
 * successfully (un)loaded. */ 












/* utility function to obtain a context */ 
static int get_context (ICA_ADAPTER_HANDLE * p_handle) 
{
    

    
    
        
    




/* similarly to release one. */ 
static void release_context (ICA_ADAPTER_HANDLE handle) 
{
    


/* (de)initialisation functions. */ 
static int ibmca_init (ENGINE * e) 
{
    

    

    

    

    

    
        
    {
        
        
    
    
        /* Attempt to load libatasi.so/atasi.dll/whatever. Needs to be
         * changed unfortunately because the Ibmca drivers don't have
         * standard library names that can be platform-translated well. */ 
        /* TODO: Work out how to actually map to the names the Ibmca
         * drivers really use - for now a symbollic link needs to be
         * created on the host system from libatasi.so to atasi.so on
         * unix variants. */ 
        
        /* WJH XXX check name translation */ 
        
                               /* DSO_FLAG_NAME_TRANSLATION */ 0);
    
        
    {
        
        
    
    
          || 
          || 
        
    {
        
        
    
    
        /* Copy the pointers */ 
        
    
    
    
    
    
        
    {
        
        
    
    
  
        
    
    
    
    
    



{
    
        
    {
        
        
    
    
    
        
    {
        
        
    
    
    



{
    

    
        
    {
        
            
                
            {
                
                
            
            
                
            {
                
                
            
            
            
        
            
    
    
    



{
    
        /* I need somewhere to store temporary serialised values for
         * use with the Ibmca API calls. A neat cheat - I'll use
         * BIGNUMs from the BN_CTX but access their arrays directly as
         * byte arrays <grin>. This way I don't have to clean anything
         * up. */ 
        
    
    
    

    

    
    

    
    
        
    {
        
        
    
    
        /* Prepare the params */ 
        BN_CTX_start (ctx);
    
    
    
    
        
    {
        
        
    
    
           || 
        
    {
        
        
    
    
    
        
    {
        
    
    
    
    
    
    
        /* A quirk of the card: the exponent length has to be the same
           as the modulus (key) length */ 
        
    

/* check for modulus length SAB*/ 
        if (outLen > 256)
    {
        
        
    
    

/* check for modulus length SAB*/ 
        
    

/* SAB Check for underflow condition
    the size of the exponent is less than the size of the parameter
    then we have a big problem and will underflow the keyRecord
   buffer.  Bad stuff could happen then
*/ 
        if (outLen < BN_num_bytes (p))
    {
        
        
    
    

/* SAB End check for underflow */ 
        
    
    
    
    
    
    
    
        /* Prepare the argument */ 
        
    
    
    
        /* Perform the operation */ 
        
              p_icaRsaModExpo (handle, inLen, (unsigned char *) argument->d, 
                               (unsigned char *) result->d)) 
        
    {
        
        
        
    
    
        /* Convert the response */ 
        BN_bin2bn ((unsigned char *) result->d, outLen, r);
    
  
    



#ifndef OPENSSL_NO_RSA 
static int ibmca_rsa_mod_exp (BIGNUM * r0, const BIGNUM * I, RSA * rsa) 
{
    
    

    
        
    
        
    {
        
            
        {
            
            
        
        
    
    
    else
        
    {
        
    
  
        
    



#endif    /* 
    

/* Ein kleines chinesisches "Restessen"  */ 
static int ibmca_mod_exp_crt (BIGNUM * r, const BIGNUM * a, const BIGNUM * p, 
                              
{
    
    
    
    

    

    
    

    

    

    

/* SAB New variables */ 
    unsigned int keyRecordSize;

    

    

    

    

    

    
        /* Prepare the params */ 
        
    
    
    
    
        
    {
        
        
    
    
          || 
        
    {
        
        
    
    
    

/* SAB Add check for total size in bytes of the parms does not exceed
   the buffer space we have
   do this first
*/ 
        keyRecordSize = pbytes + qbytes + dmp1bytes + dmq1bytes + iqmpbytes;
    
    {
        
        
    
    
    {
        
        
    
    
    {
        
        
    
    

/* end SAB additions */ 
        
    
    
    
    
        /*
         * p,dp & qInv are 1 QWORD Larger
         */ 
        privKey->pLength = CORRECT_ENDIANNESS (BN_num_bytes (p) + 8);
    
    
    
    
    
    
    
    

/* SAB  probably aittle redundant, but we'll verify that each of the
   components which make up a key record sent ot the card does not exceed
   the space that is allocated for it.  this handles the case where even if
   the total length does not exceed keyrecord zied, if the operands are funny sized
they could cause potential side affects on either the card or the result */ 
        
             (iqmpbytes > pSize) || (qbytes > qSize) || 
    {
        
        
    
    
    
    
    
    
    
    
    
    
    
    

/* SAB first check that we don;t under flow the buffer */ 
        if (pSize < pbytes)
    {
        
        
    
    
        /* pkey += pSize - BN_num_bytes(p); WROING this should be dmp1) */ 
        pkey += pSize - BN_num_bytes (dmp1);
    
    
    
    
    
    
    
    
    
    
    
    
        /* Prepare the argument and response */ 
        
                                                                   because the fields were converted above */
    
    {
        
        
    
    
        /* SAB check for underflow here on the argeument */ 
        if (outLen < BN_num_bytes (a))
    {
        
        
    
    
    
    
    
        /* Perform the operation */ 
        
              p_icaRsaCrt (handle, inLen, (unsigned char *) argument->d, 
                           (unsigned char *) result->d)) != 0)
        
    {
        
        
        
    
    
        /* Convert the response */ 
        
    
  
    



#ifndef OPENSSL_NO_DSA

/* This code was liberated and adapted from the commented-out code in
 * dsa_ossl.c. Because of the unoptimised form of the Ibmca acceleration
 * (it doesn't have a CRT form for RSA), this function means that an
 * Ibmca system running with a DSA server certificate can handshake
 * around 5 or 6 times faster/more than an equivalent system running with
 * RSA. Just check out the "signs" statistics from the RSA and DSA parts
 * of "openssl speed -engine ibmca dsa1024 rsa1024". */ 
static int ibmca_dsa_mod_exp (DSA * dsa, BIGNUM * rr, BIGNUM * a1, 
                              BIGNUM * p1, BIGNUM * a2, BIGNUM * p2, BIGNUM * m, 
                              BN_CTX * ctx, BN_MONT_CTX * in_mont) 
{
    
    

    
    
        /* let rr = a1 ^ p1 mod m */ 
        if (!ibmca_mod_exp (rr, a1, p1, m, ctx))
        goto end;
    
        /* let t = a2 ^ p2 mod m */ 
        if (!ibmca_mod_exp (&t, a2, p2, m, ctx))
        goto end;
    
        /* let rr = rr * t mod m */ 
        if (!BN_mod_mul (rr, rr, &t, m, ctx))
        goto end;
    
  
    



                                 const BIGNUM * p, const BIGNUM * m, BN_CTX * ctx, 
{
    



#endif    /* 
    

/* This function is aliased to mod_exp (with the mont stuff dropped). */ 
static int ibmca_mod_exp_mont (BIGNUM * r, const BIGNUM * a, const BIGNUM * p, 
                               BN_MONT_CTX * m_ctx) 
{
    



#ifndef OPENSSL_NO_DH 

/* This function is aliased to mod_exp (with the dh and mont dropped). */ 
static int ibmca_mod_exp_dh (DH const *dh, BIGNUM * r, 
                             BN_CTX * ctx, BN_MONT_CTX * m_ctx) 
{
    



#endif    /* 
    

/* Random bytes are good */ 
static int ibmca_rand_bytes (unsigned char *buf, int num) 
{
    

    

    
        
    {
        
        
    
    
    
        
    {
        
        
    
    
  



{
    




/* This stuff is needed if this ENGINE is being compiled into a self-contained
 * shared-library. */ 
#ifdef ENGINE_DYNAMIC_SUPPORT
static int bind_fn (ENGINE * e, const char *id) 
{
    
        
    
        
    



#endif    /* ENGINE_DYNAMIC_SUPPORT */
    
#endif    /* !OPENSSL_NO_HW_IBMCA */
#endif    /* !OPENSSL_NO_HW */