/*
Scrivere un programma in C che permetta la raccolta dati da una serie di sensori (3 sensori)

Ogni sensore è rappresentato da un processo.
-Il primo sensore, periodicamente e ogni secondo, monitora la temperatura di una stanza.
-Il secondo sensore, periodicamente e ogni secondo, monitora l'umidità di una stanza.
-Il terzo sensore, periodicamente e ogni secondo, il consumo energetico.

tutti i sensori inviano i propri valori ad un processo lettore che riceverà un messaggio ogni due secondi e si occuperà di stampare a video i valori dei tre sensori in ordine di priorità.

Dopo 20 secondi di esecuzione tutti i processi sensori invieranno come valore del proprio sensore -1 per comunicare al processo lettore che hanno terminato.

Il processo lettore, quando leggerà che il valore di tutti e tre i sensori è uguale a -1 termina.

Utilizzare la coda di messaggi per lo scambio dati. Assegnare le seguenti priorità ai messaggi:1 temperatura, 2 umidità, 3 energia.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

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
	struct messaggio rxdata; 

	msgid = msgget((key_t)7777, 0666 | IPC_CREAT);

	while(1){
		msgrcv(msgid, &rxdata, sizeof(struct dati), -3, 0); //-3 è negativo, quindi riceve i messaggi in ordine di priorità
		switch(rxdata.info.sensore){
			case SENS_TEMP:
				printf("Temp: %d\n", rxdata.info.valore);
				break;
			case SENS_ENER:
				printf("Ener: %d\n", rxdata.info.valore);
				break;
			case SENS_UMID:
				printf("Umid: %d\n", rxdata.info.valore);
				break;
			default:
				break;
		}
		if(rxdata.info.valore == -1){
			conta++;
			if(conta == 3)
				break;
		}
		
		sleep(2);
	}

}





















