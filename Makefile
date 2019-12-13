main : main.cpp Aquarium.o Bestiole.o ConcreteBestiole.o Milieu.o Decorateur.o Camouflage.o Carapace.o Yeux.o Nageoire.o
	g++ -Wall -std=c++11 -o main main.cpp Aquarium.o Bestiole.o ConcreteBestiole.o  Decorateur.o Camouflage.o Carapace.o Yeux.o Nageoire.o Milieu.o -I . -lX11 -lpthread

Aquarium.o : Aquarium.h Aquarium.cpp

Milieu.o : Milieu.h Milieu.cpp

Bestiole.o : Bestiole.h Bestiole.cpp

ConcreteBestiole.o : ConcreteBestiole.h ConcreteBestiole.cpp Bestiole.h

Decorateur.o : Decorateur.h Decorateur.cpp Bestiole.h

Nageoire.o : Nageoire.h Nageoire.cpp Decorateur.h

Oreilles.o : Oreilles.h Oreilles.cpp Decorateur.h

Yeux.o : Yeux.h Yeux.cpp Decorateur.h

Carapace.o : Carapace.h Carapace.cpp Decorateur.h

Camouflage.o : Camouflage.h Camouflage.cpp Decorateur.h


