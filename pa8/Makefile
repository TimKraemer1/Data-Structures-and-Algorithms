#Tim Kraemer
#CruzID: tikraeme
#pa8

Order : Order.o Dictionary.o
		g++ -std=c++17 -Wall -o Order Order.o Dictionary.o

WordFrequency : WordFrequency.o Dictionary.o
		g++ -std=c++17 -Wall -o WordFrequency WordFrequency.o Dictionary.o

Order.o : Dictionary.h Order.cpp
		g++ -std=c++17 -Wall -c -g Order.cpp

WordFrequency.o : Dictionary.h WordFrequency.cpp
		g++ -std=c++17 -Wall -c -g WordFrequency.cpp

DictionaryTest: DictionaryTest.o Dictionary.o
		g++ -std=c++17 -Wall -o DictionaryTest DictionaryTest.o Dictionary.o

DictionaryTest.o: Dictionary.h DictionaryTest.cpp
		g++ -std=c++17 -Wall -c -g DictionaryTest.cpp

Dictionary.o : Dictionary.h Dictionary.cpp
		g++ -std=c++17 -Wall -c -g Dictionary.cpp

clean :
		rm -f DictionaryTest DictionaryTest.o Order Order.o Dictionary.o WordFrequency WordFrequency.o

check1 : DictionaryTest
		valgrind --leak-check=full DictionaryTest

check2 : Order
		valgrind --leak-check=full Order
