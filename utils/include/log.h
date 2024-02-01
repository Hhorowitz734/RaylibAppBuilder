#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>

static FILE *LOGFILE = NULL;


void initLogfile() {

    char filename[64];
    char dirPath[] = "../logs/";
    char filepath[128];
    
    //Sets permissions and creates folder if it doesn't exist
    struct stat st = {0};
    if (stat(dirPath, &st) == -1) {
        mkdir(dirPath, 0700);
    }

    //Gets time and creates logpath name based on it
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(filename, sizeof(filename), "log_%Y%m%d_%H%M%S.txt", tm_info);
    
    snprintf(filepath, sizeof(filepath), "%s%s", dirPath, filename);
    
    //Opens the file and sets the global pointer
    LOGFILE = fopen(filepath, "a");

    if (LOGFILE == NULL) {
        perror("Failed to open log file");
        exit(EXIT_FAILURE);
    }

}

void logMessage(const char *format, ...) {

    //If this activates something has gone seriously wrong
    if (LOGFILE == NULL) { return; }

    //Gets current time to see how long our program takes (should not be >1s)
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timeBuffer[20]; 
    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", tm_info);

    //Write time to logfile
    fprintf(LOGFILE, "[%s] ", timeBuffer);

    //Handle %s %d etc etc
    va_list args;
    va_start(args, format);
    vfprintf(LOGFILE, format, args);
    va_end(args);

    //Newline
    fprintf(LOGFILE, "\n");
    fflush(LOGFILE);

}


#endif