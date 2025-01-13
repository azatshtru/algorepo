src := $(notdir $(wildcard src/*.c))
obj := $(addprefix obj/,$(src:.c=.o))
headers := $(notdir $(wildcard 'headers/*.h'))

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
	@rm -f build/main *.o obj/*.o build/tests/* build/examples/*
	@echo cleaned.

run: build/main
	@./build/main

examples: $(examples) $(obj) tests/orange_juice.h

build/examples/%: examples/%.c $(obj) tests/orange_juice.h $(headers)
	gcc $< $(obj) -o $@

build/tests/%: tests/%.c $(obj) tests/orange_juice.h
	gcc $< $(obj) -o $@

test: $(tests)
	$(foreach x,$(tests),./$(x);)
