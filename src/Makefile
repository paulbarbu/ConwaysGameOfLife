CXX = clang++
CXX_FLAGS = -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-qual -std=c++11

VALGRIND = valgrind
V_FALGS = --leak-check=full

DEBUG_FLAGS = -g

LIBS = -lSDL -lboost_program_options

APP_NAME = conway

SRC_FILES = main.cpp Game.cpp ConwaysGameOfLife.cpp helpers.cpp

executable:
	$(CXX) $(CXX_FLAGS) -O3 -o $(APP_NAME) $(SRC_FILES) $(LIBS)

debug:
	$(CXX) $(CXX_FLAGS) $(DEBUG_FLAGS) -o $(APP_NAME) $(SRC_FILES) $(LIBS)

valgrind: debug
	$(VALGRIND) $(V_FALGS) ./$(APP_NAME) $(args)

install:
	install -m 755 $(APP_NAME) $(DESTDIR)/usr/bin/
	mkdir $(DESTDIR)/usr/share/$(APP_NAME)
	install -m 744 *.txt $(DESTDIR)/usr/share/$(APP_NAME)

uninstall:
	rm -f $(DESTDIR)/usr/bin/$(APP_NAME)
	rm -rf $(DESTDIR)/usr/share/$(APP_NAME)

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
	rm -rf *.o ./$(APP_NAME)
