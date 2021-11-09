//
// Created by Daan Meijer on 11/2/21.
//

#ifndef TESTER_LOGGER_H
#define TESTER_LOGGER_H

#ifndef LOG_FILENAME
#define LOG_FILENAME "deepthought"
#endif

#ifdef TESTER_LOG
#define LogF(...) LogFormatted(__VA_ARGS__)
#define LogStart() OpenLogStream()
#define LogStop() CloseLogStream()
#else
#define LogF(x, ...)
#define LogStart()
#define LogStop()
#endif

void OpenLogStream();

void LogFormatted(const char *format, ...);

void CloseLogStream();

#endif //TESTER_LOGGER_H
