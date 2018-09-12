#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define max_players 100
#define port 228

pthread_mutex_t mutex_login = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t mutex_manager = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t mutex_net = PTHREAD_MUTEX_INITIALIZER;

bool manager_st=0, login_st=0, net_st=0;

struct player_s {
    unsigned long int_id = 0;
    char ip1, ip2, ip3, ip4;
    char name[50];
    int sock;
    long x, y, z;
    Bool st = 0;
    char i_status = 0
};

struct player_s player[max_players];
//int sock[max_players];

bool sock_stat[max_players];


int stop = 0; 

//Функция завершения работы
int stop_all(void) {
    int d;
    if(stop == 2) exit(10);
    if(stop != 1) {
        stop = 1;
        ptolog( debug,  LOG_F, "\nЗавершение работы.");
        for(;;)
        {
            if(manager_st == 0 || login_st == 0 || net_st == 0)
            {
                ptolog( debug,  LOG_F, "\n");
                sleep(3);
                if(debug == 1) ptolog( debug,  LOG_F, "\nВсе потоки остановлены.\n");
                remove("term.pid");
                stop=2;
                break;
            }
        }
    }
}

void game_server()
{
    explicit_bzero(sock_stat, max_players);
    bzero(sock, max_players);

    pthread_attr_t attr;
    pthread_t info;
    pthread_attr_init(&attr);

    void (*TermSignal)(int);
    TermSignal = signal(SIGTERM, stop_file);

    void (*IntSignal)(int);
    IntSignal = signal(SIGINT, stop_file);
    
    void (*QuitSignal)(int);

    QuitSignal = signal(SIGQUIT, stop_file);
	
}

void* manager(void *arg){
	manager_st = 1;
	while(stop == 0)
	{
		
	}
	manager_st = 0;
}

void* login(void *arg){
	login_st = 1;
	while(stop == 0)
	{
		
	}
	login_st = 0;	
}

void* main_net(void *arg){
	net_st = 1;
	int listener, free_id = 0;
	char buf[1024];
	
	struct sockaddr_in addr;
	
	listener = socket(AF_INET, SOCK_STREAM, 0);
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)) <0 )
	{
	    perror("BIND!!");
	    exit(2);
	}


	while(stop == 0)
	{
		free_id = -1;
		for(int id; id < max_players; id++)
		{
		    if(sock_stat[id] == 0)
			free_id = id;
		}
		if(free_id != -1){
		    sock[free_id]=accept(listener, NULL, NULL);
		    sock_stat[id] = 1;
		    send(sock[free_id], "001, CONNECT ACCEPTED", 21, 0);
		    
		}
		
	}
	net_st = 0;	
}

void* test_server(void *arg)
{
	
}
