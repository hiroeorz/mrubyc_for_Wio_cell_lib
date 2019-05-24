.PHONY: build

TARGET=~/Documents/Arduino/libraries/mrubyc_Wio3G_Soracom_Edition

install:
	rm -r $(TARGET)
	cp -r ../mrubyc_Wio3G_Soracom_Edition $(TARGET)
