/*
 * FreeRTOS STM32 Reference Integration
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#ifndef LOGGING_H
#define LOGGING_H

/* Standard Include. */
#include <stdio.h>

/* Include header for logging level macros. */
#include "logging_levels.h"

/* Default logging config */
#if ( !defined(LOGGING_OUTPUT_UART) && !defined(LOGGING_OUTPUT_ITM) && !defined(LOGGING_OUTPUT_NONE) )
#define LOGGING_OUTPUT_UART
#endif

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_INFO
#endif


/* Function declarations */
void vLoggingPrintf( const char * const     pcLogLevel,
                     const char * const     pcFileName,
                     const char * const     pcFunctionName,
                     const unsigned long    ulLineNumber,
                     const char * const     pcFormat,
                     ... );
void vLoggingInit( void );
void vLoggingDeInit( void );
int _write( int fd, const void * buffer, unsigned int count );

/* Generic logging macros */

#define SdkLog( level, ... )        do { vLoggingPrintf( level, __FILE__, __func__, __LINE__, __VA_ARGS__); } while( 0 )

#define LogAssert( ... )            SdkLog( "ASSERT", __VA_ARGS__ )

#if !defined( LOG_LEVEL ) ||       \
    ( ( LOG_LEVEL != LOG_NONE ) && \
    ( LOG_LEVEL != LOG_ERROR ) &&  \
    ( LOG_LEVEL != LOG_WARN ) &&   \
    ( LOG_LEVEL != LOG_INFO ) &&   \
    ( LOG_LEVEL != LOG_DEBUG ) )

    #error "Please define LOG_LEVEL as either LOG_NONE, LOG_ERROR, LOG_WARN, LOG_INFO, or LOG_DEBUG."
#else

    #if ( LOG_LEVEL >= LOG_ERROR )
        #define LogError( ... )     SdkLog( "ERROR", __VA_ARGS__ )
    #else
        #define LogError( ... )
    #endif

    #if ( LOG_LEVEL >= LOG_WARN )
        #define LogWarn( ... )      SdkLog( "WARN ", __VA_ARGS__ )
    #else
        #define LogWarn( ... )
    #endif

    #if ( LOG_LEVEL >= LOG_INFO )
        #define LogInfo( ... )      SdkLog( "INFO ", __VA_ARGS__ )
    #else
        #define LogInfo( ... )
    #endif

    #if ( LOG_LEVEL >= LOG_DEBUG )
        #define LogDebug( ... )     SdkLog( "DEBUG", __VA_ARGS__ )
    #else
        #define LogDebug( ... )
    #endif

#endif /* if !defined( LOG_LEVEL ) || ( ( LOG_LEVEL != LOG_NONE ) && ( LOG_LEVEL != LOG_ERROR ) && ( LOG_LEVEL != LOG_WARN ) && ( LOG_LEVEL != LOG_INFO ) && ( LOG_LEVEL != LOG_DEBUG ) ) */


#endif /* LOGGING_H */
