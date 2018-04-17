CXXFLAGS = -std=c++11

all: main

debug: CXXFLAGS += -g
debug: rebuild

rebuild: clean main

main: main.o line.o turtle.o view.o *.h
	$(CXX) $(CXXFLAGS) -o stars main.o line.o turtle.o view.o `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
line.o: line.cpp *.h
	$(CXX) $(CXXFLAGS) -c line.cpp
turtle.o: turtle.cpp *.h
	$(CXX) $(CXXFLAGS) -c turtle.cpp
view.o: view.cpp *.h
	$(CXX) $(CXXFLAGS) -c view.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
pointers: pointers.cpp
	$(CXX) $(CXXFLAGS) -o pointers pointers.cpp
hello: hello.cpp hellop.cpp
	$(CXX) $(CXXFLAGS) -o hello hello.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
	$(CXX) $(CXXFLAGS) -o hellop hellop.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
clean:
	-rm -f *.o stars pointers hello hellop
