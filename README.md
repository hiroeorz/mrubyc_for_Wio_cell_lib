# mruby/c for Wio3G Soracom Edition

## About
mruby/c for Wio3G Soracom Edition はSeeed社が開発し、ソラコム社が発売する[Wio3G SORACOM EDITION](https://soracom.jp/products/module/wio_3g_soracom_edition/)上で [mruby/c](https://github.com/mrubyc/mrubyc) を動作させるためのライブラリです。

本ライブラリを実装するにあたり、kishimaさんの以下の電子書籍やレポジトリ等を参考にさせていただいています。
* [mruby/cの小さな世界](https://silentworlds.info/2018/09/17/post-620/)
* [kishima/libmrubycForWioLTEArduino](https://github.com/kishima/libmrubycForWioLTEArduino)
* [mruby/cで始めるオリジナルIoTデバイス作り](https://magazine.rubyist.net/articles/0059/0059-original_mrubyc_iot_device.html)

本ライブラリはmruby/c 1.2のソースコードを含んでいます。

## Install

本リポジトリをcloneします.

```
$ git clone https://github.com/hiroeorz/mrubyc_Wio3G_Soracom_Edition.git
```

リポジトリごとArduinoのライブラリディレクトリに保存します。

```
$ cp -r mrubyc_Wio3G_Soracom_Edition  ~/Documents/Arduino/libraries/
```

あとは、スケッチの中で本ライブラリをインクルードします

* `スケッチ` -> `ライブラリのインクルード` -> `mruby/c for Wio3G Soracom Edition` を選択。

## Document

* [Wio3Gクラス](https://github.com/hiroeorz/mrubyc_Wio3G_Soracom_Edition/blob/master/doc/Wio3G.md)

## Examples

`examples` ディレクトリ以下にサンプルを置いています。
各サンプルのディレクトリに移動し

```
$ make
```

とすると、rubyのソースからCのソースを吐き出します。
あとはArduino上でビルドし、Wio3Gにアップロードして実行してください。

例として、Wio3Gに実装されているLEDを赤・緑・青で繰り返し光らせるためのRubyソースコードは以下のようになります。

```ruby:examples/led/task1.rb
wio = Wio.new
wio.power_supply_led(true)
rgb = [255, 0, 0]

while true
  last = rgb.pop
  rgb.unshift(last)
  wio.led_set_rgb(rgb[0], rgb[1], rgb[2])
  sleep 0.3
end
```

ここで、このディレクトリ内で `make` を実行すると `task.c` が生成されます。
この `task.c` を読み込んで実行するArduinoスケッチは以下のようになります。

```c++:led.ino
#include <Wio3GforArduino.h>
#include <libmrubyc.h>
#include "task.c"

extern const uint8_t code[];

#define MEMSIZE (1024*30)
static uint8_t mempool[MEMSIZE];

void setup() {
  delay(1000);

  mrbc_init(mempool, MEMSIZE);
  mrbc_define_wio3g_methods();

  if (NULL == mrbc_create_task(code, 0)) {
    SerialUSB.println("!!! mrbc_create_task error");
    return;
  }
 
  SerialUSB.println("--- running mruby/c ---");
}

void loop() {
  mrbc_run();
}
```

コンパイル・基板にアップロードして実行するとLEDが三色順番に発光します。

## License
mruby/c for Wio3G Soracom Edition はBSD License(aka 3-clause license)のもとで配布いたします。
