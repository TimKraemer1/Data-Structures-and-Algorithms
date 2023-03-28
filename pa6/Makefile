#Tim Kraemer
#CruzID: tikraeme
#pa6

Arithmetic : Arithmetic.o List.o BigInteger.o
		g++ -std=c++17 -Wall -o Arithmetic Arithmetic.o List.o BigInteger.o

Arithmetic.o : List.h BigInteger.h Arithmetic.cpp
		g++ -std=c++17 -Wall -c -g Arithmetic.cpp

BigIntegerTest: BigIntegerTest.o List.o BigInteger.o
		g++ -std=c++17 -Wall -o BigIntegerTest BigIntegerTest.o List.o BigInteger.o

BigIntegerTest.o: List.h BigInteger.h BigIntegerTest.cpp
		g++ -std=c++17 -Wall -c -g BigIntegerTest.cpp

List.o : List.h List.cpp
		g++ -std=c++17 -Wall -c -g List.cpp

BigInteger.o: BigInteger.h BigInteger.cpp
		g++ -std=c++17 -Wall -c -g BigInteger.cpp

clean :
		rm -f BigIntegerTest BigIntegerTest.o Arithmetic Arithmetic.o ListClient ListClient.o List.o BigInteger.o

check1 : ListClient
		valgrind --leak-check=full ListClient

check2 : Shuffle
		valgrind --leak-check=full Shuffle 35
