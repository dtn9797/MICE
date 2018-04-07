#compiler options
CXXFLAGS+=--std=c++11
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
#source files
SOURCES=$(wildcard *.cpp)

#object files
OBJECTS=$(SOURCES:.cpp=.o)

#main link objects
MOBJECTS=$(filter-out test%,$(OBJECTS))

#test link objects
TOBJECTS=$(filter-out main.o,$(OBJECTS))

#included libraries
INCLUDE=

#executable filename
EXECUTABLE=mice

#Special symbols used:
#$^ - is all the dependencies (in this case =$(OBJECTS) )
#$@ - is the result name (in this case =$(EXECUTABLE) )

$(EXECUTABLE): $(MOBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(INCLUDE) $(GTKFLAGS)

test: CXXFLAGS+= -g
test: $(TOBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(INCLUDE) $(GTKFLAGS)

debug: CXXFLAGS+= -g
debug: $(EXECUTABLE)

%.o: %.cpp *.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@ $(GTKFLAGS)

clean:
	-rm -f $(EXECUTABLE) test $(OBJECTS)

div:
	echo "###########################"

