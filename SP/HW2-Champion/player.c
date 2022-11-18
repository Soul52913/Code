#include "status.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PLAYER_PATH "./player_status.txt"

int main (int argc, char **argv) {
	int fifoFd = 0;
	FILE * file_fd, * log_fd;
	int fullHp = 0;
	Status info;
	char buf[512];
	char targetId[20] = {'G', 'G', 'H', 'H', 'I', 'I', 'J', 'J', 'M', 'M', 'K', 'N', 'N', 'L', 'C'};
	int agentid[128] = {0};
	int playerId = atoi(argv[1]);
	int pPid = atoi(argv[2]);
	agentid['G'] = 8, agentid['I'] = 9, agentid['D'] = 10, agentid['H'] = 11, agentid['J'] = 12;
	agentid['E'] = 13, agentid['B'] = 14;
	pid_t pid = getpid();
	if (playerId > 7){
		sprintf(buf, "player%d.fifo", playerId);
		mkfifo(buf, 0700);
		fifoFd = open(buf, O_RDONLY);
		read(fifoFd, &info, sizeof(Status));
		sprintf(buf, "log_player%d.txt", info.real_player_id);
		log_fd = fopen(buf, "a+");
		fprintf(log_fd, "%d,%d fifo from %d %d,%d\n", playerId, pid, info.real_player_id, info.real_player_id, info.HP);
	}
	else if (playerId <= 7 && playerId >= 0){
		file_fd = fopen(PLAYER_PATH, "r");
		char attrTemp[16];
		for(int i = 0; i <= playerId; ++i){
			fscanf(file_fd, "%d %d %s %c %d\n", &info.HP, &info.ATK, attrTemp, &info.current_battle_id, &info.battle_ended_flag);
		}
		info.real_player_id = playerId;
		if (strcmp(attrTemp, "FIRE") == 0) 
			info.attr = FIRE;
		else if (strcmp(attrTemp, "GRASS") == 0) 
			info.attr = GRASS;
		else if (strcmp(attrTemp, "WATER") == 0) 
			info.attr = WATER;
		fclose(file_fd);
		sprintf(buf, "log_player%d.txt", info.real_player_id);
		log_fd = fopen(buf, "a+");
	}
	fullHp = info.HP;
	while (info.HP > 0 && info.current_battle_id != 'A') {
		if (info.battle_ended_flag == 1){
			info.HP += ((fullHp - info.HP) / 2);
			info.battle_ended_flag = 0;
		}
		while (info.battle_ended_flag != 1){
			fprintf(log_fd, "%d,%d pipe to %c,%d %d,%d,%c,%d\n", playerId, pid, targetId[playerId], pPid, info.real_player_id, info.HP, info.current_battle_id, info.battle_ended_flag);
			write(1, &info, sizeof(Status));
			read(0, &info, sizeof(Status));
			fprintf(log_fd, "%d,%d pipe from %c,%d %d,%d,%c,%d\n", playerId, pid, targetId[playerId], pPid, info.real_player_id, info.HP, info.current_battle_id, info.battle_ended_flag);
		}
	}
	if (playerId <= 7 && playerId >= 0 && info.current_battle_id != 'A') {
		info.HP = fullHp; info.battle_ended_flag = 0;
		sprintf(buf, "player%d.fifo", agentid[info.current_battle_id]);
		mkfifo(buf, 0700);
		fifoFd = open(buf, O_WRONLY);
		fprintf(log_fd, "%d,%d fifo to %d %d,%d\n", playerId, pid, agentid[info.current_battle_id], info.real_player_id, info.HP);
        write(fifoFd, &info, sizeof(Status));
	}
	fclose(log_fd);
	exit(0);
	return 0;
}