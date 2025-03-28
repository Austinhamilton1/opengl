CXX=g++

SRC=src
INC=include
OBJ=obj
BIN=bin

OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(wildcard $(SRC)/*.cpp)) $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(wildcard $(SRC)/*.c))

CXXFLAGS=-I$(INC)
LDFLAGS=-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

.PHONY: all clean

all: $(BIN)/libtest $(BIN)/hello

$(BIN)/libtest: $(OBJ)/libtest.o $(OBJS) | $(BIN)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)/libtest.o $(OBJS) $(LDFLAGS)

$(BIN)/hello: $(OBJ)/hello.o $(OBJS) | $(BIN)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)/hello.o $(OBJS) $(LDFLAGS)

$(OBJ)/libtest.o: libtest.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ)/hello.o: hello.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ)/glad.o: $(SRC)/glad.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ):
	mkdir -p $@

$(BIN):
	mkdir -p $@

clean:
	rm -rf $(OBJ)
	rm -rf $(BIN)