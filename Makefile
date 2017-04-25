CC=g++
LDIR=$(HOME)/CODE/libs/Boost/boost_1_58_0/
CFLAGS=-I$(LDIR) -std=c++11 #-g -pg #-stdlib=libc++
#CFLAGS=-I$(LDIR) -stdlib=libc++
#CFLAGS=-I$(LDIR) 
ODIR=./bin/
OBJS=$(ODIR)main.o $(ODIR)Domain.o $(ODIR)Crossover.o $(ODIR)Design.o $(ODIR)Constants.o $(ODIR)Common.o $(ODIR)Strand.o $(ODIR)Input.o $(ODIR)Staple.o $(ODIR)Scaffold.o $(ODIR)MyGraph.o $(ODIR)TempRamp.o $(ODIR)Transition.o $(ODIR)Simulation.o
EXECUTABLE=$(ODIR)DLM
SDIR=./src/
HDIR=./Headers/


#DEPS = $(SDIR)Common.h $(SDIR)MyGraph.h $(SDIR)TempRamp.h $(SDIR)Constants.h $(SDIR)Design.h $(SDIR)Simulation.h
DEPS = $(SDIR)Crossover.h $(SDIR)Domain.h $(HDIR)VertexProperty.h $(HDIR)EdgeProperty.h $(SDIR)Graph.h 

#%.o: %.cpp $(DEPS)
#		$(CC) -c -o $@ $< $(CFLAGS)


#all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXECUTABLE)

$(ODIR)main.o: $(SDIR)main.cpp $(ODIR)Design.o $(ODIR)Constants.o $(ODIR)Common.o $(ODIR)Strand.o $(ODIR)Input.o $(ODIR)Staple.o $(ODIR)Scaffold.o $(ODIR)MyGraph.o $(ODIR)TempRamp.o $(ODIR)Transition.o $(ODIR)Simulation.o
	$(CC) $(CFLAGS) -c $(SDIR)main.cpp -o $(ODIR)main.o

$(ODIR)Simulation.o: $(SDIR)Simulation.cpp $(SDIR)Simulation.h $(ODIR)MyGraph.o $(ODIR)TempRamp.o $(ODIR)Transition.o 
	$(CC) $(CFLAGS) -c $(SDIR)Simulation.cpp -o $(ODIR)Simulation.o

$(ODIR)Transition.o: $(SDIR)Transition.cpp $(SDIR)Transition.h $(ODIR)Common.o 
	$(CC) $(CFLAGS) -c $(SDIR)Transition.cpp -o $(ODIR)Transition.o

$(ODIR)TempRamp.o: $(SDIR)TempRamp.cpp $(SDIR)TempRamp.h $(ODIR)Common.o
	$(CC) $(CFLAGS) -c $(SDIR)TempRamp.cpp -o $(ODIR)TempRamp.o

$(ODIR)MyGraph.o: $(SDIR)MyGraph.cpp $(SDIR)MyGraph.h $(ODIR)Design.o
	$(CC) $(CFLAGS) -c $(SDIR)MyGraph.cpp -o $(ODIR)MyGraph.o

$(ODIR)Design.o: $(SDIR)Design.cpp $(SDIR)Design.h $(ODIR)Staple.o $(ODIR)Scaffold.o $(ODIR)Constants.o
	$(CC) $(CFLAGS) -c $(SDIR)Design.cpp -o $(ODIR)Design.o

$(ODIR)Scaffold.o: $(SDIR)Scaffold.cpp $(SDIR)Scaffold.h $(ODIR)Strand.o
	$(CC) $(CFLAGS) -c $(SDIR)Scaffold.cpp -o $(ODIR)Scaffold.o

$(ODIR)Staple.o: $(SDIR)Staple.cpp $(SDIR)Staple.h $(ODIR)Strand.o
	$(CC) $(CFLAGS) -c $(SDIR)Staple.cpp -o $(ODIR)Staple.o

$(ODIR)Strand.o: $(SDIR)Strand.cpp $(SDIR)Strand.h $(ODIR)Crossover.o
	$(CC) $(CFLAGS) -c $(SDIR)Strand.cpp -o $(ODIR)Strand.o

$(ODIR)Crossover.o: $(SDIR)Crossover.cpp $(SDIR)Crossover.h $(ODIR)Domain.o
	$(CC) $(CFLAGS) -c $(SDIR)Crossover.cpp -o $(ODIR)Crossover.o

$(ODIR)Domain.o: $(SDIR)Domain.cpp $(SDIR)Domain.h $(ODIR)Common.o $(HDIR)Graph.h
	$(CC) $(CFLAGS) -c $(SDIR)Domain.cpp -o $(ODIR)Domain.o

$(ODIR)Constants.o: $(SDIR)Constants.cpp $(SDIR)Constants.h $(ODIR)Common.o
	$(CC) $(CFLAGS) -c $(SDIR)Constants.cpp -o $(ODIR)Constants.o

$(ODIR)Input.o: $(SDIR)Input.cpp $(SDIR)Input.h $(ODIR)Common.o 
	$(CC) $(CFLAGS) -c $(SDIR)Input.cpp -o $(ODIR)Input.o

$(ODIR)Common.o: $(SDIR)Common.cpp $(SDIR)Common.h $(HDIR)Headers.h
	$(CC) $(CFLAGS) -c $(SDIR)Common.cpp -o $(ODIR)Common.o

clean:
	rm $(ODIR)*o $(ODIR)DLM
