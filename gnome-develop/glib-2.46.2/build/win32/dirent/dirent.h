/*
 * DIRENT.H (formerly DIRLIB.H)
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is a part of the mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within the package.
 *
 */  
#ifndef _DIRENT_H_
#    define _DIRENT_H_
    
#    include <stdio.h>
#    include <io.h>
    
#    ifndef RC_INVOKED
    
#        ifdef __cplusplus
extern "C"
{
    
#        endif
    
    {
        
         
         
         
     
     
#        ifdef _WIN64
#            define INTPTR __int64
#        else
#            define INTPTR long
#        endif
     
/*
 * This is an internal data structure. Good programmers will not use it
 * except as an argument to one of the functions below.
 * dd_stat field is now int (was short in older versions).
 */ 
    typedef struct 
    {
        
            /* disk transfer area for this dir */ 
        struct _finddata_t dd_dta;
         
            /* dirent struct to return from dir (NOTE: this makes this thread
             * safe as long as only one thread uses a particular DIR struct at
             * a time) */ 
        struct dirent dd_dir;
         
            /* _findnext handle */ 
          INTPTR dd_handle;
         
            /*
             * Status of search:
             *   0 = not started yet (next entry to read is first entry)
             *  -1 = off the end
             *   positive = 0 based index of next entry
             */ 
        int dd_stat;
         
            /* given path for dir with search pattern (struct is extended) */ 
        char dd_name[1];
     
     
     
     
     
     
     
     
/* wide char versions */ 
     
    {
        
         
         
         
     
     
/*
 * This is an internal data structure. Good programmers will not use it
 * except as an argument to one of the functions below.
 */ 
    typedef struct 
    {
        
            /* disk transfer area for this dir */ 
        struct _wfinddata_t dd_dta;
         
            /* dirent struct to return from dir (NOTE: this makes this thread
             * safe as long as only one thread uses a particular DIR struct at
             * a time) */ 
        struct _wdirent dd_dir;
         
            /* _findnext handle */ 
          INTPTR dd_handle;
         
            /*
             * Status of search:
             *   0 = not started yet (next entry to read is first entry)
             *  -1 = off the end
             *   positive = 0 based index of next entry
             */ 
        int dd_stat;
         
            /* given path for dir with search pattern (struct is extended) */ 
          wchar_t dd_name[1];
     
     
     
     
     
     
     
     
#        ifdef    __cplusplus
} 
#        endif
 
#    endif    /* Not RC_INVOKED */
 
#endif    /* Not _DIRENT_H_ */