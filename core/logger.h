# ifndef LOGGER_H
# define LOGGER_H

typedef enum logLevel{
    FATAL, ERROR, WARNING, DEBUG, INFO, LEVEL_COUNT
} logLevel;

void log_output(logLevel, char*, ...);

# define FATAL_LOG(message, ...) log_output(FATAL, message, ##__VA_ARGS__)
# define ERROR_LOG(message, ...) log_output(ERROR, message, ##__VA_ARGS__)
# define WARNING_LOG(message, ...) log_output(WARNING, message, ##__VA_ARGS__)
# define DEBUG_LOG(message, ...) log_output(DEBUG, message, ##__VA_ARGS__)
# define INFO_LOG(message, ...) log_output(INFO, message, ##__VA_ARGS__)

# endif
