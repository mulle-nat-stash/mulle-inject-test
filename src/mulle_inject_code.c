//
//  main.m
//  mulle-inject-into-dock
//
//  Created by Nat! on 03.11.13.
//  Copyright (c) 2013 Mulle kybernetiK. All rights reserved.
//
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "mach_inject.h"
#include <string.h>


// just some code to get the mulle_injection_victim started automatically

static int  fork_victim( char *s)
{
   pid_t pid;
   
   if( ! (pid = fork()))
   {
      char *argv[ 2];

      argv[ 0] = strdup( s);
      argv[ 1] = NULL;

      if( execv( argv[ 0], argv) < 0)
      {
         perror("execv error:");
         return( -1);
      }
      perror("umm:");
      abort();
      return( 0); // can't happen can it ?
   }
   return( pid);
}


int main( int argc, char *argv[])
{
   int   pid;
   int   err;
   void  *adr;
   char  *s;
   
   s    = (argc == 2) ? argv[ 1] : NULL;
   pid  = s ? atoi( s) : 0;
   if( ! pid && s)
      pid = fork_victim( s);
   
   if( ! pid)
   {
      fprintf( stderr, "usage: sudo DYLD_FALLBACK_LIBRARY_PATH=`pwd` %s <pid|executable>\n", argv[ 0]);
      return( 1);
   }

   adr = dlsym( RTLD_NEXT, INJECT_ENTRY_SYMBOL);
   if( ! adr)
   {
      fprintf( stderr, "%s not found in current program", INJECT_ENTRY_SYMBOL);
      return( 2);
   }

#if 0 // this used to check, that the dlsym does what it should (paranoia)
   {
      mach_inject_entry  test;
      
      test = adr;
      (*test)( 0, 0, 0, NULL);
   }
#endif
  
#if defined( __i386__) & defined( DEBUG)
   fprintf( stderr, "%s is running 32 bit code\n", argv[ 0]);
#endif
#if defined( __x86_64__) & defined( DEBUG)
   fprintf( stderr, "%s is running 64 bit code\n", argv[ 0]);
#endif
   err = mach_inject( adr, NULL, 0, pid, 0);

   return( err);
}

