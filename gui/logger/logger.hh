#pragma once

#include <cstdint>

#define ltrace(fmt, ...) \
    Logger::logf(Logger::TRACE, __FILE__, __LINE__, fmt, __VA_ARGS__)

#define linfo(fmt, ...) \
    Logger::logf(Logger::INFO, __FILE__, __LINE__, fmt, __VA_ARGS__)

#define lwarn(fmt, ...) \
    Logger::logf(Logger::WARN, __FILE__, __LINE__, fmt, __VA_ARGS__)

#define lerror(fmt, ...) \
    Logger::logf(Logger::ERROR, __FILE__, __LINE__, fmt, __VA_ARGS__)

class Logger
{
  public:
    enum Level
    {
        TRACE,
        INFO,
        WARN,
        ERROR
    };

  public:
    Logger() = delete;
    ~Logger() = delete;
    static void log(
            int8_t level, const char * file, unsigned line, const char * dsc);
    static void logf(int8_t level, const char * file, unsigned line,
            const char * fmt, ...) __attribute__((format(printf, 4, 5)));

  protected:
    static const char * lstrip(const char * str, const char c, int n = 1);
    static const char * rstrip(const char * str, const char c, int n = 1);
};
