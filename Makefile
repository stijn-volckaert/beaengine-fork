
all: shared

shared:
	gcc -O3 -fPIC -shared -o libBeaEngine.so BeaEngine.c
	strip -s libBeaEngine.so

lite:
	gcc -O3 -fPIC -shared -DBEA_LIGHT_DISASSEMBLY -o libBeaEngineLite.so BeaEngine.c
	strip -s libBeaEngineLite.so

