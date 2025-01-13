src := $(notdir $(shell cd src && find . -name '*.c' -or -name '*.s'))
obj := $(addprefix obj/,$(src:.c=.o))
headers := $(shell find headers -name '*.h')

TESTFILT = *
tests := $(addprefix build/,$(basename $(wildcard tests/*.c)))

examples = $(addprefix build/,$(basename $(wildcard examples/*.c)))

.PHONY: all clean run test

all: build/main

build/main: $(obj) main.c $(headers)
	gcc main.c $(obj) -o build/main

obj/%.o: src/%.c headers/%.h
	gcc $< -o $@ -c

clean:
	@rm -f build/main *.o obj/*.o build/tests/*
	@echo cleaned.

run: build/main
	@./build/main

example: $(examples) $(obj) tests/orange_juice.h
	./build/examples/$(example)

build/examples/%: examples/%.c $(obj) tests/orange_juice.h
	gcc $< $(obj) -o $@

build/tests/%: tests/%.c $(obj) tests/orange_juice.h
	gcc $< $(obj) -o $@

test: $(tests)
	@for x in $(tests); do \
		./$$x; \
	done
