CC= g++

CPPFLAGS= -g -Wall -std=c++11

main: main.o civ.o res.o list.o app.o

main.o: main.h app.h	

app.o: app.h list.h 

list.o: list.h civ.h 

civ.o: civ.h res.h

res.o: res.h

clean:
	rm *.o
