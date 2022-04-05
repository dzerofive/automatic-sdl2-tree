#pragma once

#include <stdio.h>
#include <ctime>
#include <string>
#include <cstdarg>


enum logType
{
    Normal,
    Fatal,
    Error,
    Warning,
    Ok
};

namespace Logger
{
static time_t currentTime = time(0);
static tm *ltm = localtime(&currentTime);

static void updateTime()
{
    currentTime = time(0);
    ltm = localtime(&currentTime);
}

/**
 * @brief Print time, type, and message to log with apropriate color.
 * 
 * @param text Text of the message
 * @param type Can be Normal, Warning, Fatal and Ok
 */
static void log(std::string text)
{
    Logger::updateTime();
    printf("%02i:%02i:%02i :: %s\n", ltm->tm_hour, ltm->tm_min, ltm->tm_sec, text.c_str());
}


static void log(logType type, const char* text, ...)
{
    Logger::updateTime();
    switch (type)
    {
    case Normal:
        printf("%02i:%02i:%02i :: ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
        break;
    
    case Warning:
        printf("\x1B[33m%02i:%02i:%02i\x1B[0m :: \x1B[33mWARNING\x1B[0m :: ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
        break;

    case Error:
        printf("\x1B[31m%02i:%02i:%02i\x1B[0m :: \x1B[31mError\x1B[0m :: ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
        break;

    case Fatal:
        printf("\033[2;31m%02i:%02i:%02i\x1B[0m :: \033[2;31mFATAL\x1B[0m :: ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
        break;

    case Ok:
        printf("\x1B[32m%02i:%02i:%02i\x1B[0m :: \x1B[32mOK\x1B[0m :: ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
        break;

    default:
        printf("\x1B[35m%02i:%02i:%02i\x1B[0m :: \x1B[35mINVALID LOG TYPE\x1B[0m :: ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
        break;
    }

    va_list args;
    va_start(args, text);
    vprintf(text, args);
    va_end(args);
    putchar('\n');
    
}


}