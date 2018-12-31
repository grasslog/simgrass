CFLAGS=
OBJS = message.o decoder.o sim.o link.o fde.o
CXX=g++

all: $(OBJS)
	g++ -g test.cpp $(OBJS) -o test
	g++ test_link.cpp $(OBJS) -o test_link util/log.o

.cpp.o:
	$(CXX) -c $< -o $@

clean:
	rm -rf *.o a.out
