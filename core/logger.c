#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "logger.h"

const char *levelStrings[] = {"[FATAL]", "[INFO]", "[DEBUG]", "[WARNING]"};
const char *colorCodes[] = {"[31m", "[32m", "[35m", "[33m", "\033", "[0m"};

void log_output(LOG_LEVEL level, const char *formatString, ...) {
  char output[32000];
  memset(output, 0, sizeof(output));
  va_list argPtr;
  va_start(argPtr, formatString);
  vsnprintf(output, sizeof(output), formatString, argPtr);
  va_end(argPtr);

  char finalOutput[32000];
  memset(finalOutput, 0, sizeof(finalOutput));
  snprintf(finalOutput, sizeof(finalOutput), "%s%s%s: %s%s%s\n",
           colorCodes[LEVEL_COUNT], colorCodes[level], levelStrings[level],
           output, colorCodes[LEVEL_COUNT], colorCodes[LEVEL_COUNT + 1]);
  printf("%s", finalOutput);
}
