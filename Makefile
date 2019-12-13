main : main.cpp Aquarium.o Bestiole.o Milieu.o Personality.h GregairePersonality.o PeureusePersonality.o KamikazePersonality.o PrevoyantePersonality.o
	g++ -Wall -std=c++11 -o main main.cpp Aquarium.o Bestiole.o Milieu.o GregairePersonality.o PeureusePersonality.o KamikazePersonality.o PrevoyantePersonality.o -I . -lX11 -lpthread

Aquarium.o : Aquarium.h Aquarium.cpp
	g++ -Wall -std=c++11  -c Aquarium.cpp -I .

Bestiole.o : Bestiole.h Bestiole.cpp Personality.h
	g++ -Wall -std=c++11  -c Bestiole.cpp -I .

Milieu.o : Milieu.h Milieu.cpp
	g++ -Wall -std=c++11  -c Milieu.cpp -I .

GregairePersonality.o : GregairePersonality.h GregairePersonality.cpp Personality.h
	g++ -Wall -std=c++11  -c GregairePersonality.cpp -I .

PeureusePersonality.o : PeureusePersonality.h PeureusePersonality.cpp Personality.h
	g++ -Wall -std=c++11  -c PeureusePersonality.cpp -I .

KamikazePersonality.o : KamikazePersonality.h KamikazePersonality.cpp Personality.h
	g++ -Wall -std=c++11  -c KamikazePersonality.cpp -I .

PrevoyantePersonality.o : PrevoyantePersonality.h PrevoyantePersonality.cpp Personality.h
	g++ -Wall -std=c++11  -c PrevoyantePersonality.cpp -I .

PHYLIS: clean
clean:
	rm *.o main
