PROJECT=LABWORK1

IDIR=.
CXX=g++
CXXFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

DEPS = Image.h


OBJ = main.o Image.o

.PHONY: default

default: all;

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(PROJECT): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

all: $(PROJECT)

.PHONY: clean

clean:
	rm -f *.o *~ core $(INCDIR)/*~

cleanall: clean
	rm -f $(PROJECT)
