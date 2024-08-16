src := $(shell cd src && find . -name '*.c' -or -name '*.s')
obj := $(addprefix obj/,$(src:.c=.o))
headers := $(shell find include -name '*.h')

.PHONY: all clean

all: main
	@:

main: $(obj) $(headers)

obj/%.o: src/%.c
	gcc $< -o $@ -c

clean:
	@rm -f *.o obj/*.o