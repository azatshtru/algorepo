src := $(notdir $(wildcard src/*.c))
obj := $(addprefix build/obj/,$(src:.c=.o))
headers := $(wildcard headers/*.h)

dependencies := $(addprefix build/dependencies/,$(src:.c=.d))

TESTFILT = *
tests := $(addprefix build/,$(basename $(wildcard tests/$(TESTFILT)test*.c)))

examples = $(addprefix build/,$(basename $(wildcard examples/*.c)))

.PHONY: all clean run test

all: build/main

build/main: $(obj) main.c
	gcc main.c $(obj) -o build/main

build/dependencies/%.d: src/%.c
	gcc -MM -MT build/obj/$*.o $< -MF $@

build/obj/%.o: src/%.c
	gcc $< -o $@ -c

examples: $(examples) $(obj) tests/orange_juice.h

build/examples/%: examples/%.c $(obj) tests/orange_juice.h $(headers)
	gcc $< $(obj) -o $@

build/tests/%: tests/%.c $(obj) tests/orange_juice.h $(headers)
	gcc $< $(obj) -o $@

test: $(tests)
	@$(foreach x,$(tests),./$(x);)

-include $(dependencies)

clean:
	@rm -f build/obj/*.o build/tests/* build/examples/* build/main* build/dependencies/*
	@echo cleaned.

run: build/main
	@echo
	@./build/main

