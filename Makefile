
#VARS, FLAGS
D_INC = inc
D_SRC = src
D_OBJ = obj
D_BIN = bin
F_SRC = $(wildcard $(D_SRC)/*.cpp)
F_OBJ = $(patsubst $(D_SRC)/%.cpp,$(D_OBJ)/%.o,$(F_SRC))

D_GLEW_INC = lib/glew/include
GLEW_FLAGS = -Llib/glew/lib -lglew32

D_GLFW_INC = lib/glfw/include
GLFW_FLAGS = -Llib/glfw/lib -lglfw3dll

D_GLM_INC = lib/glm/include
GLM_FLAGS = -Llib/glm/lib -lglm_shared.dll

CXX_FLAGS = -std=c++11


#COMMANDS
prog.exe: $(D_OBJ)/main.o $(F_OBJ)
	g++ -o $(D_BIN)/$@ $(D_OBJ)/main.o $(F_OBJ) $(GLEW_FLAGS) $(GLFW_FLAGS) $(GLM_FLAGS) -lopengl32

$(D_OBJ)/main.o: main.cpp
	g++ -c $< -o $@ -I$(D_INC) -I$(D_GLEW_INC) -I$(D_GLFW_INC) -I$(D_GLM_INC) $(CXX_FLAGS)

$(D_OBJ)/%.o: $(D_SRC)/%.cpp $(D_INC)/%.hpp
	g++ -c $< -o $@ -I$(D_INC) -I$(D_GLEW_INC) -I$(D_GLFW_INC) -I$(D_GLM_INC) $(CXX_FLAGS)
	
clean:
	rm $(D_OBJ)/*.o
	rm $(D_BIN)/*.exe
