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

all: water_data_write_rtf eltech_dz

water_data_write_rtf:
	$(CC) $(CFLAGSL) -o build/water_data_write_rtf water_data_write_rtf.c
# $(PBCC) $(CFLAGSPB) -o build/water_data_write_rtf.app water_data_write_rtf.c
	$(W32CC) $(CFLAGSW) -o build/water_data_write_rtf.exe water_data_write_rtf.c
	$(SU) "$(COPY) $(PWD)/build/water_data_write_rtf /bin/water_data_write_rtf"

tcp_sc: tcp_sc/client.c tcp_sc/server.c
	$(CC) $(CFLAGSL) tcp_sc/client.c -o build/tcp_sc/client
	$(PBCC) $(CFLAGSPB) -o build/tcp_sc/client.app tcp_sc/client.c
	$(W32CC) $(CFLAGSW) -o build/tcp_sc/client.exe tcp_sc/client.c -lws2_32
	$(CC) $(CFLAGSL) -o build/tcp_sc/server tcp_sc/server.c
	$(PBCC) $(CFLAGSPB) -o build/tcp_sc/server.app tcp_sc/server.c
	$(W32CC) $(CFLAGSW) -o build/tcp_sc/server.exe tcp_sc/server.c -lws2_32

eltech_dz:
	$(CC) $(CFLAGSL) -o build/eltech_dz eltech_dz.c
	$(PBCC) $(CFLAGSPB) -o build/eltech_dz.app eltech_dz.c
	$(W32CC) $(CFLAGSW) -o build/eltech_dz.exe eltech_dz.c

#lab2: 
#	$(CC) $(CFLAGSL) -o build/lab2 l2/main.cpp
#	$(PBCC) $(CFLAGSPB) -o build/lab2.app l2/main.cpp
#	$(W32CC) $(CFLAGSW) -o build/lab2.exe l2/main.cpp
#	
#lab4: 
#	$(CC) $(CFLAGSL) -o build/lab4 l4/main.cpp
#	$(PBCC) $(CFLAGSPB) -o build/lab4.app l4/main.cpp
#	$(W32CC) $(CFLAGSW) -o build/lab4.exe l4/main.cpp

clean:
	$(RM) build/water_data_write_rtf
	$(RM) build/water_data_write_rtf.app
	$(RM) build/water_data_write_rtf.exe
	$(RM) build/eltech_dz
	$(RM) build/tcp_sc/client
	$(RM) build/tcp_sc/client.app
	$(RM) build/tcp_sc/client.exe
	$(RM) build/tcp_sc/server
	$(RM) build/tcp_sc/server.app
	$(RM) build/tcp_sc/server.exe
#	$(RM) build/lab2
#	$(RM) build/lab2.app
#	$(RM) build/lab2.exe
#	$(RM) build/lab4
#	$(RM) build/lab4.app
#	$(RM) build/lab4.exe

rebuild: clean all