a.out: view.o edit.o main.o
	gccc -o view.o edit.o main.o
view.o:  view.c
	gcc -c  view.c
edit.o:   edit.c
	gccc  -c  edit.c
main.o: main.c
	gcc  -c main.c
clean:
	rm  *.o *.out
