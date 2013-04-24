all : python-bindings

python-bindings: 
	swig -Wall -c++ -python -shadow -c++ -I../src/ -outdir python ncva.i
	mv -f ncva_wrap.cxx python

clean:
	rm *.o
