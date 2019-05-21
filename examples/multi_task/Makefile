.PHONY: build

MRBC=mrbc

build:
	$(MRBC) -E -Bcode task1.rb && cat task1.c | sed -e 's/code/code1/g' \
		| sed -e 's/extern const uint8_t code1\[\];//g'> task.c

	$(MRBC) -E -Bcode task2.rb && cat task2.c | sed -e 's/code/code2/g' \
		| sed -e 's/extern const uint8_t code2\[\];//g' >> task.c

	rm -f task1.c task2.c

clean:
	rm -f task.c task1.c task2.c

show:
	cat task.c
