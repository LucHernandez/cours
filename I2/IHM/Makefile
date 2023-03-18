CC=clang -Wall
PROG=Interface_Humain_SAT

all: $(PROG)

Interface_Humain_SAT: interface.o lecture_ecriture.o createur_fichier_sat.o
	$(CC) -o $@ $^

%.o : %.c
	$(CC) -c $<

interface.o: interface.c lecture_ecriture.h createur_fichier_sat.h tools.h

lecture_ecriture.o: lecture_ecriture.c lecture_ecriture.h tools.h

createur_fichier_sat.o: createur_fichier_sat.c createur_fichier_sat.h lecture_ecriture.h tools.h

clean:
	rm *.o $(PROG)