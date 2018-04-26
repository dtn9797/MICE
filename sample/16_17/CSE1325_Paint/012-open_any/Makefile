CXXFLAGS = --std=c++11

all: div main

rebuild: clean all

debug: CXXFLAGS += -g
debug: rebuild

test_line: test_line.o line.o *.h
	$(CXX) $(CXXFLAGS) -g -o  a test_line.o line.o `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
main: main.o mainwin.o line.o view.o *.h
	$(CXX) $(CXXFLAGS) -o paint main.o mainwin.o line.o view.o `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
mainwin.o: mainwin.cpp *.h
	$(CXX) $(CXXFLAGS) -c mainwin.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
view.o: view.cpp *.h
	$(CXX) $(CXXFLAGS) -c view.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
line.o: line.cpp *.h
	$(CXX) $(CXXFLAGS) -g -c line.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
test_line.o: test_line.cpp *.h
	$(CXX) $(CXXFLAGS) -g -c  test_line.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

clean:
	-rm -f *.o paint test_line
div:
	@echo
	@echo 'X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-'
	@echo '-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X'
	@echo 'X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-'
	@echo '-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X'
	@echo
