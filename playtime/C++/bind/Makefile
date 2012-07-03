
CC=g++
CFLAGS=
#CFLAGS=-std=c++0x 
OPT_CFLAGS=-O2
DEBUG_CFLAGS=-g

IFLAGS=-I../../utility
FILES=test.cxx
TARGET=a.out

deb:
	${CC} ${CFLAGS} ${DEBUG_CFLAGS} ${IFLAGS} ${FILES} -o ${TARGET}

opt:
	${CC} ${CFLAGS} ${OPT_CFLAGS} ${IFLAGS} ${FILES} -o ${TARGET}
