CC = gcc
INCDIR = ../include
LIBDIR = ../lib
EXDIR = ../Exemples
CFLAGS = -fPIC -Wall -I$(INCDIR) -g -lm
EXEC = compresseur
OBJS = main.o arbres.o calculs.o lecture_ecriture.o structure.o decompression.o pretraitement.o

all: $(EXEC) libcompresseur.a libcompresseur.so

libcompresseur.a :
	ar -r $(LIBDIR)/libcompresseur.a arbres.o calculs.o lecture_ecriture.o structure.o decompression.o

libcompresseur.so:
	gcc -shared -o $(LIBDIR)/libcompresseur.so arbres.o calculs.o lecture_ecriture.o structure.o decompression.o

$(EXEC) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) -lm

%.o: %.c %.h
	$(CC) -c $(CFLAGS) -o $@ $< -lm

# structure.o: structure.c
# 	$(CC) -c -o $@ $< $(CFLAGS)
#
# calculs.o: calculs.c
# 	$(CC) -c -o $@ $< $(CFLAGS)
#
# lecture_ecriture.o: lecture_ecriture.c
# 	$(CC) -c -o $@ $< $(CFLAGS)
#
# main.o: main.c
# 	$(CC) -c -o $@ $< $(CFLAGS)
#
# arbres.o: arbres.c
# 	$(CC) -c -o $@ $< $(CFLAGS)


clean :
	rm -f $(OBJS)
	rm -f $(EXEC)
