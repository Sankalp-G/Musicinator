all: main

main: build
	make -j -C ./build

build:
	mkdir ./build
	cmake -B ./build

clean:
	rm -f main main-debug