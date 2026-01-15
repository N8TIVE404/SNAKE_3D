# ifndef LOGGER_H
# define LOGGER_H

// Color codes
# define COLOR_FATAL   "\033[1;37;41m"
# define COLOR_ERROR   "\033[1;31m"
# define COLOR_WARN    "\033[1;33m"
# define COLOR_INFO    "\033[1;36m"
# define COLOR_DEBUG   "\033[0;90m"
# define COLOR_RESET   "\033[0m"

typedef enum logLevel{
    FATAL, ERROR, WARNING, DEBUG, INFO, LEVEL_COUNT
} logLevel;

void log_output(logLevel, const char*, char*, ...);

# define FATAL_LOG(message, ...) log_output(FATAL, COLOR_FATAL, message, ##__VA_ARGS__)
# define ERROR_LOG(message, ...) log_output(ERROR, COLOR_ERROR, message, ##__VA_ARGS__)
# define WARNING_LOG(message, ...) log_output(WARNING, COLOR_WARN, message, ##__VA_ARGS__)
# define DEBUG_LOG(message, ...) log_output(DEBUG, COLOR_DEBUG, message, ##__VA_ARGS__)
# define INFO_LOG(message, ...) log_output(INFO, COLOR_INFO, message, ##__VA_ARGS__)

# endif
