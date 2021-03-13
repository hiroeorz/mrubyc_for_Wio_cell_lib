.PHONY: mrbc

TARGET=~/Documents/Arduino/libraries/mrubyc_for_Wio_cell_lib

MRBC=mrbc
SRC=./mrblib/bmp280.rb ./mrblib/bme680.rb ./mrblib/json_generator.rb ./mrblib/json_parser.rb ./mrblib/mqtt_client.rb ./mrblib/serial_uart.rb ./mrblib/sht35.rb ./mrblib/wio.rb
RUBY_OUTPUT=./mrblib/wio_mrb_lib.rb
OUTPUT=./src/hal_wio/wio_mrb_lib.c

mrbc:
	cat $(SRC) > $(RUBY_OUTPUT)

	$(MRBC) -E -Bmruby_wio_code -o $(OUTPUT) $(RUBY_OUTPUT) && \
		sed -i .tmp -e 's/extern const uint8_t mruby_wio_code\[\];//g' $(OUTPUT)

	rm -f $(RUBY_OUTPUT) $(OUTPUT).tmp

install:
	rm -rf $(TARGET)
	cp -r ../mrubyc_for_Wio_cell_lib $(TARGET)

clean:
	rm -rf $(RUBY_OUTPUT) $(OUTPUT).tmp
