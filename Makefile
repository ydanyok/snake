OBJ = tview.o model.o main.o 
EXE = snake
CXXFLAGS += -Wall -g

all: $(EXE)
	
$(EXE): $(OBJ)
	$(CXX) -o $(EXE) $(OBJ)

clear:
	$(RM) $(OBJ) $(EXE)

depend:
	$(CXX) -MM $(OBJ:.o=.cpp) > .depend

-include .depend
