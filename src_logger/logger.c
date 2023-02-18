#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include <time.h>
#include <string.h>


// Create logfile for current launch
int start_log(char *file_path) {
    time_t rawtime;
    struct tm *tm;
    time(&rawtime);
    tm = localtime(&rawtime);
    // Open file in filepath in append mode
    FILE *log_file = fopen(file_path, "a");
    if (log_file == NULL) {
        printf("Error : logfile may be not accessible or does not exist\n");
        exit(1);
    }
    // remove date back line
    char *date = asctime(tm);
    date[strlen(date) - 1] = '\0';
    fprintf(log_file, "[%s]___: Start pong session\n", date);
    printf("[%s]___: Start pong session\n", date);
    fclose(log_file);


    return 0;
}

int logger(char *message, char *file_path) {
    FILE *log_file = fopen(file_path, "a");
    time_t rawtime;
    struct tm *tm;
    time(&rawtime);
    tm = localtime(&rawtime);
    // remove date back line
    char *date = asctime(tm);
    date[strlen(date) - 1] = '\0';
    fprintf(log_file, "[%s]___: %s\n", date, message);
    printf("[%s]___: %s\n", date, message);
    fclose(log_file);

    return 0;
}

int reset_log(char *file_path) {
    FILE *log_file = fopen(file_path, "w");
    fclose(log_file);
    return 0;
}
