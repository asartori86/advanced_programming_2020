EXE = exe.x
CXX = c++
CXXFLAGS = -I include -g -std=c++11 -Wall -Wextra -I ../../06_error_handling/

SRC= main.cpp src/dog.cpp src/animal.cpp src/snake.cpp src/helper_functions.cpp
OBJ=$(SRC:.cpp=.o)
INC = include/animal.h  include/dog.h  include/helper_functions.h  include/snake.h

VPATH = ../../06_error_handling

# eliminate default suffixes
.SUFFIXES:
SUFFIXES =

# just consider our own suffixes
.SUFFIXES: .cpp .o

all: $(EXE)

.PHONY: all

clean:
	rm -rf $(OBJ) $(EXE) src/*~ include/*~ *~ html latex

.PHONY: clean

%.o: %.cpp ap_error.h
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(EXE): $(OBJ)
	$(CXX) $^ -o $(EXE)

documentation: Doxygen/doxy.in
	doxygen $^

.PHONY: documentation

main.o: include/dog.h include/animal.h include/snake.h \
 include/helper_functions.h

src/animal.o: include/animal.h 

src/dog.o: include/animal.h include/dog.h
src/snake.o: include/animal.h include/snake.h
src/helper_functions.o: include/animal.h include/helper_functions.h

format: $(SRC) $(INC)
	@clang-format -i $^ -verbose || echo "Please install clang-format to run this commands"

.PHONY: format
