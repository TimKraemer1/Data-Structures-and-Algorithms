#Tim Kraemer
#CruzID: tikraeme
#pa5

Shuffle : Shuffle.o List.o
		g++ -std=c++17 -Wall -o Shuffle Shuffle.o List.o 

Shuffle.o : List.h Shuffle.cpp
		g++ -std=c++17 -Wall -c -g Shuffle.cpp

ListTest: ListTest.o List.o
		g++ -std=c++17 -Wall -o ListTest ListTest.o List.o

ListTest.o: List.h ListTest.cpp
		g++ -std=c++17 -Wall -c -g ListTest.cpp

ListClient : ListClient.o List.o
		g++ -std=c++17 -Wall -o ListClient ListClient.o List.o 

ListClient.o : List.h ListClient.cpp
		g++ -std=c++17 -Wall -c ListClient.cpp

List.o : List.h List.cpp
		g++ -std=c++17 -Wall -c -g List.cpp

clean :
		rm -f ListTest ListTest.o Shuffle Shuffle.o ListClient ListClient.o List.o

check1 : ListClient
		valgrind --leak-check=full ListClient

check2 : Shuffle
		valgrind --leak-check=full Shuffle 35
