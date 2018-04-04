CXXFLAGS += --std=c++14

rebuild: div clean test_for_manager_items

debug: CXXFLAGS += -g
debug: rebuild

test_for_scoop_container_topping: test_for_scoop_container_topping.o scoop.o container.o topping.o
	$(CXX) $(CXXFLAGS) -o test_for_scoop_container_topping test_for_scoop_container_topping.o scoop.o container.o topping.o

test_for_scoop_container_topping.o: test_for_scoop_container_topping.cpp *.h
	$(CXX) $(CXXFLAGS) -c test_for_scoop_container_topping.cpp
scoop.o: scoop.cpp *h
	$(CXX) $(CXXFLAGS) -c scoop.cpp
container.o: container.cpp *h
	$(CXX) $(CXXFLAGS) -c container.cpp
topping.o: topping.cpp *h
	$(CXX) $(CXXFLAGS) -c topping.cpp

items.o: items.cpp *.h
	$(CXX) $(CXXFLAGS) -c items.cpp
clean: 
	-rm -f *.o test_for_scoop_container_topping test_for_manager_items

div:
	@echo
	@echo 'X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-'
	@echo '-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X'
	@echo 'X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-'
	@echo '-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X'
	@echo


