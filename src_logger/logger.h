#ifndef ARCADE_PONG_LOGGER_H
#define ARCADE_PONG_LOGGER_H

// Create logfile for current launch
int start_log(char* file_path);

// Log message in file
int logg(char* message, char* file_path);

// Reset log file
int reset_log(char* file_path);

// Log message in file and in console
int log_all(char* message, char* file_path);

#endif //ARCADE_PONG_LOGGER_H