.PHONY: build

MRBC=mrbc

build:
	$(MRBC) -E -Bcode task1.rb && cat task1.c | sed -e 's/extern const uint8_t code\[\];//g'> task.c
	rm -f task1.c

clean:
	rm -f task.c task1.c

show:
	cat task.c
