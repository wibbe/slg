
all: compile

configure:
	mkdir -p build
	(cd build && cmake -DCMAKE_BUILD_TYPE=Release ..)

configure-debug:
	mkdir -p build
	(cd build && cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_DEBUG=Yes ..)

compile: 
	make -C build && (cd build/bin && ./unit_test)

run:
	(cd build/bin && ./terrain-edit)

debug:
	(cd build/bin && gdb ./terrain-edit)

run-example:
	(cd build/bin && ./example)

test:
	(cd build/bin && ./unit_test)

clean:
	make -C build clean

distclean:
	(rm -rf build)
