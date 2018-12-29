CFLAGS=
OBJS = message.o decoder.o sim.o
CXX=g++

all: $(OBJS)
	g++ -g test.cpp $(OBJS) -o test

.cpp.o:
	$(CXX) -c $< -o $@

clean:
	rm -rf *.o a.out
