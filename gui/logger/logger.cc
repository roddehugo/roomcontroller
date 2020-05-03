#include "logger.hh"

#include <cstdarg>
#include <cstring>
#include <iostream>

#define BLUE "\x1b[34m"
#define GREEN "\x1b[32m"
#define ORANGE "\x1b[33m"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"

void Logger::log(
        int8_t level, const char * file, uint32_t line, const char * dsc)
{
    static const char * colors[] = {BLUE, GREEN, ORANGE, RED};
    static const char * levels[] = {"TRACE", "INFO", "WARN", "ERROR"};
    std::cout << colors[level] << levels[level] << " " << rstrip(file, '/', 2)
              << ":" << line << "]" RESET " " << dsc << '\n';
}

void Logger::logf(
        int8_t level, const char * file, uint32_t line, const char * fmt, ...)
{
    char buf[256];
    int bufsize = sizeof(buf);
    std::va_list ap;
    va_start(ap, fmt);
    int len = std::vsnprintf(buf, bufsize, fmt, ap);
    va_end(ap);
    if (len >= bufsize)
    {
        bufsize -= 4;
        buf[bufsize++] = '.';
        buf[bufsize++] = '.';
        buf[bufsize++] = '.';
    }
    log(level, file, line, buf);
}

const char * Logger::lstrip(const char * str, const char c, int n)
{
    const char * pch = str;
    while (n-- && *pch != '\0')
    {
        while (*pch != c)
            if (*(++pch) == '\0')
                break;
        if (*pch == c)
            ++pch;
    }
    return *pch != '\0' ? pch : str;
}

const char * Logger::rstrip(const char * str, const char c, int n)
{
    const char * pch = &str[std::strlen(str) - 1];
    while (n-- && pch != str)
    {
        while (*pch != c)
            if (--pch == str)
                break;
        if (*pch == c)
            --pch;
    }
    return pch != str ? pch + 2 : str;
}
