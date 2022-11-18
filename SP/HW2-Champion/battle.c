#include "status.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main (int argc, char **argv) {
	Status pone, ptwo;
	int log_fd = -1;
	char buf[512], bbuf[512], linebuf[2048];;
	int playerchild[14][2] = {{-1, -1}, {-1, -1}, {-1, 14}, {-1, -1}, {-1, -1}, {-1, -1}, {0, 1}, {2, 3}, {4, 5}, {6, 7}, {-1, 10}, {-1, 13}, {8, 9}, {11, 12}};
	char battlechild[14][2] = {{'B', 'C'}, {'D', 'E'}, {'F', '\0'}, {'G', 'H'}, {'I', 'J'}, {'K', 'L'}, {'\0', '\0'}, {'\0', '\0'}, {'\0', '\0'}, {'\0', '\0'}, {'M', '\0'}, {'N', '\0'}, {'\0', '\0'}, {'\0', '\0'}};
	char parent[14] = {' ', 'A', 'A', 'B', 'B', 'C', 'D', 'D', 'E', 'E', 'F', 'F', 'K', 'L'};
	Attribute battleAttr[14] = {FIRE, GRASS, WATER, WATER, FIRE, FIRE, FIRE, GRASS, WATER, GRASS, GRASS, GRASS, FIRE, WATER};
	char battleId = argv[1][0];
	int pPid = atoi(argv[2]);
	pid_t pid = getpid(), cpid, ccpid, onepid, twopid;
	sprintf(buf, "log_battle%c.txt", battleId);
	log_fd = open(buf, O_CREAT | O_WRONLY | O_APPEND, 0777);
	int pone_pipeIN[2], pone_pipeOUT[2], ptwo_pipeIN[2], ptwo_pipeOUT[2];
	int passPid = 0;
	int passIN = -1; int passOUT = -1;
	if(pipe(pone_pipeIN) < 0)	return -1;
	if(pipe(pone_pipeOUT) < 0)	return -1;
	if(pipe(ptwo_pipeIN) < 0)	return -1;
	if(pipe(ptwo_pipeOUT) < 0)	return -1;
	if((onepid = fork()) == 0) {
		dup2(pone_pipeIN[1], 1);
		close(pone_pipeIN[0]);
		close(pone_pipeIN[1]);
		dup2(pone_pipeOUT[0], 0);
		close(pone_pipeOUT[0]);
		close(pone_pipeOUT[1]);
		close(ptwo_pipeIN[0]);
		close(ptwo_pipeIN[1]);
		close(ptwo_pipeOUT[0]);
		close(ptwo_pipeOUT[1]);
		if (playerchild[battleId - 'A'][0] == -1){
			sprintf(buf, "%c", battlechild[battleId - 'A'][0]);
			sprintf(bbuf, "%d", pid);
			execlp("./battle", "battle", buf, bbuf, NULL);
		}
		else{
			sprintf(buf, "%d", playerchild[battleId - 'A'][0]);
			sprintf(bbuf, "%d", pid);
			execlp("./player", "player", buf, bbuf, NULL);
		}
	}
	else if (onepid > 0){
		close(pone_pipeIN[1]);
		close(pone_pipeOUT[0]);
	}
	if((twopid = fork()) == 0) {
		close(pone_pipeIN[0]);
		close(pone_pipeIN[1]);
		close(pone_pipeOUT[0]);
		close(pone_pipeOUT[1]);
		dup2(ptwo_pipeIN[1], 1);
		close(ptwo_pipeIN[0]);
		close(ptwo_pipeIN[1]);
		dup2(ptwo_pipeOUT[0], 0);
		close(ptwo_pipeOUT[0]);
		close(ptwo_pipeOUT[1]);
		if (playerchild[battleId - 'A'][1] == -1){
			sprintf(buf, "%c", battlechild[battleId - 'A'][1]);
			sprintf(bbuf, "%d", pid);
			execlp("./battle", "battle", buf, bbuf, NULL);
		}
		else{
			sprintf(buf, "%d", playerchild[battleId - 'A'][1]);
			sprintf(bbuf, "%d", pid);
			execlp("./player", "player", buf, bbuf, NULL);
		}
	}
	else if (twopid > 0){
		close(ptwo_pipeIN[1]);
		close(ptwo_pipeOUT[0]);
	}
	if (playerchild[battleId - 'A'][0] == -1)
		sprintf(buf, "%c", battlechild[battleId - 'A'][0]);
	else
		sprintf(buf, "%d", playerchild[battleId - 'A'][0]);
	if (playerchild[battleId - 'A'][1] == -1)
		sprintf(bbuf, "%c", battlechild[battleId - 'A'][1]);
	else
		sprintf(bbuf, "%d", playerchild[battleId - 'A'][1]);
	
	Status *first; Status *second;
	
	while (1){
		read(pone_pipeIN[0], &pone, sizeof(Status));
		sprintf(linebuf, "%c,%d pipe from %s,%d %d,%d,%c,%d\n", battleId, pid, buf, onepid, pone.real_player_id, pone.HP, pone.current_battle_id, pone.battle_ended_flag);
		write(log_fd, linebuf, strlen(linebuf));
		read(ptwo_pipeIN[0], &ptwo, sizeof(Status));
		sprintf(linebuf, "%c,%d pipe from %s,%d %d,%d,%c,%d\n", battleId, pid, bbuf, twopid, ptwo.real_player_id, ptwo.HP, ptwo.current_battle_id, ptwo.battle_ended_flag);
		write(log_fd, linebuf, strlen(linebuf));
		if (pone.HP < ptwo.HP)
			first = &pone, second = &ptwo;
		else if (pone.HP == ptwo.HP){
			if (pone.real_player_id < ptwo.real_player_id)
				first = &pone, second = &ptwo;
			else
				first = &ptwo, second = &pone;
		}
		else
			first = &ptwo, second = &pone;
		first->current_battle_id = battleId, second->current_battle_id = battleId;
		int fAtk = first->ATK, sAtk = second->ATK;
		if (first->attr == battleAttr[battleId - 'A'])
			fAtk *= 2;
		if (second->attr == battleAttr[battleId - 'A'])
			sAtk *= 2;
		second->HP -= fAtk;
		if (second->HP <= 0){
			if (battleId == 'A'){
				printf("Champion is P%d\n", first->real_player_id);
			}
			break;
		}
		first->HP -= sAtk;
		if (first->HP <= 0){
			if (battleId == 'A'){
				printf("Champion is P%d\n", second->real_player_id);
			}
			break;
		}
		write(pone_pipeOUT[1], &pone, sizeof(Status));
		sprintf(linebuf, "%c,%d pipe to %s,%d %d,%d,%c,%d\n", battleId, pid, buf, onepid, pone.real_player_id, pone.HP, pone.current_battle_id, pone.battle_ended_flag);
		write(log_fd, linebuf, strlen(linebuf));
		write(ptwo_pipeOUT[1], &ptwo, sizeof(Status));
		sprintf(linebuf, "%c,%d pipe to %s,%d %d,%d,%c,%d\n", battleId, pid, bbuf, twopid, ptwo.real_player_id, ptwo.HP, ptwo.current_battle_id, ptwo.battle_ended_flag);
		write(log_fd, linebuf, strlen(linebuf));
	}
	pone.battle_ended_flag = 1, ptwo.battle_ended_flag = 1;
	write(pone_pipeOUT[1], &pone, sizeof(Status));
	sprintf(linebuf, "%c,%d pipe to %s,%d %d,%d,%c,%d\n", battleId, pid, buf, onepid, pone.real_player_id, pone.HP, pone.current_battle_id, pone.battle_ended_flag);
	write(log_fd, linebuf, strlen(linebuf));
	write(ptwo_pipeOUT[1], &ptwo, sizeof(Status));
	sprintf(linebuf, "%c,%d pipe to %s,%d %d,%d,%c,%d\n", battleId, pid, bbuf, twopid, ptwo.real_player_id, ptwo.HP, ptwo.current_battle_id, ptwo.battle_ended_flag);
	write(log_fd, linebuf, strlen(linebuf));
	int left, right;
	if (pone.HP <= 0) {
		wait(&left);
		if (playerchild[battleId - 'A'][1] == -1)
			sprintf(buf, "%c", battlechild[battleId - 'A'][1]);
		else
			sprintf(buf, "%d", playerchild[battleId - 'A'][1]);
		passIN = ptwo_pipeIN[0];
		passOUT = ptwo_pipeOUT[1];
		passPid = twopid;
	}
	else if (ptwo.HP <= 0) {
		wait(&right);
		if (playerchild[battleId - 'A'][0] == -1)
			sprintf(buf, "%c", battlechild[battleId - 'A'][0]);
		else
			sprintf(buf, "%d", playerchild[battleId - 'A'][0]);
		passIN = pone_pipeIN[0];
		passOUT = pone_pipeOUT[1];
		passPid = onepid;
	}
	int win;
	if (battleId != 'A'){
		Status pass;
		read(passIN, &pass, sizeof(Status));
		sprintf(linebuf, "%c,%d pipe from %s,%d %d,%d,%c,%d\n", battleId, pid, buf, passPid, pass.real_player_id, pass.HP, pass.current_battle_id, pass.battle_ended_flag);
		write(log_fd, linebuf, strlen(linebuf));
		int check = 0;
		while(pass.HP > 0){
			if (pass.current_battle_id == 'A' && pass.battle_ended_flag == 1) break;
			if (check != 0){
				read(passIN, &pass, sizeof(Status));
				sprintf(linebuf, "%c,%d pipe from %s,%d %d,%d,%c,%d\n", battleId, pid, buf, passPid, pass.real_player_id, pass.HP, pass.current_battle_id, pass.battle_ended_flag);
				write(log_fd, linebuf, strlen(linebuf));
			}
			else if (check == 0){
				check = 1;
			}
			sprintf(linebuf, "%c,%d pipe to %c,%d %d,%d,%c,%d\n", battleId, pid, parent[battleId - 'A'], pPid, pass.real_player_id, pass.HP, pass.current_battle_id, pass.battle_ended_flag);
			write(log_fd, linebuf, strlen(linebuf));
			write(STDOUT_FILENO, &pass, sizeof(Status));
			read(STDIN_FILENO, &pass, sizeof(Status));
			sprintf(linebuf, "%c,%d pipe from %c,%d %d,%d,%c,%d\n", battleId, pid, parent[battleId - 'A'], pPid, pass.real_player_id, pass.HP, pass.current_battle_id, pass.battle_ended_flag);
			write(log_fd, linebuf, strlen(linebuf));
			sprintf(linebuf, "%c,%d pipe to %s,%d %d,%d,%c,%d\n", battleId, pid, buf, passPid, pass.real_player_id, pass.HP, pass.current_battle_id, pass.battle_ended_flag);
			write(log_fd, linebuf, strlen(linebuf));
			write(passOUT, &pass, sizeof(Status));
		}
	}
	wait(&win);
	close(log_fd);
	exit(0);
}