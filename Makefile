CC=g++
LDIR=$(HOME)/CODE/libs/Boost/boost_1_58_0/
CFLAGS=-I$(LDIR) -std=c++11 #-stdlib=libc++
#CFLAGS=-I$(LDIR) -stdlib=libc++
#CFLAGS=-I$(LDIR) 
ODIR=./bin/
OBJS=$(ODIR)main.o $(ODIR)Design.o $(ODIR)Constants.o $(ODIR)Common.o $(ODIR)Strand.o $(ODIR)Input.o $(ODIR)Staple.o $(ODIR)Scaffold.o
EXECUTABLE=$(ODIR)DLM
SDIR=./src/


#DEPS = $(SDIR)Common.h $(SDIR)MyGraph.h $(SDIR)TempRamp.h $(SDIR)Constants.h $(SDIR)Design.h $(SDIR)Simulation.h
DEPS = $(SDIR)Crossover.h $(SDIR)Domain.h $(SDIR)VertexProperty.h $(SDIR)EdgeProperty.h $(SDIR)Graph.h 

#%.o: %.cpp $(DEPS)
#		$(CC) -c -o $@ $< $(CFLAGS)


#all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXECUTABLE)

$(ODIR)main.o: $(SDIR)main.cpp $(ODIR)Design.o $(ODIR)Constants.o $(ODIR)Common.o $(ODIR)Strand.o $(ODIR)Input.o $(ODIR)Staple.o $(ODIR)Scaffold.o
	$(CC) $(CFLAGS) -c $(SDIR)main.cpp -o $(ODIR)main.o

$(ODIR)Design.o: $(SDIR)Design.cpp $(SDIR)Design.h $(ODIR)Common.o $(ODIR)Staple.o $(ODIR)Scaffold.o $(DEPS)
	$(CC) $(CFLAGS) -c $(SDIR)Design.cpp -o $(ODIR)Design.o

$(ODIR)Scaffold.o: $(SDIR)Scaffold.cpp $(SDIR)Scaffold.h $(ODIR)Strand.o $(ODIR)Common.o $(DEPS)
	$(CC) $(CFLAGS) -c $(SDIR)Scaffold.cpp -o $(ODIR)Scaffold.o

$(ODIR)Staple.o: $(SDIR)Staple.cpp $(SDIR)Staple.h $(ODIR)Strand.o $(ODIR)Common.o $(DEPS)
	$(CC) $(CFLAGS) -c $(SDIR)Staple.cpp -o $(ODIR)Staple.o

$(ODIR)Strand.o: $(SDIR)Strand.cpp $(SDIR)Strand.h $(ODIR)Common.o $(DEPS)
	$(CC) $(CFLAGS) -c $(SDIR)Strand.cpp -o $(ODIR)Strand.o

$(ODIR)Constants.o: $(SDIR)Constants.cpp $(SDIR)Constants.h $(ODIR)Common.o
	$(CC) $(CFLAGS) -c $(SDIR)Constants.cpp -o $(ODIR)Constants.o

$(ODIR)Common.o: $(SDIR)Common.cpp $(SDIR)Common.h $(SDIR)Headers.h
	$(CC) $(CFLAGS) -c $(SDIR)Common.cpp -o $(ODIR)Common.o

$(ODIR)Input.o: $(SDIR)Input.cpp $(SDIR)Input.h $(SDIR)Headers.h 
	$(CC) $(CFLAGS) -c $(SDIR)Input.cpp -o $(ODIR)Input.o

clean:
	rm $(ODIR)*o $(ODIR)DLM
