#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "vertigal/iofuncs.h"

/***
 *A very haphazard implementation of  
 * getLine from the POSIX C library.
 * This function does not do a lot of
 * things that function does, such as
 * acquiring a lock on the file.
 * Is this function vulnerable because
 * of that? Maybe. But it also may have
 * many other, more trivial (read dumb),
 * bugs
 ***/

ssize_t VG_getline(char** restrict lineptr, size_t* restrict n, file_buffer_t* restrict fb, bool* isEOF)
{
    if(lineptr == NULL)
        return -1;
    
    if(n == NULL )
        return -1;

    if(fb == NULL)
        return -1;
    
    ssize_t lnSize = fb->__cursor;

    for(lnSize; ;lnSize++)
    {
        if((fb->buffer[lnSize] == '\n') | (fb->buffer[lnSize] == '\0') )
        {
            if(*lineptr == NULL)
            {
                *lineptr = malloc(lnSize + 1);

                if(*lineptr == NULL)
                    return -1;
                fb->__cursor = lnSize+1;
            }
            
            if(fb->buffer[lnSize] == '\0')
                isEOF = true;

            break;
        }
       
    }   

    lnSize++;
    memcpy(**lineptr, &fb->buffer[fb->__cursor - lnSize ], &lnSize);
    fb->buffer[fb->__cursor] = '\0';

    return lnSize;
}
