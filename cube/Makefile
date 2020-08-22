# $@ -- target
# $< : 1st pre-req
# $? : all pre-req newer
# $^ : all pre-req


EXE:=main
SRC_DIR:=.
OBJ_DIR:=.

#wildcard is to extract all from *
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES)) 
#the following one will create ./src/*.o, not ./obj.o
#OBJ_FILES = $(patsubst %.cpp, %.o, $(SRC_FILES)) 


all: $(EXE)	

$(EXE): $(OBJ_FILES)
	g++ $^ -o $@

#this one will not work. it's calling  g++ -c cube.cpp -o main.o
#$(OBJ_FILES): $(SRC_FILES)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -c $< -o $@


clean:
	rm -f *.o ./main
