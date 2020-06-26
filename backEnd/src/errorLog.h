//
// Created by amagood on 2020/4/19.
//

#ifndef MY_PROJECT_ERRORLOG_H
#define MY_PROJECT_ERRORLOG_H

#include <iostream>
#define PrintError
#define PrintInfo
#define PrintDebug
std::string unixTime2Str(unsigned long long int ms)
{
    ms/=1000;
    struct tm tm = *localtime((time_t *)&ms);
    char strTime[100]={};
    int bufLen = 100;
    strftime(strTime, bufLen - 1, "%Y-%m-%d %H:%M:%S", &tm);
    strTime[bufLen - 1] = '\0';

    std::string str(strTime);
    return str;
}

namespace Error
{
    template <typename T>
    int error(T input)
    {
    #ifdef PrintError
        std::cerr<<input;
    #endif
        return 0;
    }
    template <typename T>
    int error(unsigned long long int ms, T input)
    {
        error(unixTime2Str(ms)), error(" Error: "), error(input);
        return 0;
    }

    template <typename T>
    int info(T input)
    {
    #ifdef PrintInfo
        std::cerr<<input;
    #endif
        return 0;
    }
    template <typename T>
    int info(unsigned long long int ms, T input)
    {
        info(unixTime2Str(ms)), info(" Info: "), info(input);
        return 0;
    }

    template <typename T>
    int debug(T input)
    {
    #ifdef PrintDebug
        std::cerr<<input;
    #endif
        return 0;
    }
    template <typename T>
    int debug(unsigned long long int ms, T input)
    {
        debug(unixTime2Str(ms)), debug(" Debug: "), debug(input);
        return 0;
    }
};



#endif //MY_PROJECT_ERRORLOG_H
