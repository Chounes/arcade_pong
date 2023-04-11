#ifndef ARCADE_PONG_LOGGER_H
#define ARCADE_PONG_LOGGER_H

#include <stdio.h>
#include <stdbool.h>

// Create logfile for current launch
int initLog(char* file_path);

// Log message in file
int loggerInfo(const char* message, char* file_path);

// Reset log file
int loggerClean(char* file_path);

// Log message in file and in console
int loggerDebug(const char* message, char* file_path, bool debug);

// Get current date
char* getDate();

#endif //ARCADE_PONG_LOGGER_H