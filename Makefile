TARGET = bin/project
SRC = (wildcard src/*.c)
OBJ = bin/test.o bin/main.o

$(TARGET): $(OBJ)
	gcc $^ -o $@

bin/%.o: src/%.c
	gcc -c $< -o $@ -Iinc

clean:
	rm -f $(TARGET)
	rm -f bin/%.o
