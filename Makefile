src := $(shell cd src && find . -name '*.c' -or -name '*.s')
obj := $(addprefix obj/,$(src:.c=.o))
headers := $(shell find headers -name '*.h')

collection_dirs := common_collections
collections = $(shell find $(collection_dirs) -name '*.o')
collection_make := $(foreach word,$(collection_dirs),cd $(word) && $(MAKE))

.PHONY: all clean run pre-build

all: build

build: pre-build main

main: $(obj) main.c $(headers)
	gcc main.c $(obj) $(collections) -o main

pre-build:
	@$(collection_make)

obj/%.o: src/%.c
	gcc $< -o $@ -c

clean:
	@rm -f main *.o obj/*.o $(collections)

run: build
	@./main
