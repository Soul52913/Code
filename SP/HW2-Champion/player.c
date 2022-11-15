//#include "status.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef enum {
    FIRE,
    GRASS,
    WATER
} Attribute;

typedef struct {
    int real_player_id; // ID of the Real Player, an integer from 0 - 7
    int HP; // Healthy Point
    int ATK; // Attack Power
    Attribute attr; // Player's attribute
    char current_battle_id; //current battle ID
    int battle_ended_flag; // a flag for validate if the battle is the last round or not, 1 for yes, 0 for no
} Status;

#define PLAYER_PATH "./player_status.txt"

int file_fd, log_fd;

char *createline(char *after, char *beforeOne, char *beforeTwo){
	if((after = malloc(strlen(beforeOne) + strlen(beforeTwo) + 1)) != NULL){
		after[0] = '\0';
		strcat(after, beforeOne);
		strcat(after, beforeTwo);
	}
	return after;
}

int main (int argc, char **argv) {
	int playerId = atoi(argv[1]);
	int pPid = atoi(argv[2]);
	if (playerId > 7){

	}
	else if (playerId <= 7 && playerId >= 0){
		file_fd = open(PLAYER_PATH, O_RDWR);
		for(int i = 0; i < playerId; ++i){
			fscanf(file_fd, "%d%d%s%c%d", Status.HP, Status.ATK, Status.attr, Status.current_battle_id, Status.battle_ended_flag);
		}
		Status.real_player_id = playerId;
	}
	char name[512], fileName = "log_player";
	name[0] = '.', name[1] = '/', name[2] = '\0';
	strcat(name, fileName);
	strcat(name, argv[1]);
	log_fd = open(name, O_WRONLY | O_CREAT | O_APPEND);
	char logLine[512];
	logLine = {0};
	write(fd, logLine, sizeof(logLine));
	return 0;
}