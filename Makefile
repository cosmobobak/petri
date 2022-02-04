

build:
	g++ -o target/main src/main.cpp -O2 -std=c++20 -Wall -Wextra -Wpedantic

run: build
	./target/main