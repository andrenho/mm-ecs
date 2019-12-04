ecs.so: luaecs.c
	gcc -I../lib $< -shared -o $@ -fPIC  -llua

clean:
	rm ecs.so

check: ecs.so
	lua example.lua
