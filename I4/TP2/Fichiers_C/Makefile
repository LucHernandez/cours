CC=gcc -Wall -Wextra
progs=test_lexeme calculette
all: $(progs)

%.o:%.c
	$(CC) -c $<
	
analyse_lexicale.o: analyse_lexicale.c analyse_lexicale.h lecture_caracteres.h

analyse_syntaxique.o: analyse_syntaxique.c analyse_syntaxique.h analyse_lexicale.h lecture_caracteres.h

lecture_caracteres.o: lecture_caracteres.c lecture_caracteres.h

test_lexeme.o: test_lexeme.c analyse_lexicale.h

calculette.o: calculette.c analyse_lexicale.h analyse_syntaxique.h lecture_caracteres.h

test_lexeme: analyse_lexicale.o lecture_caracteres.o test_lexeme.o
	$(CC) -o $@ $^

calculette: calculette.o analyse_lexicale.o analyse_syntaxique.o lecture_caracteres.o
	$(CC) -o $@ $^


clean:
	rm -f  $(progs) *.o *.gch