/*
 * Project: PRIMUM ENGINE
 * Author:  KEN KIKAYA
 *
 * This is the basic logging system implemented for the engine. The function defined below is not
 * to be used directly. Instead, macros dependent on the reason or level of the log entry are to be
 * used. They eventually call this function but they fill in the log level from the levels array defined below.
 * Using these macros exclusively for output when using the engine is encouraged to maintain uniformity and 
 * because it provides the user with more info regarding the reason for the output.
 *
 */

# include <stdarg.h>
# include <string.h>
# include <stdio.h>

# include "logger.h"

void log_output(logLevel level, const char *color, char *message, ...){
    char output[32000];
    memset(output, 0, sizeof(output));

    va_list argPtr;
    va_start(argPtr, message);
    vsnprintf(output, sizeof(output), message, argPtr);
    va_end(argPtr);

    char *levels[5] = {"FATAL", "ERROR", "WARNING", "DEBUG", "INFO"};
    char outputMessage[32100];
    snprintf(outputMessage, sizeof(outputMessage), "[%s] %s\n", levels[level], output);
    printf("%s%s%s", color, outputMessage, COLOR_RESET);
}
