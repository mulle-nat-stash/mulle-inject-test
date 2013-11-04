//
//  mulle_injection_victim.c
//  mulle-inject-test
//
//  Created by Nat! on 03.11.13.
//  Copyright (c) 2013 Mulle kybernetiK. All rights reserved.
//
#include <stdio.h>
#include <unistd.h>


int main(int argc, const char * argv[])
{
   // just idle and wait for something to happen
   for(;;)
   {
      putchar( '.');
      fflush( stdout);
      sleep( 2);
   }
   return( 0);
}

