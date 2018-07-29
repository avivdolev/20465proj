TARGET = assembler

src := $(wildcard *.c)
obj := $(src:.c=.o)
headers = $(wildcard *.h)

# TARGET = $(shell echo $${PWD\#\#*/})
FLAGS = -Wall -ansi -pedantic -g

%.o: %.c $(headers)
		gcc $(FLAGS) -o $@ -c $<

$(TARGET): $(obj) $(headers)
	gcc $(FLAGS) $(obj) -o $@

clean:
		rm $(obj) $(TARGET)

cleano:
		rm $(obj)
