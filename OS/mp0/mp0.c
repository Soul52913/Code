#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int countkey (char *path, char key) {
    int count = 0;
    while (*path != '\0') {
        if (*path == key) ++count;
        ++path;
    }
    return count;
}

void mp0(char *path, char key, int *dirNum, int *fileNum){
    char buf[512], *p;
    int fd, keyNum = 0;
    struct dirent de;
    struct stat st;
    if((fd = open(path, 0)) < 0) return;
    if(fstat(fd, &st) < 0){
        close(fd);
        return;
    }
    switch(st.type){
    case T_FILE:
        *fileNum += 1;
        keyNum = countkey(path, key);
        printf("%s %d\n", path, keyNum);
        break;
    case T_DIR:
        *dirNum += 1;
        if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
            close(fd);
            break;
        }
        strcpy(buf, path);
        keyNum = countkey(buf, key);
        printf("%s %d\n", buf, keyNum);
        p = buf+strlen(buf);
        *p++ = '/';
        while(read(fd, &de, sizeof(de)) == sizeof(de)){
            if(de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
                continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            mp0(buf, key, dirNum, fileNum);
        }
        break;
    }
    close(fd);
    return;
}

int main (int argc, char *argv[]) {
    if (argc > 3) return -1;
    char key, path[32], ans[64] = "\0";
    strcpy(path, argv[1]);
    key = argv[2][0];
    int pipeP[2], dirNum = 0, fileNum = 0;
    if (pipe(pipeP) < 0) return -1;
    if (fork() == 0) {
        close(pipeP[0]);
        char buf[512], *p;
        int fd;
        struct dirent de;
        struct stat st;
        if((fd = open(path, 0)) < 0) {
            fprintf(pipeP[1], "%s [error opening dir]\n\n0 directories, 0 files\n", path);
            close(pipeP[1]);
            exit(0);
        }
        if(fstat(fd, &st) < 0){
            fprintf(pipeP[1], "%s [error opening dir]\n\n0 directories, 0 files\n", path);
            close(pipeP[1]);
            close(fd);
            exit(0);
        }
        switch(st.type){
            case T_FILE:
                fprintf(pipeP[1], "%s [error opening dir]\n\n0 directories, 0 files\n", path);
                close(fd);
                break;
            case T_DIR:
                if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
                    fprintf(pipeP[1], "%s [error opening dir]\n\n0 directories, 0 files\n", path);
                    close(fd);
                    break;
                }
                strcpy(buf, path);
                int keyNum = countkey(buf, key);
                printf("%s %d\n", buf, keyNum);
                p = buf+strlen(buf);
                *p++ = '/';
                while(read(fd, &de, sizeof(de)) == sizeof(de)){
                    if(de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
                        continue;
                    memmove(p, de.name, DIRSIZ);
                    p[DIRSIZ] = 0;
                    mp0(buf, key, &dirNum, &fileNum);
                }
                fprintf(pipeP[1], "\n%d directories, %d files\n", dirNum, fileNum);
                break;
        }
        close(pipeP[1]);
        exit(0);
    }
    else {
        wait(0);
        close(pipeP[1]);
        read(pipeP[0], &ans, sizeof(ans));
        printf("%s", ans);
        close(pipeP[0]);
    }
    exit(0);
}