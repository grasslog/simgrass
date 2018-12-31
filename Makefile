all:
	cd src/util; make
	cd src; make

clean:
	cd src/util; make clean
	cd src; make clean
	rm -rf *.o a.out
