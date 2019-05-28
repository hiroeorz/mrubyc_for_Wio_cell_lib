.PHONY: build

TARGET=~/Documents/Arduino/libraries/mrubyc_for_Wio_cell_lib

install:
	rm -rf $(TARGET)
	cp -r ../mrubyc_for_Wio_cell_lib $(TARGET)
