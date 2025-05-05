all: build
	./katanaCPP

build:
	g++-13 main.cpp -L /usr/local/lib/libhpdf.so.2.4 -l hpdf -o katanaCPP

clean:
	rm katanaCPP