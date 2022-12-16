#include "header.h"

movie_profile* movies[MAX_MOVIES];
unsigned int num_of_movies = 0;
unsigned int num_of_reqs = 0;
unsigned int num_of_usage = 0;
unsigned int limitSize = 1948;
unsigned int Plimit = 124;

// Global request queue and pointer to front of queue
// TODO: critical section to protect the global resources
request* reqs[MAX_REQ];
result* results[MAX_REQ];
result* presults;

/* Note that the maximum number of processes per workstation user is 512. * 
 * We recommend that using about <256 threads is enough in this homework. */
pthread_t tid[MAX_CPU][MAX_THREAD]; //tids for multithread

#ifdef PROCESS
pid_t pid[MAX_CPU][MAX_THREAD]; //pids for multiprocess
#endif

//mutex
pthread_mutex_t lock; 
/*int pop();
int pop(){
	front+=1;
	return front;
}*/

void initialize(FILE* fp);
request* read_request();


void merge(int index, int l, int m, int r) {
	/*for (int i = l; i <= r; ++i){
		fprintf(stderr, "%lf %s\n", results[index]->profile[i], results[index]->title[i]);
	}
		fprintf(stderr, "a\n");*/
    int left_i = 0, right_i = 0, arr_i = l;
    int lSize = m - l + 1;
    int rSize = r - m;
    double *L; L = (double *)malloc(sizeof(double) * lSize);
	double *R; R = (double *)malloc(sizeof(double) * rSize);
	char **Ltitle; Ltitle = (char **)malloc(sizeof(char *) * lSize);
	char **Rtitle; Rtitle = (char **)malloc(sizeof(char *) * rSize);
    for (int i = 0; i < lSize; ++i) {
        L[i] = results[index]->profile[l + i];
		Ltitle[i] = results[index]->title[l + i];
	}
    for (int i = 0; i < rSize; ++i) {
        R[i] = results[index]->profile[m + 1 + i];
		Rtitle[i] = results[index]->title[m + 1 + i];
	}
	if (lSize <= limitSize) {
		sort(Ltitle, L, lSize);
	}
	if (rSize <= limitSize) {
		sort(Rtitle, R, rSize);
	}
    while (left_i < lSize && right_i < rSize) {
        if (L[left_i] > R[right_i]) {
            results[index]->profile[arr_i] = L[left_i];
			results[index]->title[arr_i] = Ltitle[left_i];
            ++left_i;
        }
		else if (L[left_i] == R[right_i]) {
			if (strcmp(Ltitle[left_i], Rtitle[right_i]) > 0) {
				results[index]->profile[arr_i] = R[right_i];
				results[index]->title[arr_i] = Rtitle[right_i];
				++right_i;
			}
			else {
				results[index]->profile[arr_i] = L[left_i];
				results[index]->title[arr_i] = Ltitle[left_i];
				++left_i;
			}
		}
        else {
            results[index]->profile[arr_i] = R[right_i];
			results[index]->title[arr_i] = Rtitle[right_i];
            ++right_i;
        }
        ++arr_i;
    }
    while (left_i < lSize) {
        results[index]->profile[arr_i] = L[left_i];
		results[index]->title[arr_i] = Ltitle[left_i];
        ++left_i;
        ++arr_i;
    }
    while (right_i < rSize) {
        results[index]->profile[arr_i] = R[right_i];
		results[index]->title[arr_i] = Rtitle[right_i];
        ++right_i;
        ++arr_i;
    }
	/*for (int i = l; i <= r; ++i){
		fprintf(stderr, "%lf %s\n", results[index]->profile[i], results[index]->title[i]);
	}
		fprintf(stderr, "\n");*/
	return;
}

void * tmergeSort(void *arg) {
	int *input = (int *) arg;
	int index = input[0], l = input[1], r = input[2];
	//fprintf(stderr, "%d %d %d\n", index, l, r);
	int *ainput = (int *)malloc(sizeof(int) * 3);
	int *binput = (int *)malloc(sizeof(int) * 3);
    if (l < r) {
        int m = l + (r - l) / 2;
		pthread_t a, b;
		if (m - l + 1 > limitSize) {
			ainput[0] = index, ainput[1] = l, ainput[2] = m;
			pthread_create(&a, NULL, tmergeSort, (void*) ainput);
			tid[index][results[index]->threadUsed] = a;
			++results[index]->threadUsed;
		}
		if (r - m > limitSize) {
			binput[0] = index, binput[1] = m + 1, binput[2] = r;
			pthread_create(&b, NULL, tmergeSort, (void*) binput);
			tid[index][results[index]->threadUsed] = b;
			++results[index]->threadUsed;
		}
		if (m - l + 1 > limitSize)
			pthread_join(a, NULL);
		if (r - m > limitSize)
			pthread_join(b, NULL);
        merge(index, l, m, r);
    }
	////perror("tmerge");
}

void mergeSort(int index, int l, int r){
	//printf("in\n");
    if (l < r) {
        int m = l + (r - l) / 2;
		pthread_t a, b;
		//fprintf(stderr, "%d %d %d\n", l, m, r);
		int *ainput = (int *)malloc(sizeof(int) * 3);
		int *binput = (int *)malloc(sizeof(int) * 3);
		if (m - l + 1 > limitSize) {
			ainput[0] = index, ainput[1] = l, ainput[2] = m;
			pthread_create(&a, NULL, tmergeSort, (void*) ainput);
			tid[index][results[index]->threadUsed] = a;
			++results[index]->threadUsed;
		}
		////perror("aa");
		if (r - m > limitSize) {
			binput[0] = index, binput[1] = m + 1, binput[2] = r;
			pthread_create(&b, NULL, tmergeSort, (void*) binput);
			tid[index][results[index]->threadUsed] = b;
			++results[index]->threadUsed;
		}
		////perror("bb");
		if (m - l + 1 > limitSize)
			pthread_join(a, NULL);
		if (r - m > limitSize)
			pthread_join(b, NULL);
        merge(index, l, m, r);
    }
	else if (l == r) {
		double *K; K = (double *)malloc(sizeof(double));
		char **Ktitle; Ktitle = (char **)malloc(sizeof(char *));
        K[0] = results[index]->profile[0];
		Ktitle[0] = results[index]->title[0];
		sort(Ktitle, K, 1);
        results[index]->profile[0] = K[0];
		results[index]->title[0] = Ktitle[0];
    }
	////perror("merge");
	return;
}

void *threadProg(void *arg) {
	int index = *(int *) arg;
	int filterNum = 0;
	result temp;
	if (reqs[index]->keywords[0] == '*'){
		filterNum = num_of_movies;
		temp.threadUsed = 1;
		temp.profile = (double *)malloc(sizeof(double) * filterNum);
		temp.title = (char **)malloc(sizeof(char *) * filterNum);
		for (int i = 0; i < filterNum; ++i){
			temp.title[i] = movies[i]->title;
			temp.profile[i] = 0;
			for (int k = 0; k < NUM_OF_GENRE; ++k){
				temp.profile[i] += (movies[i]->profile[k] * reqs[index]->profile[k]);
			}
		}
		filterNum = num_of_movies;
	}
	else{
		for(int i = 0; i < num_of_movies; ++i){
			if (strstr(movies[i]->title, reqs[index]->keywords)){
				++filterNum;
			}
		}
		temp.profile = (double *)malloc(sizeof(double) * filterNum);
		temp.title = (char **)malloc(sizeof(char *) * filterNum);
		//perror("malloc");
		for(int i = 0, count = 0; i < num_of_movies; ++i){
			if (strstr(movies[i]->title, reqs[index]->keywords)){
				temp.title[count] = movies[i]->title;
				temp.profile[count] = 0;
				for (int k = 0; k < NUM_OF_GENRE; ++k){
					temp.profile[count] += (movies[i]->profile[k] * reqs[index]->profile[k]);
				}
				++count;
			}
		}
		//pthread_mutex_lock(&lock);
	}
	//perror("filter");
	temp.threadUsed = 1;
	results[index] = &temp;
	mergeSort(index, 0, filterNum - 1);
	//perror("mergeSort");
	char buf[126];
	sprintf(buf, "%dt.out", reqs[index]->id);
	FILE *fpwrite;
	if ((fpwrite = fopen(buf, "w+")) == NULL){
		ERR_EXIT("fopen");
	}
	for (int i = 0; i < filterNum; ++i){
		fprintf(fpwrite, "%s\n", results[index]->title[i]);
	}
	//perror("fwrite");
	fclose(fpwrite);
}

void pmerge(int l, int m, int r) {
	/*for (int i = l; i <= r; ++i){
		fprintf(stderr, "%lf %s\n", results[index]->profile[i], results[index]->title[i]);
	}
		fprintf(stderr, "a\n");*/
	int index = 0;
    int left_i = 0, right_i = 0, arr_i = l;
    int lSize = m - l + 1;
    int rSize = r - m;
    double *L; L = (double *)malloc(sizeof(double) * lSize);
	double *R; R = (double *)malloc(sizeof(double) * rSize);
	char **Ltitle; Ltitle = (char **)malloc(sizeof(char *) * lSize);
	char **Rtitle; Rtitle = (char **)malloc(sizeof(char *) * rSize);
    for (int i = 0; i < lSize; ++i) {
		Ltitle[i] = (char *)malloc(sizeof(char) * MAX_LEN);
		strcpy(Ltitle[i], presults->title[l + i]);
        L[i] = presults->profile[l + i];
	}
    for (int i = 0; i < rSize; ++i) {
        Rtitle[i] = (char *)malloc(sizeof(char) * MAX_LEN);
		strcpy(Rtitle[i], presults->title[m + 1 + i]);
        R[i] = presults->profile[m + 1 + i];
	}
	if (lSize <= Plimit) {
		sort(Ltitle, L, lSize);
	}
	if (rSize <= Plimit) {
		sort(Rtitle, R, rSize);
	}
    while (left_i < lSize && right_i < rSize) {
        if (L[left_i] > R[right_i]) {
            presults->profile[arr_i] = L[left_i];
			strcpy(presults->title[arr_i], Ltitle[left_i]);
            ++left_i;
        }
		else if (L[left_i] == R[right_i]) {
			if (strcmp(Ltitle[left_i], Rtitle[right_i]) > 0) {
				presults->profile[arr_i] = R[right_i];
				strcpy(presults->title[arr_i], Rtitle[right_i]);
				++right_i;
			}
			else {
				presults->profile[arr_i] = L[left_i];
				strcpy(presults->title[arr_i], Ltitle[left_i]);
				++left_i;
			}
		}
        else {
            presults->profile[arr_i] = R[right_i];
			strcpy(presults->title[arr_i], Rtitle[right_i]);
            ++right_i;
        }
        ++arr_i;
    }
    while (left_i < lSize) {
        presults->profile[arr_i] = L[left_i];
		strcpy(presults->title[arr_i], Ltitle[left_i]);
        ++left_i;
        ++arr_i;
    }
    while (right_i < rSize) {
        presults->profile[arr_i] = R[right_i];
		strcpy(presults->title[arr_i], Rtitle[right_i]);
        ++right_i;
        ++arr_i;
    }
	/*for (int i = l; i <= r; ++i){
		fprintf(stderr, "%lf %s\n", results[index]->profile[i], results[index]->title[i]);
	}
		fprintf(stderr, "\n");*/
	return;
}

void pmergeSort(int l, int r){
	//printf("in\n");
    if (l < r) {
        int m = l + (r - l) / 2;
		pid_t a, b;
		//fprintf(stderr, "%d %d %d\n", l, m, r);
		if (m - l + 1 > Plimit) {
			a = fork();
			if (!a){
				fprintf(stderr, "%d %d", l, m);
				pmergeSort(l, m);
			}
		}
		////perror("aa");
		if (r - m > Plimit) {
			b = fork();
			if (!b){
				fprintf(stderr, "%d %d", m + 1, r);
				pmergeSort(m + 1, r);
			}
		}
		////perror("bb");
		if (m - l + 1 > Plimit)
			waitpid(a, NULL, 0);
		if (r - m > Plimit)
			waitpid(b, NULL, 0);
        pmerge(l, m, r);
		////perror("fork");
    }
	else if (l == r) {
		double *K; K = (double *)malloc(sizeof(double));
		char **Ktitle; Ktitle = (char **)malloc(sizeof(char *));
        K[0] = presults->profile[0];
		Ktitle[0] = presults->title[0];
		sort(Ktitle, K, 1);
        presults->profile[0] = K[0];
		presults->title[0] = Ktitle[0];
    }
	exit(0);
	//perror("merge");
	return;
}

void procProg(void) {
	int index = 0;
	int filterNum = 0;
	if (reqs[index]->keywords[0] == '*'){
		filterNum = num_of_movies;
		presults->profile = (double *)mmap(NULL, sizeof(double) * filterNum, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );
		presults->title = (char **)mmap(NULL, sizeof(char *) * filterNum, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );
		for (int i = 0; i < filterNum; ++i){
			presults->title[i] = (char *)mmap(NULL, sizeof(char) * MAX_LEN, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );
			strcpy(presults->title[i], movies[i]->title);
			presults->profile[i] = 0;
			for (int k = 0; k < NUM_OF_GENRE; ++k){
				presults->profile[i] += (movies[i]->profile[k] * reqs[index]->profile[k]);
			}
		}
		filterNum = num_of_movies;
	}
	else{
		for(int i = 0; i < num_of_movies; ++i){
			if (strstr(movies[i]->title, reqs[index]->keywords)){
				++filterNum;
			}
		}
		presults->profile = (double *)mmap(NULL, sizeof(double) * filterNum, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );
		presults->title = (char **)mmap(NULL, sizeof(char *) * filterNum, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );
		//perror("malloc");
		for(int i = 0, count = 0; i < num_of_movies; ++i){
			if (strstr(movies[i]->title, reqs[index]->keywords)){
				presults->title[count] = (char *)mmap(NULL, sizeof(char) * MAX_LEN, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );
				strcpy(presults->title[count], movies[i]->title);
				presults->profile[count] = 0;
				for (int k = 0; k < NUM_OF_GENRE; ++k){
					presults->profile[count] += (movies[i]->profile[k] * reqs[index]->profile[k]);
				}
				++count;
			}
		}
		//pthread_mutex_lock(&lock);
	}
	//perror("filter");
	presults->threadUsed = 1;
	pid_t temp;
	temp = fork();
	if (!temp){
		pmergeSort(0, filterNum - 1);
	}
	waitpid(temp, NULL, 0);
	//perror("mergeSort");
	char buf[126];
	sprintf(buf, "%dp.out", reqs[index]->id);
	FILE *fpwrite;
	if ((fpwrite = fopen(buf, "w+")) == NULL){
		ERR_EXIT("fopen");
	}
	for (int i = 0; i < filterNum; ++i){
		fprintf(fpwrite, "%s\n", presults->title[i]);
	}
	//perror("fwrite");
	fclose(fpwrite);
}

int main(int argc, char *argv[]){
	if(argc != 1){
#ifdef PROCESS
		fprintf(stderr,"usage: ./pserver\n");
#elif defined THREAD
		fprintf(stderr,"usage: ./tserver\n");
#endif
		exit(-1);
	}

	FILE *fp;
	//perror("start");

	if ((fp = fopen("./data/movies.txt","r")) == NULL){
		ERR_EXIT("fopen");
	}

	initialize(fp);
	assert(fp != NULL);
	fclose(fp);	
	num_of_usage = MAX_CPU / num_of_reqs;
	
	//lock = PTHREAD_MUTEX_INITIALIZER;
	#ifdef PROCESS
		presults = (result *)mmap (NULL, sizeof(result), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );
		procProg();
	#elif defined THREAD
		int *iIndex = (int *)malloc(sizeof(int) * num_of_reqs);
		for(int i = 0; i < num_of_reqs; ++i){
			iIndex[i] = i;
			pthread_create(&tid[i][0], NULL, threadProg, (void*) &iIndex[i]);
		}
		for(int i = 0; i < num_of_reqs; ++i){
			pthread_join(tid[i][0], NULL);
		}
	#endif
	return 0;
}

/**=======================================
 * You don't need to modify following code *
 * But feel free if needed.                *
 =========================================**/

request* read_request(){
	int id;
	char buf1[MAX_LEN],buf2[MAX_LEN];
	char delim[2] = ",";

	char *keywords;
	char *token, *ref_pts;
	char *ptr;
	double ret,sum;

	scanf("%u %254s %254s",&id,buf1,buf2);
	keywords = malloc(sizeof(char)*strlen(buf1)+1);
	if(keywords == NULL){
		ERR_EXIT("malloc");
	}

	memcpy(keywords, buf1, strlen(buf1));
	keywords[strlen(buf1)] = '\0';

	double* profile = malloc(sizeof(double)*NUM_OF_GENRE);
	if(profile == NULL){
		ERR_EXIT("malloc");
	}
	sum = 0;
	ref_pts = strtok(buf2,delim);
	for(int i = 0;i < NUM_OF_GENRE;i++){
		ret = strtod(ref_pts, &ptr);
		profile[i] = ret;
		sum += ret*ret;
		ref_pts = strtok(NULL,delim);
	}

	// normalize
	sum = sqrt(sum);
	for(int i = 0;i < NUM_OF_GENRE; i++){
		if(sum == 0)
				profile[i] = 0;
		else
				profile[i] /= sum;
	}

	request* r = malloc(sizeof(request));
	if(r == NULL){
		ERR_EXIT("malloc");
	}

	r->id = id;
	r->keywords = keywords;
	r->profile = profile;

	return r;
}

/*=================initialize the dataset=================*/
void initialize(FILE* fp){

	char chunk[MAX_LEN] = {0};
	char *token,*ptr;
	double ret,sum;
	int cnt = 0;

	assert(fp != NULL);

	// first row
	if(fgets(chunk,sizeof(chunk),fp) == NULL){
		ERR_EXIT("fgets");
	}

	memset(movies,0,sizeof(movie_profile*)*MAX_MOVIES);	

	while(fgets(chunk,sizeof(chunk),fp) != NULL){
		
		assert(cnt < MAX_MOVIES);
		chunk[MAX_LEN-1] = '\0';

		const char delim1[2] = " "; 
		const char delim2[2] = "{";
		const char delim3[2] = ",";
		unsigned int movieId;
		movieId = atoi(strtok(chunk,delim1));

		// title
		token = strtok(NULL,delim2);
		char* title = malloc(sizeof(char)*strlen(token)+1);
		if(title == NULL){
			ERR_EXIT("malloc");
		}
		
		// title.strip()
		memcpy(title, token, strlen(token)-1);
	 	title[strlen(token)-1] = '\0';

		// genres
		double* profile = malloc(sizeof(double)*NUM_OF_GENRE);
		if(profile == NULL){
			ERR_EXIT("malloc");
		}

		sum = 0;
		token = strtok(NULL,delim3);
		for(int i = 0; i < NUM_OF_GENRE; i++){
			ret = strtod(token, &ptr);
			profile[i] = ret;
			sum += ret*ret;
			token = strtok(NULL,delim3);
		}

		// normalize
		sum = sqrt(sum);
		for(int i = 0; i < NUM_OF_GENRE; i++){
			if(sum == 0)
				profile[i] = 0;
			else
				profile[i] /= sum;
		}

		movie_profile* m = malloc(sizeof(movie_profile));
		if(m == NULL){
			ERR_EXIT("malloc");
		}

		m->movieId = movieId;
		m->title = title;
		m->profile = profile;

		movies[cnt++] = m;
	}
	num_of_movies = cnt;

	// request
	scanf("%d",&num_of_reqs);
	assert(num_of_reqs <= MAX_REQ);
	for(int i = 0; i < num_of_reqs; i++){
		reqs[i] = read_request();
	}
}
/*========================================================*/
