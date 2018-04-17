CXXFLAGS = -std=c++11

all: main

debug: CXXFLAGS += -g
debug: rebuild

rebuild: clean main

main: main.o line.o view.o *.h
	$(CXX) $(CXXFLAGS) -o paint main.o line.o view.o `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
line.o: line.cpp *.h
	$(CXX) $(CXXFLAGS) -c line.cpp
view.o: view.cpp *.h
	$(CXX) $(CXXFLAGS) -c view.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
clean:
	-rm -f *.o paint
