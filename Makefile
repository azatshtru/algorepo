src := $(notdir $(shell cd src && find . -name '*.c' -or -name '*.s'))
obj := $(addprefix obj/,$(src:.c=.o))
headers := $(shell find headers -name '*.h')

TESTFILT = *
tests := $(shell cd tests && find . -name '$(TESTFILT)test*.c')
tests := $(foreach test,$(tests),tests/$(notdir $(test)))
compiled_tests := $(addprefix build/,$(basename $(tests)))

examples := examples/dynamic_programming_counting_tilings.c

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
	gcc $< $(obj) -o example
	./example

build/tests/%: tests/%.c $(obj) tests/orange_juice.h
	gcc $< $(obj) -o $@

test: $(compiled_tests)
	@for x in $(compiled_tests); do \
		./$$x; \
	done
