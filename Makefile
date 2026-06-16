TARGET = bin/project
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

$(TARGET): $(OBJ)
	gcc -g $^ -o $@

obj/%.o: src/%.c
	gcc -g -c $^ -o $@ -Iinc

clean:
	rm -f $(TARGET)
	rm -f bin/%.o
