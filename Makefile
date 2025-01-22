src := $(notdir $(wildcard src/*.c))
obj := $(addprefix build/obj/,$(src:.c=.o))
headers := $(wildcard headers/*.h)

dependencies := $(addprefix build/dependencies/,$(src:.c=.d))

tests := $(addprefix build/,$(basename $(wildcard tests/test*.c)))

examples := $(addprefix build/,$(basename $(wildcard examples/*.c)))

directories := build build/dependencies build/examples build/obj build/tests src tests headers examples docs

.PHONY: all clean run test setup

all: setup build/main $(examples)

setup: $(directories)

$(directories):
	mkdir -p $@

build/main: $(obj) main.c
	gcc main.c $(obj) -o build/main

build/dependencies/%.d: src/%.c
	gcc -MM -MT build/obj/$*.o $< -MF $@

build/obj/%.o: src/%.c
	gcc $< -o $@ -c

build/examples/%: examples/%.c $(obj) tests/orange_juice.h $(headers)
	gcc $< $(obj) -o $@

build/tests/%: tests/%.c $(obj) tests/orange_juice.h $(headers)
	gcc $< $(obj) -o $@

test: setup $(tests)
	@$(foreach x,$(tests),./$(x);)

test_%: setup build/tests/test_%
	@./build/tests/$@

clean:
	@rm -f build/obj/*.o build/tests/* build/examples/* build/main* build/dependencies/*
	@rm -rf build
	@echo cleaned.

run: setup build/main
	@echo
	@./build/main

-include $(dependencies)
