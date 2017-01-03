all: static

static:
	mkdir -p build;
	cd build; \
	cmake -DCMAKE_BUILD_TYPE=Release ..; \
	make #VERBOSE=1

install: static
	cd build; \
	make install

clean:
	rm -rf ./build
