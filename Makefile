prog_name = clox

.PHONY: all

all: compile run

compile:
	@cmake -S . -B ./build
	@cd build && make

run:
	@./build/$(prog_name)

clean:
	@rm -rf ./build
