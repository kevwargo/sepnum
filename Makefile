CC=gcc
CFLAGS=--std=c99 -D_POSIX_C_SOURCE=200809L

sepnum: sepnum.c
	${CC} ${CFLAGS} sepnum.c -o sepnum
