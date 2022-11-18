#include "status.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, char **argv) {
	FILE * file_fd, * log_fd;
	Status pone, ptwo;
	char buf[512], bbuf[512];
	int child[14][2] = {{-1, -1}, {-1, -1}, {14, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {0, 1}, {2, 3}, {4, 5}, {6, 7}, {10, -1}, {13, -1}, {8, 9}, {11, 12}};
	char parent[14] = {'', 'A', 'A', 'B', 'B', 'C', 'D', 'D', 'E', 'E',, 'F', 'F', 'K', 'L'};
	int child[14] = {7, };
	Attribute[14] = {FIRE, GRASS, WATER, WATER, FIRE, FIRE, FIRE, GRASS, WATER, GRASS, GRASS, GRASS, FIRE, WATER}
	int agentid[128];
	char battleId = atoi(argv[1]);
	int pPid = atoi(argv[2]);
	pid_t pid = getpid(), cpid;
	sprintf(buf, "log_battle%d.txt", battleId);
	log_fd = fopen(buf, "a+");
	int pone_pipeIN[2], pone_pipeOUT[2], ptwo_pipeIN[2], ptwo_pipeOUT[2];
	if(pipe(pone_pipeIN) < 0)	return -1;
	if(pipe(pone_pipeOUT) < 0)	return -1;
	if(pipe(ptwo_pipeIN) < 0)	return -1;
	if(pipe(ptwo_pipeOUT) < 0)	return -1;
	for (int i = 0; i < 2; ++i){
		if((cpid = fork()) == 0) {
			pid_t ccpid;
			if((ccpid = fork()) == 0) {
				if (i == 0){
					dup2(pone_pipeIN[0].fd, 1);
					close(pone_pipeIN[1]);
					dup2(0, pone_pipeOUT[1].fd);
					close(pone_pipeOUT[0]);
					if (child[battleId - 'A'][i] != -1){
						sprintf(buf, "%c", battleId);
						sprintf(bbuf, "%d", pid);
						execlp("./battle", "battle", buf, bbuf, NULL);
					}
					else{
						sprintf(buf, "%c", battleId);
						sprintf(bbuf, "%d", pid);
						execlp("./player", "player", buf, bbuf, NULL);
					}
				}
				else{
					dup2(ptwo_pipeIN[0].fd, 1);
					close(ptwo_pipeIN[1]);
					dup2(0, ptwo_pipeOUT[1].fd);
					close(ptwo_pipeOUT[0]);
					if (child[battleId - 'A'][i] != -1){
						execlp("./battle", "battle", "A", "0", NULL);
					}
					else{
						execlp("./player", "player", "A", "0", NULL);
					}
				}
			}
			else{
				exit(0);
			}
		}
		else if (cpid > 0){
		}
	}
	fprintf(log_fd, "%c,%d pipe to %c,%d %d,%d,%c,%d\n", battleId, pid, targetId[playerId], pPid, pone.real_player_id, pone.HP, pone.current_battle_id, pone.battle_ended_flag);
			write(1, &info, sizeof(Status));
			read(0, &info, sizeof(Status));
			fprintf(log_fd, "%d,%d pipe from %c,%d %d,%d,%c,%d\n", playerId, pid, targetId[playerId], pPid, info.real_player_id, info.HP, info.current_battle_id, info.battle_ended_flag);
	read(pone_pipeIN[1].fd, &pone, sizeof(Status));
	read(ptwo_pipeIN[1].fd, &ptwo, sizeof(Status));
	while (pone.HP > 0 && ptwo.HP > 0){
		
	}
	exit(0);
	return 0;
}