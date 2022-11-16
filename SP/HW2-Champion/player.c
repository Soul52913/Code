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

int file_fd, log_fd, fullHp, agentCheck;

char *logTo(char *selfId, char *selfPid, char *targetId, char *targetPid,
				 char *realPlayerId, char *hp, char *currentBattleId, char *endFlag){
	char after[512];
	memset(after, 0, strlen(after));
	strcat(after, selfId); strcat(after, ","); strcat(after, selfPid); strcat(after, " pipe to "); strcat(after, targetId); strcat(after, ","); strcat(after, targetPid); strcat(after, " ");
	strcat(after, realPlayerId); strcat(after, ","); strcat(after, hp); strcat(after, ","); strcat(after, currentBattleId); strcat(after, ","); strcat(after, endFlag); strcat(after, "\n");
	return after;
}

char *logFrom(char *selfId, char *selfPid, char *targetId, char *targetPid,
				 char *realPlayerId, char *hp, char *currentBattleId, char *endFlag){
	char after[512];
	memset(after, 0, strlen(after));
	strcat(after, selfId); strcat(after, ","); strcat(after, selfPid); strcat(after, " pipe from "); strcat(after, targetId); strcat(after, ","); strcat(after, targetPid); strcat(after, " ");
	strcat(after, realPlayerId); strcat(after, ","); strcat(after, hp); strcat(after, ","); strcat(after, currentBattleId); strcat(after, ","); strcat(after, endFlag); strcat(after, "\n");
	return after;
}

char *fifoTo(char *selfId, char *selfPid, char *targetId, char *realPlayerId, char *hp){
	char after[512];
	memset(after, 0, strlen(after));
	strcat(after, selfId); strcat(after, ","); strcat(after, selfPid); strcat(after, " fifo to "); strcat(after, targetId); strcat(after, " ");
	strcat(after, realPlayerId); strcat(after, ","); strcat(after, hp); strcat(after, "\n");
	return after;
}

char *fifoFrom(char *selfId, char *selfPid, char *targetId, char *realPlayerId, char *hp){
	char after[512];
	memset(after, 0, strlen(after));
	strcat(after, selfId); strcat(after, ","); strcat(after, selfPid); strcat(after, " fifo from "); strcat(after, targetId); strcat(after, " ");
	strcat(after, realPlayerId); strcat(after, ","); strcat(after, hp); strcat(after, "\n");
	return after;
}

int main (int argc, char **argv) {
	int playerId = atoi(argv[1]);
	int pPid = atoi(argv[2]);
	if (playerId > 7){
		agentCheck = 1;
	}
	else if (playerId <= 7 && playerId >= 0){
		file_fd = open(PLAYER_PATH, O_RDWR);
		for(int i = 0; i < playerId; ++i){
			fscanf(file_fd, "%d%d%s%c%d", Status.HP, Status.ATK, Status.attr, Status.current_battle_id, Status.battle_ended_flag);
		}
		fullHp = Status.HP;
		Status.real_player_id = playerId;
	}
	char name[512], fileName = "log_player";
	name[0] = '.', name[1] = '/', name[2] = '\0';
	strcat(name, fileName);
	strcat(name, argv[1]);
	log_fd = open(name, O_WRONLY | O_CREAT | O_APPEND);
	char logLine[256];
	memset(logLine, 0, strlen(logLine));

	write(log_fd, logLine, sizeof(logLine));
	while (Status.battle_ended_flag != 1){

	}
	if (Status.HP > 0){
		Status.HP += ((fullHp - Status.HP) / 2);
	}
	else if (agent == 0) {
		Status.HP = fullHp;
		//to fifo
	}
	else {
		exit;
	}
	return 0;
}