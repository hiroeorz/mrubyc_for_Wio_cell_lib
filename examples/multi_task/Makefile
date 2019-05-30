.PHONY: build

MRBC=mrbc

build:
	$(MRBC) -E -Bcode1 task1.rb && cat task1.c  \
		| sed -e 's/extern const uint8_t code1\[\];//g'> task.c

	$(MRBC) -E -Bcode2 task2.rb && cat task2.c  \
		| sed -e 's/extern const uint8_t code2\[\];//g' >> task.c

	$(MRBC) -E -Bcode3 task3.rb && cat task3.c  \
		| sed -e 's/extern const uint8_t code3\[\];//g' >> task.c


	rm -f task1.c task2.c task3.c

clean:
	rm -f task.c task1.c task2.c task3.c

show:
	cat task.c
