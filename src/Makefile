CXX = clang++
CXX_FLAGS = -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-qual -std=c++11

DEBUG_FLAGS = -g

LIBS = -lSDL -lboost_program_options

APP_NAME = conway.exe

SRC_FILES = main.cpp Game.cpp ConwaysGameOfLife.cpp helpers.cpp

executable:
	$(CXX) $(CXX_FLAGS) -O3 -o $(APP_NAME) $(SRC_FILES) $(LIBS)

debug:
	$(CXX) $(CXX_FLAGS) $(DEBUG_FLAGS) -o $(APP_NAME) $(SRC_FILES) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
	rm -rf *.o *.exe
