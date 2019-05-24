.PHONY: build

MRBC=mrbc
SRC = ../../mrblib/*.rb task1.rb
OUTPUT = ./mrblib.rb

build:
	cat $(SRC) > mrblib.rb
	$(MRBC) -E -Bcode mrblib.rb && sed -i .tmp -e 's/extern const uint8_t code\[\];//g' mrblib.c
	rm -f mrblib.rb mrblib.c.tmp

clean:
	rm -f mrblib.c mrblib.rb


watch: # pip install watchdog
	watchmedo shell-command --patterns="task1.rb" --recursive --wait \
	     --command="make"
