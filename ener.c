#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

#define SENS_TEMP 0
#define SENS_UMID 1
#define SENS_ENER 2

struct dati {
	int sensore;
	int valore;
};

struct messaggio {
	long int mtype;
	struct dati info;
};

int main(){
	int msgid, conta=0;
	struct messaggio txdata; 
	time_t start_time;

	msgid = msgget((key_t)7777, 0666 | IPC_CREAT);

	start_time = time(NULL);
	
	txdata.mtype = 3;
	txdata.info.sensore = SENS_ENER;

	srand((unsigned int)getpid());

	while((time(NULL)-start_time)<10){
		txdata.info.valore = (rand()%3000)+10;
		msgsnd(msgid, &txdata, sizeof(struct dati), 0);
		sleep(1);
	}

	txdata.info.valore = -1;
		msgsnd(msgid, &txdata, sizeof(struct dati), 0);

}

