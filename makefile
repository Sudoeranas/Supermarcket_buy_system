=gcc
op=-Wall -Wextra

all : main.c
        $(c) $(op) main.c -o exe
clean :
	rm -rf exe
