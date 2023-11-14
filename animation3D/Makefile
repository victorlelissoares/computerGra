CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDLIBS =  -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

SRC_DIR = .
LIB_DIR = Libs
UTILS_DIR = Utils

SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(LIB_DIR)/*.cpp) $(wildcard $(UTILS_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

app: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm -rf *.o *~ app