exec = claudius.out
sources = $(wildcard src/*.cc)
objects = $(sources:.cc=.o)
flags = -g

$(exec): $(objects)
	g++ $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	g++ -c $(flags) $< -o $@

install:
	make
	cp ./$(exec) /usr/local/bin/claudius

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o