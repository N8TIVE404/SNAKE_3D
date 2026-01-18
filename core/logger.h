#ifndef LOGGER_H
#define LOGGER_H

typedef enum LOG_LEVEL { FATAL, INFO, DEBUG, WARNING, LEVEL_COUNT } LOG_LEVEL;

void log_output(LOG_LEVEL, const char *, ...);

#define FATAL_LOG(message, ...) log_output(FATAL, message, ##__VA_ARGS__)
#define DEBUG_LOG(message, ...) log_output(DEBUG, message, ##__VA_ARGS__)
#define INFO_LOG(message, ...) log_output(INFO, message, ##__VA_ARGS__)
#define WARNING_LOG(message, ...) log_output(WARNING, message, ##__VA_ARGS__)

#endif
