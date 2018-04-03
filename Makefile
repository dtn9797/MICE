CXXFLAGS += --std=c++14

rebuild: div clean test_for_manager_items

debug: CXXFLAGS += -g
debug: rebuild

test_for_manager_items: test_for_manager_items.o manager.o items.o
	$(CXX) $(CXXFLAGS) -o test_for_manager_items test_for_manager_items.o manager.o items.o

test_for_manager_items.o: test_for_manager_items.cpp *h
	$(CXX) $(CXXFLAGS) -c test_for_manager_items.cpp

manager.o: manager.cpp *.h
	$(CXX) $(CXXFLAGS) -c manager.cpp

items.o: items.cpp *.h
	$(CXX) $(CXXFLAGS) -c items.cpp

test_for_scoop_container_topping: test_for_scoop_container_topping.o
	$(CXX) $(CXXFLAGS) -o test_for_scoop_container_topping test_for_scoop_container_topping.o

test_for_scoop_container_topping.o: test_for_scoop_container_topping.cpp *.h
	$(CXX) $(CXXFLAGS) -c test_for_scoop_container_topping.cpp

clean: 
	-rm -f *.o test_for_scoop_container_topping test_for_manager_items

div:
	@echo
	@echo 'X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-'
	@echo '-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X'
	@echo 'X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-'
	@echo '-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X'
	@echo


