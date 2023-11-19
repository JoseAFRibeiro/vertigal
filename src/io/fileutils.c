#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#include <stddef.h>
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

static uint32_t counter = 0;

ssize_t VG_getline(char** restrict lineptr, size_t* restrict n, file_buffer_t* restrict fb, bool* isEOF)
{
    counter++;
    if(counter == 33)
    {
        counter--;
    }
    if(lineptr == NULL)
        return -1;
    
    if(n == NULL )
        return -1;

    if(fb == NULL)
        return -1;
    
    ssize_t lnCursor = 0;
    ssize_t fbCursorStart = fb->__cursor;

    for(lnCursor; ;lnCursor++)
    {
        if((fb->buffer[fbCursorStart + lnCursor] == '\n') || (fb->buffer[fbCursorStart + lnCursor] == '\0') )
        {
            if(*lineptr == NULL)
            {
                *lineptr = malloc(lnCursor + 3);

                if(*lineptr == NULL)
                    return -1;
                fb->__cursor = fbCursorStart + lnCursor + 1;
            }
            
            if(fb->buffer[fbCursorStart + lnCursor] == '\0')
                *isEOF = true;

            break;
        }
       
    }   

    lnCursor++;
    memcpy(*lineptr, &fb->buffer[fbCursorStart], lnCursor);

    #ifdef DEBUG
        #ifdef _win32
        uint32_t size = _msize(*lineptr);
        #endif
    (*lineptr)[lnCursor] = '\0';
    vg_log(*lineptr);
    #endif
    return lnCursor;
}
