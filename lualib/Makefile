CXXFLAGS=-std=c++17 -Wall -Wextra -g
LUAJIT=`pkg-config --cflags --libs luajit`

ecs.so: luaecs.cc ../cpp/mm_ecs.hh
	g++ $(LUAJIT) $(CXXFLAGS) -I../cpp $< -shared -o $@ -fPIC

clean:
	rm ecs.so

check: ecs.so
	lua example.lua
