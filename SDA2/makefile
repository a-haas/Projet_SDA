CFLAGS = -Wall -g
IFLAGS = -Iinclude
MODE = tasbinaire
ifeq ($(MODE),tasbinaire)
	STRUCTURE = tasBinaire.o
	STRUCTURE2 = tasBinaire.c tasBinaire.h
	STRUCTURE3 = tasBinaire.h
	TEST = -DTASBINAIRE
else
	STRUCTURE = merge_sort.o
	STRUCTURE2 = merge_sort.c merge_sort.h
	STRUCTURE3 = merge_sort.h
	TEST = -DMERGESORT
endif


main : main.o graphe.o prim.o kruskal.o pile.o parser.o $(STRUCTURE)
	gcc $(CFLAGS) $(TEST) -o main main.o graphe.o prim.o kruskal.o pile.o parser.o $(STRUCTURE)



kruskal.o : kruskal.c kruskal.h graphe.h
graphe.o : graphe.c graphe.h
prim.o : prim.c prim.h graphe.h $(STRUCTURE3)
$(STRUCTURE) : $(STRUCTURE2) graphe.h pile.h
pile.o : pile.c pile.h
parser.o : parser.c parser.h graphe.h
main.o : main.c graphe.h prim.h kruskal.h parser.h $(STRUCTURE3)

%.o :
	gcc $(CFLAGS) $(TEST) -c $< $(IFLAGS)

clean :
	rm *.o
	rm main
