#include "status.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PLAYER_PATH "./player_status.txt"

int fifoFd, log_fd;
FILE * file_fd;
int fullHp, agentCheck;
Status info;

void logTo(char *after, char *selfId, char *selfPid, char *targetId, char *targetPid,
				 char *realPlayerId, char *hp, char *currentBattleId, char *endFlag){
	memset(after, 0, strlen(after));
	strcat(after, selfId); strcat(after, ","); strcat(after, selfPid); strcat(after, " pipe to "); strcat(after, targetId); strcat(after, ","); strcat(after, targetPid); strcat(after, " ");
	strcat(after, realPlayerId); strcat(after, ","); strcat(after, hp); strcat(after, ","); strcat(after, currentBattleId); strcat(after, ","); strcat(after, endFlag); strcat(after, "\n");
	return;
}

void logFrom(char *after, char *selfId, char *selfPid, char *targetId, char *targetPid,
				 char *realPlayerId, char *hp, char *currentBattleId, char *endFlag){
	memset(after, 0, strlen(after));
	strcat(after, selfId); strcat(after, ","); strcat(after, selfPid); strcat(after, " pipe from "); strcat(after, targetId); strcat(after, ","); strcat(after, targetPid); strcat(after, " ");
	strcat(after, realPlayerId); strcat(after, ","); strcat(after, hp); strcat(after, ","); strcat(after, currentBattleId); strcat(after, ","); strcat(after, endFlag); strcat(after, "\n");
	return;
}

void fifoTo(char *after, char *selfId, char *selfPid, char *targetId, char *realPlayerId, char *hp){
	memset(after, 0, strlen(after));
	strcat(after, selfId); strcat(after, ","); strcat(after, selfPid); strcat(after, " fifo to "); strcat(after, targetId); strcat(after, " ");
	strcat(after, realPlayerId); strcat(after, ","); strcat(after, hp); strcat(after, "\n");
	return;
}

void fifoFrom(char *after, char *selfId, char *selfPid, char *targetId, char *realPlayerId, char *hp){
	memset(after, 0, strlen(after));
	strcat(after, selfId); strcat(after, ","); strcat(after, selfPid); strcat(after, " fifo from "); strcat(after, targetId); strcat(after, " ");
	strcat(after, realPlayerId); strcat(after, ","); strcat(after, hp); strcat(after, "\n");
	return;
}

int main (int argc, char **argv) {
	int playerId = atoi(argv[1]);
	int pPid = atoi(argv[2]);
	pid_t pid = getpid();
	if (playerId > 7){
		agentCheck = 1;
		char fifoName[256]; 
		char *fileName = "player";
		memset(fifoName, 0, strlen(fifoName));
		fifoName[0] = '.', fifoName[1] = '/', fifoName[2] = '\0';
		strcat(fifoName, fileName);
		strcat(fifoName, argv[1]);
		fifoFd = open(fifoName, O_RDONLY);
		read(fifoFd, &info, sizeof(fifoFd));
		info.real_player_id = playerId - 8;
	}
	else if (playerId <= 7 && playerId >= 0){
		file_fd = fopen(PLAYER_PATH, "r");
		for(int i = 0; i < playerId; ++i){
			fscanf(file_fd, "%d%d%s%c%d", info.HP, info.ATK, info.attr, info.current_battle_id, info.battle_ended_flag);
		}
		info.real_player_id = playerId;
	}
	fullHp = info.HP;
	char name[256], logLine[256], infoData[256], sPid[256], sRealId[256], sHp[256], sCurBattle[256], sEndFlag[256];
	char *fileName = "log_player";
	sprintf(sRealId, "%d", info.real_player_id);
	memset(sRealId, 0, strlen(sRealId));
	memset(name, 0, strlen(name));
	name[0] = '.', name[1] = '/', name[2] = '\0';
	strcat(name, fileName);
	strcat(name, sRealId);
	log_fd = open(name, O_WRONLY | O_CREAT | O_APPEND);
	while (info.HP > 0) {
		while (info.battle_ended_flag != 1){
			memset(logLine, 0, strlen(logLine));
			memset(sPid, 0, strlen(sPid)); sprintf(sPid, "%d", pid);
			memset(sRealId, 0, strlen(sRealId)); sprintf(sRealId, "%d", info.real_player_id);
			memset(sHp, 0, strlen(sHp)); sprintf(sHp, "%d", info.HP);
			memset(sCurBattle, 0, strlen(sCurBattle)); sprintf(sCurBattle, "%c", info.current_battle_id);
			memset(sEndFlag, 0, strlen(sEndFlag)); sprintf(sEndFlag, "%d", info.battle_ended_flag);
			logTo(logLine, argv[1], sPid, sCurBattle, argv[2], sRealId, sHp, sCurBattle, sEndFlag);
			write(log_fd, logLine, sizeof(logLine));
			write(1, &info, sizeof(Status));
			fscanf(0, "%d%d%s%c%d", info.HP, info.ATK, info.attr, info.current_battle_id, info.battle_ended_flag);
			memset(logLine, 0, strlen(logLine));
			memset(sPid, 0, strlen(sPid)); sprintf(sPid, "%d", pid);
			memset(sRealId, 0, strlen(sRealId)); sprintf(sRealId, "%d", info.real_player_id);
			memset(sHp, 0, strlen(sHp)); sprintf(sHp, "%d", info.HP);
			memset(sCurBattle, 0, strlen(sCurBattle)); sprintf(sCurBattle, "%c", info.current_battle_id);
			memset(sEndFlag, 0, strlen(sEndFlag)); sprintf(sEndFlag, "%d", info.battle_ended_flag);
			logFrom(logLine, argv[1], sPid, sCurBattle, argv[2], sRealId, sHp, sCurBattle, sEndFlag);
			write(log_fd, logLine, sizeof(logLine));
		}
		info.HP += ((fullHp - info.HP) / 2);
		info.battle_ended_flag = 0;
	}
	if (agentCheck == 0) {
		info.HP = fullHp;
		info.battle_ended_flag = 0;
		char fifoName[256]; 
		char *fileName = "player";
		char fifoId[256]; sprintf(fifoId, "%d", info.real_player_id + 7);
		memset(fifoName, 0, strlen(fifoName));
		fifoName[0] = '.', fifoName[1] = '/', fifoName[2] = '\0';
		strcat(name, fileName);
		strcat(name, fifoId);
		mkfifo(fifoName, 0777);
		fifoFd = open(fifoName, O_WRONLY);
		memset(logLine, 0, strlen(logLine));
		char sPid[256]; sprintf(sPid, "%d", pid);
		char sTargetId[256]; sprintf(sTargetId, "%d", info.real_player_id + 7);
		char sRealId[256]; sprintf(sRealId, "%d", info.real_player_id);
		char sHp[256]; sprintf(sHp, "%d", info.HP);
		fifoTo(logLine, argv[1], sPid, sTargetId, sRealId, sHp);
		write(log_fd, logLine, sizeof(logLine));
        write(fifoFd, &info, sizeof(Status));
        close(fifoFd);
	}
	exit(0);
	return 0;
}