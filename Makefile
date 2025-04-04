CXX=g++

SRC=src
INC=include
OBJ=obj
BIN=bin

OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(wildcard $(SRC)/*.cpp)) $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(wildcard $(SRC)/*.c))

CXXFLAGS=-I$(INC) -g -D CL_TARGET_OPENCL_VERSION=300
LDFLAGS=-Llib -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lOpenCL -lopencl

.PHONY: all clean

all: $(BIN)/libtest $(BIN)/hello $(BIN)/perlin_mesh

$(BIN)/libtest: $(OBJ)/libtest.o $(OBJS) | $(BIN)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)/libtest.o $(OBJS) $(LDFLAGS)

$(BIN)/hello: $(OBJ)/hello.o $(OBJS) | $(BIN)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)/hello.o $(OBJS) $(LDFLAGS)

$(BIN)/perlin_mesh: $(OBJ)/perlin_mesh.o $(OBJS) | $(BIN)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)/perlin_mesh.o $(OBJS) $(LDFLAGS)

$(OBJ)/libtest.o: libtest.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ)/hello.o: hello.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ)/perlin_mesh.o: perlin_mesh.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ)/glad.o: $(SRC)/glad.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ)/Environment.o: $(SRC)/Environment.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ)/Scene.o: $(SRC)/Scene.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ)/Renderer.o: $(SRC)/Renderer.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ)/Shader.o: $(SRC)/Shader.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

$(OBJ)/VertexBuffer.o: $(SRC)/VertexBuffer.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

$(OBJ)/IndexBuffer.o: $(SRC)/IndexBuffer.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

$(OBJ)/GraphicsObject.o: $(SRC)/GraphicsObject.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

$(OBJ)/Image.o: $(SRC)/Image.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

$(OBJ)/Texture.o: $(SRC)/Texture.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

$(OBJ)/Camera.o: $(SRC)/Camera.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

$(OBJ)/Generate.o: $(SRC)/Generate.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

$(OBJ):
	mkdir -p $@

$(BIN):
	mkdir -p $@

clean:
	rm -rf $(OBJ)
	rm -rf $(BIN)
