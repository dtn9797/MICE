CXXFLAGS += --std=c++14

rebuild: div clean test_for_manager_items

debug: CXXFLAGS += -g
debug: rebuild

all: main test_for_scoop_container_topping test_for_emporium test_for_view

main: main.o controller.o view.o emporium.o scoop.o container.o topping.o items.o
	$(CXX) $(CXXFLAGS) -o main main.o controller.o view.o emporium.o scoop.o container.o topping.o items.o
test_for_scoop_container_topping: test_for_scoop_container_topping.o scoop.o container.o topping.o
	$(CXX) $(CXXFLAGS) -o test_for_scoop_container_topping test_for_scoop_container_topping.o scoop.o container.o topping.o
test_for_emporium: test_for_emporium.o emporium.o scoop.o container.o topping.o items.o
	$(CXX) $(CXXFLAGS) -o test_for_emporium test_for_emporium.o emporium.o scoop.o container.o topping.o items.o
test_for_view: test_for_view.o view.o emporium.o scoop.o container.o topping.o items.o
	$(CXX) $(CXXFLAGS) -o test_for_view test_for_view.o view.o emporium.o scoop.o container.o topping.o items.o

test_for_view.o: test_for_view.cpp *.h
	$(CXX) $(CXXFLAGS) -c test_for_view.cpp
test_for_scoop_container_topping.o: test_for_scoop_container_topping.cpp *.h
	$(CXX) $(CXXFLAGS) -c test_for_scoop_container_topping.cpp
test_for_emporium.o: test_for_emporium.cpp *.h
	$(CXX) $(CXXFLAGS) -c test_for_emporium.cpp
emporium.o: emporium.cpp *.h
	$(CXX) $(CXXFLAGS) -c emporium.cpp
scoop.o: scoop.cpp *.h
	$(CXX) $(CXXFLAGS) -c scoop.cpp
container.o: container.cpp *.h
	$(CXX) $(CXXFLAGS) -c container.cpp
topping.o: topping.cpp *.h
	$(CXX) $(CXXFLAGS) -c topping.cpp
items.o: items.cpp *.h
	$(CXX) $(CXXFLAGS) -c items.cpp
view.o: view.cpp *h
	$(CXX) $(CXXFLAGS) -c view.cpp
controller.o: controller.cpp *h
	$(CXX) $(CXXFLAGS) -c controller.cpp
main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp 
clean: 
	-rm -f *.o all

div:
	@echo
	@echo 'X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-'
	@echo '-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X'
	@echo 'X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-'
	@echo '-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X'
	@echo


