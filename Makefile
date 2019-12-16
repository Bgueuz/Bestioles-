main : main.cpp Aquarium.o Bestiole.o ConcreteBestiole.o Milieu.o Decorateur.o Camouflage.o Carapace.o Yeux.o Nageoire.o Personality.h GregairePersonality.o PeureusePersonality.o KamikazePersonality.o PrevoyantePersonality.o
	g++ -Wall -std=c++11 -o main main.cpp Aquarium.o Bestiole.o ConcreteBestiole.o  Decorateur.o Camouflage.o Carapace.o Yeux.o Nageoire.o Milieu.o GregairePersonality.o PeureusePersonality.o KamikazePersonality.o PrevoyantePersonality.o -I . -lX11 -lpthread

Aquarium.o : Aquarium.h Aquarium.cpp Milieu.h

Bestiole.o : Bestiole.h Bestiole.cpp

Camouflage.o : Camouflage.h Camouflage.cpp Decorateur.h

Carapace.o : Carapace.h Carapace.cpp Decorateur.h

ConcreteBestiole.o : ConcreteBestiole.h ConcreteBestiole.cpp Bestiole.h Milieu.h GregairePersonality.h PeureusePersonality.h KamikazePersonality.h PrevoyantePersonality.h

Decorateur.o : Decorateur.h Decorateur.cpp

GregairePersonality.o : GregairePersonality.h GregairePersonality.cpp Personality.h
	g++ -Wall -std=c++11  -c GregairePersonality.cpp -I .

KamikazePersonality.o : KamikazePersonality.h KamikazePersonality.cpp Personality.h
	g++ -Wall -std=c++11  -c KamikazePersonality.cpp -I .

Milieu.o : Milieu.h Milieu.cpp ConcreteBestiole.h

Nageoire.o : Nageoire.h Nageoire.cpp Decorateur.h

Oreilles.o : Oreilles.h Oreilles.cpp Decorateur.h

PeureusePersonality.o : PeureusePersonality.h PeureusePersonality.cpp Personality.h
	g++ -Wall -std=c++11  -c PeureusePersonality.cpp -I .

PrevoyantePersonality.o : PrevoyantePersonality.h PrevoyantePersonality.cpp Personality.h
	g++ -Wall -std=c++11  -c PrevoyantePersonality.cpp -I .

Yeux.o : Yeux.h Yeux.cpp Decorateur.h

PHYLIS: clean
clean:
	rm *.o main
