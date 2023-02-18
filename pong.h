#ifndef ARCADE_PONG_PONG_H
#define ARCADE_PONG_PONG_H

const char *AUTHOR= " ██████╗██╗  ██╗ ██████╗ ██╗   ██╗███╗   ██╗███████╗\n██╔════╝██║  ██║██╔═══██╗██║   ██║████╗  ██║██╔════╝\n██║     ███████║██║   ██║██║   ██║██╔██╗ ██║█████╗\n██║     ██╔══██║██║   ██║██║   ██║██║╚██╗██║██╔══╝\n╚██████╗██║  ██║╚██████╔╝╚██████╔╝██║ ╚████║███████╗\n ╚═════╝╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚══════╝\n";
const char *TITLE= "\n8888888b.   .d88888b.  888b    888  .d8888b.  \n888   Y88b d88P   Y88b 8888b   888 d88P  Y88b \n888    888 888     888 88888b  888 888    888 \n888   d88P 888     888 888Y88b 888 888        \n8888888P   888     888 888 Y88b888 888  88888 \n888        888     888 888  Y88888 888    888\n888        Y88b. .d88P 888   Y8888 Y88b  d88P \n888          Y88888P   888    Y888  Y8888P88 \n\n\n";
#define LOG_FILE_PATH "./services_log/pong.log"

int menu();
int console_menu();
int console_credits();
int console_play();


#endif //ARCADE_PONG_PONG_H
