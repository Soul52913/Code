#include <unistd.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define ERR_EXIT(a) do { perror(a); exit(1); } while(0)

#define OBJ_NUM 3

#define FOOD_INDEX 0
#define CONCERT_INDEX 1
#define ELECS_INDEX 2
#define RECORD_PATH "./bookingRecord"

static char* obj_names[OBJ_NUM] = {"Food", "Concert", "Electronics"};

typedef struct {
    char hostname[512];  // server's hostname
    unsigned short port;  // port to listen
    int listen_fd;  // fd to wait for a new connection
} server;

typedef struct {
    char host[512];  // client's host
    int conn_fd;  // fd to talk with client
    char buf[512];  // data sent by/to client
    size_t buf_len;  // bytes used by buf
    int id;
    int wait_for_write;  // used by handle_read to know if the header is read or not.
} request;


server svr;  // server
request* requestP = NULL;  // point to a list of requests
int maxfd;  // size of open file descriptor table, size of request list

const char* accept_read_header = "ACCEPT_FROM_READ";
const char* accept_write_header = "ACCEPT_FROM_WRITE";
const unsigned char IAC_IP[3] = "\xff\xf4";

static void init_server(unsigned short port);
// initailize a server, exit for error

static void init_request(request* reqP);
// initailize a request instance

static void free_request(request* reqP);
// free resources used by a request instance

typedef struct {
    int id;          // 902001-902020
    int bookingState[OBJ_NUM]; // array of booking number of each object (0 or positive numbers)
}record;

int handle_read(request* reqP) {
    /*  Return value:
     *      1: read successfully
     *      0: read EOF (client down)
     *     -1: read failed
     */
    int r;
    char buf[512];

    // Read in request from client
    r = read(reqP->conn_fd, buf, sizeof(buf));
    if (r < 0) return -1;
    if (r == 0) return 0;
    char* p1 = strstr(buf, "\015\012");
    int newline_len = 2;
    if (p1 == NULL) {
       p1 = strstr(buf, "\012");
        if (p1 == NULL) {
            if (!strncmp(buf, IAC_IP, 2)) {
                // Client presses ctrl+C, regard as disconnection
                fprintf(stderr, "Client presses ctrl+C....\n");
                return 0;
            }
            ERR_EXIT("this really should not happen...");
        }
    }
    size_t len = p1 - buf + 1;
    memmove(reqP->buf, buf, len);
    reqP->buf[len - 1] = '\0';
    reqP->buf_len = len-1;
    return 1;
}

int checkID (int conn_fd){
    char validID[4] = "9020";
    for (int i = 0; i < 4; ++i){
        if (requestP[conn_fd].buf[i] != validID[i]){ 
            return 0;
        }
    }
    if (requestP[conn_fd].buf[4] > '2' || requestP[conn_fd].buf[4] < '0') return 0;
    if (requestP[conn_fd].buf[4] == '2') if (requestP[conn_fd].buf[5] != '0') return 0;
    if (requestP[conn_fd].buf[4] == '0') if (requestP[conn_fd].buf[5] > '9' || requestP[conn_fd].buf[5] < '1') return 0;
    if (requestP[conn_fd].buf[5] > '9' || requestP[conn_fd].buf[5] < '0') return 0;
    if (requestP[conn_fd].buf[6] != '\0') return 0;
    return 1;
}

int checkWrite (int conn_fd){
    int minuscheck = 0, index = 0;
    if ((requestP[conn_fd].buf[index] > '9' || requestP[conn_fd].buf[index] < '0') && requestP[conn_fd].buf[index] != '-')
        return 0;
    ++index;
    int loopone = 0;
    while (requestP[conn_fd].buf[index] != ' ' &&  requestP[conn_fd].buf[index] != '\0'){
        if (requestP[conn_fd].buf[index] > '9' || requestP[conn_fd].buf[index] < '0'){
            return 0;
        }
        if (loopone > 5) return 0;
        ++index;
        ++loopone;
    }
    ++index;
    if ((requestP[conn_fd].buf[index] > '9' || requestP[conn_fd].buf[index] < '0') && requestP[conn_fd].buf[index] != '-')
        return 0;
    ++index;
    int looptwo = 0;
    while (requestP[conn_fd].buf[index] != ' ' &&  requestP[conn_fd].buf[index] != '\0'){
        if (requestP[conn_fd].buf[index] > '9' || requestP[conn_fd].buf[index] < '0'){
            return 0;
        }
        if (looptwo > 5) return 0;
        ++index;
        ++looptwo;
    }
    ++index;
    if ((requestP[conn_fd].buf[index] > '9' || requestP[conn_fd].buf[index] < '0') && requestP[conn_fd].buf[index] != '-')
        return 0;
    ++index;
    int loopthree = 0;
    while (requestP[conn_fd].buf[index] != '\0'){
        if (requestP[conn_fd].buf[index] > '9' || requestP[conn_fd].buf[index] < '0'){
            return 0;
        }
        if (loopthree > 5) return 0;
        ++index;
        ++loopthree;
    }
    return 1;
}

int readLock(int num, int file_fd){
    struct flock lock;
    lock.l_type == F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = sizeof(record) * num;
    lock.l_len = sizeof(record);
    int check = fcntl(file_fd, F_SETLK, &lock);
    //fprintf(stderr, "%d %hd\n", file_fd, lock.l_type);
    if(check == -1){
        return -1;
    }
    else{
        return 0;
    }
}

int writeLock(int num, int file_fd){
    struct flock lock;
    lock.l_type == F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = sizeof(record) * num;
    lock.l_len = sizeof(record);
    int check = fcntl(file_fd, F_SETLK, &lock);
    //fprintf(stderr, "%d %hd\n", file_fd, lock.l_type);
    if(check == -1){
        return -1;
    }
    else{
        return 0;
    }
}

int Unlock(int num, int file_fd){
    struct flock lock;
    lock.l_type == F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = sizeof(record) * num;
    lock.l_len = sizeof(record);
    int check = fcntl(file_fd, F_SETLK, &lock);
    if(check == -1){
        return -1;
    }
    else{
        return 0;
    }
}

int main(int argc, char** argv) {

    // Parse args.
    if (argc != 2) {
        fprintf(stderr, "usage: %s [port]\n", argv[0]);
        exit(1);
    }

    struct sockaddr_in cliaddr;  // used by accept()
    int clilen;

    int conn_fd;  // fd for a new connection with client
    int file_fd;  // fd for file that we open for reading
    char buf[512];
    int buf_len;
    int fdCount = 0;
    int num = 0;
    // Initialize server
    init_server((unsigned short) atoi(argv[1]));
    file_fd = open(RECORD_PATH, O_RDWR);
    int phase[maxfd + 5];
    int id_read[20] = {0};
    int id_write[20] = {0};
    for(int i = 0; i <= maxfd + 4; ++i) phase[i] = 0;
    struct pollfd pfds[maxfd + 5];
    int rret;
    for (int i = 0; i <= maxfd; ++i) {
        pfds[i].fd = -1;
        pfds[i].events = POLLIN;
    }
    pfds[0].fd = svr.listen_fd;
    pfds[0].events = POLLIN;

    // Loop for handling connections
    fprintf(stderr, "\nstarting on %.80s, port %d, fd %d, maxconn %d...\n", svr.hostname, svr.port, svr.listen_fd, maxfd);

    while (1) {
        // TODO: Add IO multiplexing
        rret = poll(pfds, maxfd, 60);
        if (rret == -1) {
            perror("poll");
            exit(-1);
        }
        if (rret == 0) continue;
        if (pfds[0].revents & POLLIN) {
            // Check new connection
            clilen = sizeof(cliaddr);
            conn_fd = accept(svr.listen_fd, (struct sockaddr*)&cliaddr, (socklen_t*)&clilen);
            if (conn_fd < 0) {
                if (errno == EINTR || errno == EAGAIN) continue;  // try again
                if (errno == ENFILE) {
                    (void) fprintf(stderr, "out of file descriptor table ... (maxconn %d)\n", maxfd);
                    continue;
                }
                ERR_EXIT("accept");
            }
            pfds[conn_fd].fd = conn_fd;
            pfds[conn_fd].events = POLLIN;
            requestP[conn_fd].conn_fd = conn_fd;
            strcpy(requestP[conn_fd].host, inet_ntoa(cliaddr.sin_addr));
            fprintf(stderr, "getting a new request... fd %d from %s\n", conn_fd, requestP[conn_fd].host);
            write (conn_fd, "Please enter your id (to check your booking state):\n", 53);
            --rret;
        }
        for (int i = 1; i <= maxfd + 5 && rret > 0; ++i) { 
            if (pfds[i].revents & POLLIN) {
                conn_fd = pfds[i].fd; //fprintf(stderr, "%d\n", conn_fd);
                char output[512];
                record recordData;
                if (phase[conn_fd] == 0) {
                    int ret = handle_read(&requestP[conn_fd]); // parse data from client to requestP[conn_fd].buf
                    fprintf(stderr, "ret = %d\n", ret);
                    if (ret < 0) {
                        fprintf(stderr, "bad request from %s\n", requestP[conn_fd].host);
                        continue;
                    }
                    // TODO: handle requests from clients
                    
                    if (checkID(conn_fd) == 1) {
                        sscanf(requestP[conn_fd].buf, "%d", &requestP[conn_fd].id);
                        num = requestP[conn_fd].id - 902001;
        #ifdef READ_SERVER
                        fprintf(stderr, "%d\n", num);
                        int rlockre = readLock(num, file_fd);
                        if (rlockre == -1 || id_write[num] == 1) {
                            write(conn_fd, "Locked.\n", 9);
                            pfds[conn_fd].fd = -1, phase[conn_fd] = 0;
                            close(requestP[conn_fd].conn_fd);
                            free_request(&requestP[conn_fd]);
                        }
                        else if (rlockre == 0 && id_write[num] == 0){
                            ++id_read[num];
                            lseek(file_fd, sizeof(record) * num, SEEK_SET);
                            read(file_fd, &recordData, sizeof(record));
                            sprintf(output, "Food: %d booked\nConcert: %d booked\nElectronics: %d booked\n\n(Type Exit to leave...)\n"
                                , recordData.bookingState[0], recordData.bookingState[1], recordData.bookingState[2]);
                            write(conn_fd, output, strlen(output));
                            phase[conn_fd] = 1;
                        }
                    }
                    else{
                        write (conn_fd, "[Error] Operation failed. Please try again.\n", 45);
                        pfds[conn_fd].fd = -1, phase[conn_fd] = 0;
                        close(requestP[conn_fd].conn_fd);
                        free_request(&requestP[conn_fd]);
                    }
                }
                else if(phase[conn_fd] == 1){    
                    int ret = handle_read(&requestP[conn_fd]);
                    if (ret < 0) {
                        fprintf(stderr, "bad request from %s\n", requestP[conn_fd].host);
                        continue;
                    }
                    if (strcmp(requestP[conn_fd].buf, "Exit") == 0) {
                        num = requestP[conn_fd].id - 902001;
                        --id_read[num];
                        if (id_read[num] == 0){
                            Unlock(num, file_fd);
                        }
                        pfds[conn_fd].fd = -1, phase[conn_fd] = 0;
                        close(requestP[conn_fd].conn_fd);
                        free_request(&requestP[conn_fd]);
                    }
                }
        #elif defined WRITE_SERVER
                        int wlockre = writeLock(num, file_fd);
                        if (wlockre == -1 || id_read[num] != 0 || id_write[num] == 1) {
                            write(conn_fd, "Locked.\n", 9);
                            pfds[conn_fd].fd = -1, phase[conn_fd] = 0;
                            close(requestP[conn_fd].conn_fd);
                            free_request(&requestP[conn_fd]);
                        }
                        else if (wlockre == 0 && id_read[num] == 0 && id_write[num] == 0){
                            id_write[num] = 1;
                            lseek(file_fd, sizeof(record) * num, SEEK_SET);
                            read(file_fd, &recordData, sizeof(record));
                            sprintf(output, "Food: %d booked\nConcert: %d booked\nElectronics: %d booked\n\nPlease input your booking command. (Food, Concert, Electronics. Positive/negative value increases/decreases the booking amount.):\n"
                                , recordData.bookingState[0], recordData.bookingState[1], recordData.bookingState[2]);
                            write(conn_fd, output, strlen(output));
                            phase[conn_fd] = 1;
                        }
                    }
                    else{
                        write (conn_fd, "[Error] Operation failed. Please try again.\n", 45);
                        pfds[conn_fd].fd = -1, phase[conn_fd] = 0;
                        close(requestP[conn_fd].conn_fd);
                        free_request(&requestP[conn_fd]);
                    }
                }
                else if(phase[conn_fd] == 1){
                    int ret = handle_read(&requestP[conn_fd]);
                    if (ret < 0) {
                        fprintf(stderr, "bad request from %s\n", requestP[conn_fd].host);
                        continue;
                    }
                    num = requestP[conn_fd].id - 902001; 
                    lseek(file_fd, sizeof(record) * num, SEEK_SET);
                    read(file_fd, &recordData, sizeof(record));
                    int preF = recordData.bookingState[0], preC = recordData.bookingState[1], preE = recordData.bookingState[2]; 
                    if (checkWrite(conn_fd) == 1) {
                        int F, C, E;
                        sscanf(requestP[conn_fd].buf, "%d %d %d", &F, &C, &E);
                        if (F + preF < 0 || C + preC < 0|| E + preE < 0) 
                            write (conn_fd, "[Error] Sorry, but you cannot book less than 0 items.\n", 55);
                        else if (F + preF + C + preC + E + preE > 15) 
                            write (conn_fd, "[Error] Sorry, but you cannot book more than 15 items in total.\n", 65);
                        else {
                            recordData.bookingState[0] = F + preF, recordData.bookingState[1] = C + preC, recordData.bookingState[2] = E + preE;
                            sprintf(output, "Bookings for user %d are updated, the new booking state is:\nFood: %d booked\nConcert: %d booked\nElectronics: %d booked\n"
                            , requestP[conn_fd].id, recordData.bookingState[0], recordData.bookingState[1], recordData.bookingState[2]);
                            write(conn_fd, output, strlen(output));
                            lseek(file_fd, sizeof(record) * num, SEEK_SET);
                            write(file_fd, &recordData, sizeof(record));
                        }
                    }
                    else {
                        write (conn_fd, "[Error] Operation failed. Please try again.\n", 45);
                    }
                    Unlock(num, file_fd); id_write[num] = 0;
                    pfds[conn_fd].fd = -1, phase[conn_fd] = 0;
                    close(requestP[conn_fd].conn_fd);
                    free_request(&requestP[conn_fd]);
                }
        #endif
                --rret;
            }
        }
    }
    close(file_fd);
    free(requestP);
    return 0;
}

// ======================================================================================================
// You don't need to know how the following codes are working
#include <fcntl.h>

static void init_request(request* reqP) {
    reqP->conn_fd = -1;
    reqP->buf_len = 0;
    reqP->id = 0;
}

static void free_request(request* reqP) {
    /*if (reqP->filename != NULL) {
        free(reqP->filename);
        reqP->filename = NULL;
    }*/
    init_request(reqP);
}

static void init_server(unsigned short port) {
    struct sockaddr_in servaddr;
    int tmp;

    gethostname(svr.hostname, sizeof(svr.hostname));
    svr.port = port;

    svr.listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (svr.listen_fd < 0) ERR_EXIT("socket");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    tmp = 1;
    if (setsockopt(svr.listen_fd, SOL_SOCKET, SO_REUSEADDR, (void*)&tmp, sizeof(tmp)) < 0) {
        ERR_EXIT("setsockopt");
    }
    if (bind(svr.listen_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        ERR_EXIT("bind");
    }
    if (listen(svr.listen_fd, 1024) < 0) {
        ERR_EXIT("listen");
    }

    // Get file descripter table size and initialize request table
    maxfd = getdtablesize();
    requestP = (request*) malloc(sizeof(request) * maxfd);
    if (requestP == NULL) {
        ERR_EXIT("out of memory allocating all requests");
    }
    for (int i = 0; i < maxfd; i++) {
        init_request(&requestP[i]);
    }
    requestP[svr.listen_fd].conn_fd = svr.listen_fd;
    strcpy(requestP[svr.listen_fd].host, svr.hostname);

    return;
}