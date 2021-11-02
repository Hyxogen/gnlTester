//
// Created by Daan Meijer on 11/2/21.
//

#include "Logger.h"
#include <stdio.h>
#include <stdarg.h>
#include "Assert.h"

static FILE* g_LogStream;

void OpenLogStream() {
	g_LogStream = fopen(LOG_FILENAME, "w");
	ASSERT(g_LogStream);
}

void LogFormatted(const char *format, ...) {
	va_list args_list;
	va_start(args_list, format);
	ASSERT(g_LogStream);
	vfprintf(g_LogStream, format, args_list);
}

void CloseLogStream() {
	fclose(g_LogStream);
}