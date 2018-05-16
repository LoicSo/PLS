CC = gcc
INCDIR = ../include
LIBDIR = ../lib
EXDIR = ../Exemples
CFLAGS = -fPIC -Wall -I$(INCDIR) -g 
EXEC = compresseur
OBJS = main.o arbres.o calculs.o lecture_ecriture.o structure.o

all: $(EXEC) libcompresseur.a libcompresseur.so

libcompresseur.a : 
	ar -r $(LIBDIR)/libcompresseur.a arbres.o calculs.o lecture_ecriture.o structure.o

libcompresseur.so:
	gcc -shared -o $(LIBDIR)/libcompresseur.so arbres.o calculs.o lecture_ecriture.o structure.o

$(EXEC) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.c %.h
	$(CC) -c $(CFLAGS) -o $@ $<

clean :
	rm -f $(OBJS)
	rm -f $(EXEC)