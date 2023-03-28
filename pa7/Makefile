#Tim Kraemer
#CruzID: tikraeme
#pa7

Order : Order.o Dictionary.o
		g++ -std=c++17 -Wall -o Order Order.o Dictionary.o

Order.o : Dictionary.h Order.cpp
		g++ -std=c++17 -Wall -c -g Order.cpp

DictionaryTest: DictionaryTest.o Dictionary.o
		g++ -std=c++17 -Wall -o DictionaryTest DictionaryTest.o Dictionary.o

DictionaryTest.o: Dictionary.h DictionaryTest.cpp
		g++ -std=c++17 -Wall -c -g DictionaryTest.cpp

Dictionary.o : Dictionary.h Dictionary.cpp
		g++ -std=c++17 -Wall -c -g Dictionary.cpp

clean :
		rm -f DictionaryTest DictionaryTest.o Order Order.o Dictionary.o

check1 : DictionaryTest
		valgrind --leak-check=full DictionaryTest

check2 : Order
		valgrind --leak-check=full Order
