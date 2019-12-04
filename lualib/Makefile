../lib/ecs.so: ../lib/ecs.c ../lib/ecs.h
	$(MAKE) -C ../lib

ecs.so: luaecs.c ../lib/ecs.so
	gcc -Wall -Wextra -I../lib $< -shared -o $@ -fPIC -llua ../lib/ecs.so

clean:
	rm ecs.so

check: ecs.so
	lua example.lua
