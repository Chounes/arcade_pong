#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include <time.h>
#include <string.h>
#include <stdbool.h>


// Create logfile for current launch
int initLog(char *file_path) {
    // Open file in filepath in append mode
    FILE *log_file = fopen(file_path, "a");
    if (log_file == NULL) {
        printf("Error : logfile may be not accessible or does not exist\n");
        exit(1);
    }
    // remove date back line
    printf("[%s]___: Start pong session\n", getDate());
    fprintf(log_file, "[%s]___: Start pong session\n", getDate());
    fclose(log_file);
    return 0;
}

int loggerInfo(const char *message, char *file_path) {
    FILE *log_file = fopen(file_path, "a");
    printf("[%s]___: %s\n", getDate(), message);
    fprintf(log_file, "[%s]___: %s\n", getDate(), message);
    fclose(log_file);
    return 0;
}

int loggerDebug(const char *message, char *file_path, bool debug) {
    if (!debug) {
        return 0;
    }
    FILE *log_file = fopen(file_path, "a");
    printf("[%s][DEBUG]___: %s\n", getDate(), message);
    fprintf(log_file, "[%s][DEBUG]___: %s\n", getDate(), message);
    fclose(log_file);
    return 0;
}

int loggerClean(char *file_path) {
    FILE *log_file = fopen(file_path, "w");
    fclose(log_file);
    return 0;
}

char* getDate() {
    time_t rawtime;
    struct tm *tm;
    time(&rawtime);
    tm = localtime(&rawtime);
    // remove date back line
    char *date = asctime(tm);
    date[strlen(date) - 1] = '\0';
    return date;
}
