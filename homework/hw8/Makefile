CPPFILES := main.cpp game.cpp graph.cpp city.cpp person.cpp evader.cpp pursuer.cpp


all: $(CPPFILES)
	g++ -g $(CPPFILES)

test: graph_test city_test

city_test: city_test.cpp city.cpp city.h
	g++ city_test.cpp city.cpp -o city_test

graph_test: graph.cpp graph.h city.cpp city.h
	g++ graph_test.cpp graph.cpp city.cpp -o graph_test

clean:
	-@rm a.out *.o *.gch city_test graph_test
