#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "logger.h"

// TODO: Add color codes specific to a log level

const char *levelStrings[] = {"[FATAL]", "[INFO]", "[DEBUG]", "[WARNING]"};

void log_output(LOG_LEVEL level, const char *formatString, ...) {
  char output[32000];
  memset(output, 0, sizeof(output));
  va_list argPtr;
  va_start(argPtr, formatString);
  vsnprintf(output, sizeof(output), formatString, argPtr);
  va_end(argPtr);

  char finalOutput[32000];
  memset(finalOutput, 0, sizeof(finalOutput));
  snprintf(finalOutput, sizeof(finalOutput), "%s: %s\n", levelStrings[level],
           output);
  printf("%s", finalOutput);
}
