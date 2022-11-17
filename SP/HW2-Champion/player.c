#include "status.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PLAYER_PATH "./player_status.txt"

int fifoFd;
FILE * file_fd, log_fd;
int fullHp, agentCheck;
Status info;
char buf[512];

int main (int argc, char **argv) {
	int playerId = atoi(argv[1]);
	int pPid = atoi(argv[2]);
	pid_t pid = getpid();
	if (playerId > 7){
		agentCheck = 1;
		sprintf(buf, "player%d.fifo", playerId)
		fifoFd = open(buf, O_RDONLY);
		read(fifoFd, &info, sizeof(fifoFd));
	}
	else if (playerId <= 7 && playerId >= 0){
		file_fd = fopen(PLAYER_PATH, "r");
		for(int i = 0; i < playerId; ++i){
			char attrTemp[16];
			fscanf(file_fd, "%d %d %s %c %d\n", &info.HP, &info.ATK, attrTemp, &info.current_battle_id, &info.battle_ended_flag);
		}
		info.attr = (Attribute)attrTemp;
	}
	fullHp = info.HP;
	sprintf(buf, "log_player%d.txt", info.real_player_id);
	log_fd = fopen(buf, "a+");
	while (info.HP > 0) {
		while (info.battle_ended_flag != 1){
			fprintf(log_fd, "%d,%d pipe to %c,%d %d,%d,%c,%d\n", playerId, pid, info.current_battle_id, pPid, info.real_player_id, info.HP, info.current_battle_id, info.battle_ended_flag)
			write(1, &info, sizeof(Status));
			read(0, &info, sizeof(Status));
			fprintf(log_fd, "%d,%d pipe from %c,%d %d,%d,%c,%d\n", playerId, pid, info.current_battle_id, pPid, info.real_player_id, info.HP, info.current_battle_id, info.battle_ended_flag)
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
}		memset(sHp, 0, strlen(sHp)); sprintf(sHp, "%d", info.HP);
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