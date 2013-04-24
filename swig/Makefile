_ncva.so: ncva_wrap.o
	g++ -shared ncva_wrap.o ../bin/libncva.a ../bin/libux.a -o _ncva.so  -lstdc++

ncva_wrap.o: ncva_wrap.cxx
	g++ -fPIC -c ncva_wrap.cxx -I/usr/include/python2.6 -I../src/ -lstdc++

ncva_wrap.cxx: ncva.i
	swig -Wall -c++ -python -shadow -c++ -I../src/ ncva.i

test: _ncva.so
	python ./test__ncva.py
all:
clean:
	rm ncva_wrap.o _ncva.so ncva_wrap.cxx ncva.py*
