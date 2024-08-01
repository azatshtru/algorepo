src := $(shell cd src && find . -name '*.c' -or -name '*.s')
obj := $(src:.c=.o)
headers := $(shell cd headers && find . -name '*.h')

all: main

main: obj/$(obj) main.c
	gcc main.c obj/$(obj) -o main

obj/$(obj): src/$(src) headers/$(headers)
	gcc $< -o $@ -c

.PHONY: clean
clean:
	rm obj/$(obj) main

run: main
	@./main