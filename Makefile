main : main.cpp Aquarium.o Bestiole.o Milieu.o Personality.o GregairePersonality.o PeureusePersonality.o KamikazePersonality.o PrevoyantePersonality.o
	g++ -Wall -std=c++11 -o main main.cpp Aquarium.o Bestiole.o Milieu.o -I . -lX11 -lpthread

Aquarium.o : Aquarium.h Aquarium.cpp
	g++ -Wall -std=c++11  -c Aquarium.cpp -I .

Bestiole.o : Bestiole.h Bestiole.cpp
	g++ -Wall -std=c++11  -c Bestiole.cpp -I .

Milieu.o : Milieu.h Milieu.cpp
	g++ -Wall -std=c++11  -c Milieu.cpp -I .

Personality.o : Personality.h
	g++ -Wall -std=c++11  -c Milieu.cpp -I .

GregairePersonality.o : GregairePersonality.h GregairePersonality.cpp
	g++ -Wall -std=c++11  -c GregairePersonality.cpp -I .

PeureusePersonality.o : PeureusePersonality.h PeureusePersonality.cpp
	g++ -Wall -std=c++11  -c PeureusePersonality.cpp -I .
        
KamikazePersonality.o : KamikazePersonality.h KamikazePersonality.cpp
	g++ -Wall -std=c++11  -c KamikazePersonality.cpp -I .
        
PrevoyantePersonality.o : PrevoyantePersonality.h PrevoyantePersonality.cpp
	g++ -Wall -std=c++11  -c PrevoyantePersonality.cpp -I .
        
