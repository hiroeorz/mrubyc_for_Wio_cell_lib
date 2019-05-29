.PHONY: all

MRBC=mrbc
SRC=task1.rb
OUTPUT=./mrblib.rb
ARDUINO=/Applications/Arduino.app/Contents/MacOS/Arduino

all: mrbc

mrbc:
	cat $(SRC) > mrblib.rb
	$(MRBC) -E -Bcode mrblib.rb && sed -i .tmp -e 's/extern const uint8_t code\[\];//g' mrblib.c
	rm -f mrblib.rb mrblib.c.tmp

sketch:
	$(ARDUINO) --verify tcp_socket.ino

clean:
	rm -f mrblib.c mrblib.rb

upload:
	$(ARDUINO) --upload tcp_socket.ino

watch: # pip install watchdog
	watchmedo shell-command --patterns=*task1.rb --recursive --wait --command="make"
