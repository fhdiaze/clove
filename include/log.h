// clang-format Language: C

#ifndef LOG_H
#define LOG_H

#include <stdint.h>

#define LOG_LEVEL_ALL 0UL
#define LOG_LEVEL_TRACE 1UL
#define LOG_LEVEL_DEBUG 2UL
#define LOG_LEVEL_INFO 3UL
#define LOG_LEVEL_WARN 4UL
#define LOG_LEVEL_ERROR 5UL
#define LOG_LEVEL_FATAL 6UL
#define LOG_LEVEL_OFF 7UL

// Defines what is the minimum priority of a message to be logged.
// Anything with higher priority is going to be logged.
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_ALL
#endif // LOG_LEVEL

#define STRINGIFY(n) #n
#define STRGY(n) STRINGIFY(n)

#define LOG_MSG(log_level, fmt, file_name, func_name, line_number, ...)     \
        printf("[" log_level "] %s:%s:%s: " fmt "\n", file_name, func_name, \
               STRGY(line_number) __VA_OPT__(, ) __VA_ARGS__)

#define LOG_MSG_NOOP(...) \
        ((void)0)

// Logs a trace message if LOG_LEVEL <= LOG_LEVEL_TRACE
// Usage: logd("Log trace: x=%d", x);
#if LOG_LEVEL <= LOG_LEVEL_TRACE
#define logt(fmt, ...) \
        LOG_MSG("TRACE", fmt, __FILE__, __func__, __LINE__, __VA_ARGS__)
#else
#define logt(fmt, ...) \
        LOG_MSG_NOOP()
#endif // logt

// Logs a debug message if LOG_LEVEL <= LOG_LEVEL_DEBUG.
// Usage: logd("log debug: x=%d", x);
#if LOG_LEVEL <= LOG_LEVEL_DEBUG
#define logd(fmt, ...) \
        LOG_MSG("DEBUG", fmt, __FILE__, __func__, __LINE__, __VA_ARGS__)
#else
#define logd(fmt, ...) \
        LOG_MSG_NOOP()
#endif // logd

// Logs an information message if LOG_LEVEL <= LOG_LEVEL_INFO
// Usage: logi("Log info: x=%d", x);
#if LOG_LEVEL <= LOG_LEVEL_INFO
#define logi(fmt, ...) \
        LOG_MSG("INFO", fmt, __FILE__, __func__, __LINE__, __VA_ARGS__)
#else
#define logi(fmt, ...) \
        LOG_MSG_NOOP()
#endif // logi

// Logs a warning message if LOG_LEVEL <= LOG_LEVEL_WARN
// Usage: logw("Log warn: x=%d", x);
#if LOG_LEVEL <= LOG_LEVEL_WARN
#define logw(fmt, ...) \
        LOG_MSG("WARN", fmt, __FILE__, __func__, __LINE__, __VA_ARGS__)
#else
#define logw(fmt, ...) \
        LOG_MSG_NOOP()
#endif // logw

// Logs an error message if LOG_LEVEL <= LOG_LEVEL_ERROR
// Usage: loge("Log error: x=%d", x);
#if LOG_LEVEL <= LOG_LEVEL_ERROR
#define loge(fmt, ...) \
        LOG_MSG("ERROR", fmt, __FILE__, __func__, __LINE__, __VA_ARGS__)
#else
#define loge(fmt, ...) \
        LOG_MSG_NOOP()
#endif // loge

// Logs a fatal message if LOG_LEVEL <= LOG_LEVEL_FATAL
// Usage: logf("Log fatal: x=%d", x);
#if LOG_LEVEL <= LOG_LEVEL_FATAL
#define logf(fmt, ...) \
        LOG_MSG("FATAL", fmt, __FILE__, __func__, __LINE__, __VA_ARGS__)
#else
#define logf(fmt, ...) \
        LOG_MSG_NOOP()
#endif // logf

#endif // LOG_H
