CXX       := gcc
CXX_FLAGS := -Wall -ggdb 

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   :=
EXECUTABLE  := main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.c
	$(CXX) $(CXX_FLAGS) $^ -lm -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*

