animal_classifier: animalclass.o main.o
	gcc -Wall -std=c99 animalclass.o main.o -o animal_classifier -lm

animalclass.o: animalclass.c given.h helper.h
	gcc -Wall -std=c99 -c animalclass.c

main.o: main.c given.h helper.h
	gcc -Wall -std=c99 -c main.c

clean:
	rm *.o animal_classifier
