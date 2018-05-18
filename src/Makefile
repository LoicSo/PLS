CC = gcc
INCDIR = ../include
LIBDIR = ../lib
EXDIR = ../examples
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

clean :
	rm -f $(OBJS)
	rm -f $(EXEC)
	rm -f $(EXDIR)/*.cpr  $(EXDIR)/*_decomp*
