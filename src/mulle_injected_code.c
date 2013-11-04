//
//  mulle_injected_code.c
//  mulle-inject-test
//
//  Created by Nat! on 03.11.13.
//  Copyright (c) 2013 Mulle kybernetiK. All rights reserved.
//
#include "mach_inject.h"

#include <mach/mach_init.h>
#include <mach/thread_act.h>
#include <pthread.h>
#include <unistd.h>

//
// this code is in a dylib, because mach_inject will copy the complete image
// containing the entry function. So let's keep it as small as possible.
//
void	INJECT_ENTRY( ptrdiff_t codeOffset, void *paramBlock,
                      size_t paramSize, void* dummy_pthread_data)
{
#if defined (__i386__) || defined(__x86_64__)
   // On intel, per-pthread data is a zone of data that must be allocated.
   // if not, all function trying to access per-pthread data (all mig functions for instance)
   // will crash.
   if( dummy_pthread_data)
   {
      extern void __pthread_set_self(char*);
      __pthread_set_self(dummy_pthread_data);
   }
#endif
   write( 2, "Target says hello\n", 18);

   if( dummy_pthread_data)
      thread_suspend(mach_thread_self());
}


