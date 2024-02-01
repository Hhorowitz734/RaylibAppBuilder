#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>

static FILE *LOGFILE = NULL;


void initLogfile();

void logMessage(const char *format, ...);

#endif