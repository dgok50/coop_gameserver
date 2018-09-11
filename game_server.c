#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

pthread_mutex_t mutex_login = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t mutex_manager = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t mutex_net = PTHREAD_MUTEX_INITIALIZER;

bool manager_st=0, login_st=0, net_st=0;

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
            if(rrd_trs == 1 || sens_trs == 1 || count_trs == 1 || dev_trs == 1)
            {
                ptolog( debug,  LOG_F, "\n");
                sleep(3);
                if(debug == 1)ptolog( debug,  LOG_F, "\nВсе потоки остановлены.\n");
                remove("term.pid");
                stop=2;
                break;
            }
        }
    }
}

void game_server()
{
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
	while(stop == 0)
	{
		
	}
	net_st = 0;	
}

void* test_server(void *arg)
{
	
}