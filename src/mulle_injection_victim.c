//
//  main.c
//  mulle-injection-victim
//
//  Created by Nat! on 03.11.13.
//  Copyright (c) 2013 Mulle kybernetiK. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>


int main(int argc, const char * argv[])
{
#if defined( __i386__) & defined( DEBUG)
   fprintf( stderr, "%s is running 32 bit code\n", argv[ 0]);
#endif
#if defined( __x86_64__) & defined( DEBUG)
   fprintf( stderr, "%s is running 64 bit code\n", argv[ 0]);
#endif

   // just idle and wait for something to happen
   for(;;)
   {
      putchar( '.');
      fflush( stdout);
      sleep( 2);
   }
   return( 0);
}

