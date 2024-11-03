default: build/Snake
	./build/Snake

build/Snake: 
	cmake -S. -B./build
	make -C build
