#
# iniparser tests Makefile
#

COPY    = cp
PWD	= $(shell pwd)
SU	= su -c
CC      = gcc
W32CC	= i686-w64-mingw32-gcc
PBCC	= ~/FRSCSDK/bin/arm-none-linux-gnueabi-gcc
CCPP    = g++
W32CCPP	= i686-w64-mingw32-g++
PBCCPP	= ~/FRSCSDK/bin/arm-none-linux-gnueabi-g++
CFLAGS  = -g -lm
CFLAGSW = $(CFLAGS) -static -static-libgcc -static-libstdc++ -finput-charset=UTF-8 -fexec-charset=cp1251
CFLAGSL = $(CFLAGS)
#-finput-charset=cp1251 -fexec-charset=UTF-8
CFLAGSPB = $(CFLAGS)
#-finput-charset=cp1251 -fexec-charset=UTF-8
LFLAGS  = 
AR	    = ar
ARFLAGS = rcv
RM      = rm -f


default: all

all: game_server

game_server:
	$(CC) $(CFLAGSL) -o build/game_server game_server.c
# $(PBCC) $(CFLAGSPB) -o build/game_server.app game_server.c
	$(W32CC) $(CFLAGSW) -o build/game_server.exe game_server.c

clean:
	$(RM) build/game_server
	$(RM) build/game_server.app
	$(RM) build/game_server.exe

rebuild: clean all