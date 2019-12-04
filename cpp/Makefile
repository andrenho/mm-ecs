CXXFLAGS=-std=c++17 -Wall -Wextra -g

example: example.cc mm_ecs.hh
				g++ $(CXXFLAGS) -I. -o $@ $<

clean:
				rm example

check: example
				./example

# vim: st=8:sts=8:sw=8:noexpandtab
