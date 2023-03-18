CC=gcc

all: calculette

calculette: calculette.o analyse_syntaxique.o analyse_lexicale.o lecture_caracteres.o ast_construction.o ast_parcours.o
	$(CC) -o $@ $^ && rm *.o

analyse_lexicale.o: analyse_lexicale.c analyse_lexicale.h lecture_caracteres.h
	$(CC) -c $<

analyse_syntaxique.o: analyse_syntaxique.c analyse_syntaxique.h analyse_lexicale.h lecture_caracteres.h type_ast.h ast_construction.h
	$(CC) -c $<

lecture_caracteres.o: lecture_caracteres.c lecture_caracteres.h
	$(CC) -c $<

test_lexeme.o: test_lexeme.c analyse_lexicale.h
	$(CC) -c $<

calculette.o: calculette.c analyse_lexicale.h analyse_syntaxique.h lecture_caracteres.h ast_construction.h ast_parcours.h type_ast.h
	$(CC) -c $<

ast_parcours.o: ast_parcours.c ast_parcours.h type_ast.h
	$(CC) -c $<

ast_construction.o: ast_construction.c ast_construction.h type_ast.h
	$(CC) -c $<

clean:
	rm *.o calculette
	