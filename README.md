# mruby/c for Wio(3G, LTE, LTE M1/NB1)

## About
mruby/c for Wio はSeeed社が開発した以下の基板上で [mruby/c](https://github.com/mrubyc/mrubyc) を動作させるためのライブラリです。

* [Wio3G SORACOM EDITION](https://soracom.jp/products/module/wio_3g_soracom_edition/)
* [Wio LTE JP Version](https://soracom.jp/products/module/wio_lte/)
* [Wio LTE M1/NB1](https://soracom.jp/products/module/wio_lte_m1_nb1/)


本ライブラリを実装するにあたり、kishimaさんの以下の電子書籍やレポジトリ等を参考にさせていただいています。
* [mruby/cの小さな世界](https://silentworlds.info/2018/09/17/post-620/)
* [kishima/libmrubycForWioLTEArduino](https://github.com/kishima/libmrubycForWioLTEArduino)
* [mruby/cで始めるオリジナルIoTデバイス作り](https://magazine.rubyist.net/articles/0059/0059-original_mrubyc_iot_device.html)

本ライブラリは[Wio_cell_lib_for_Arduino](https://github.com/SeeedJP/Wio_cell_lib_for_Arduino)に依存します。

本ライブラリはmruby/c 1.2のソースコードを含んでいます。

作者は手元にWio3Gしか持っていないため、Wio3Gでの動作確認はしていますが、Wio LTEおよびWio LTE N1/NB1での動作確認は行なっておりません。

mruby/cでコードを書いたLED制御サンプル（クリックで再生）。
[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/eMzv5k-YnNI/0.jpg)](http://www.youtube.com/watch?v=eMzv5k-YnNI)

## Arduino IDE側の準備

1. Arduino IDEを起動し、 `スケッチ` -> `ライブラリをインクルード` -> `ライブラリを管理` をクリックし、ライブラリマネージャを起動します。
2. `Wio cell lib` で検索し、 `Wio cell lib for Arduino` の最新版をインストールします。

## Install

本リポジトリをcloneします.

```
$ git clone https://github.com/hiroeorz/mrubyc_for_Wio_cell_lib.git
```

リポジトリごとArduinoのライブラリディレクトリに保存します。

```
$ cp -r mrubyc_for_Wio_cell_lib  ~/Documents/Arduino/libraries/
```

あとは、スケッチの中で本ライブラリをインクルードします

* `スケッチ` -> `ライブラリのインクルード` -> `mruby/c for Wio cell lib` を選択。

## Document

* [Wioクラス](https://github.com/hiroeorz/mrubyc_for_Wio_cell_lib/blob/master/doc/Wio.md)

## Examples

`examples` ディレクトリ以下にサンプルを置いています。
各サンプルのディレクトリに移動し

```
$ make
```

とすると、rubyのソースからCのソースを吐き出します。
あとはArduino上でビルドし、 `Wio3G` , `Wio LTE` , `Wio LTE M1/NB1` にアップロードして実行してください。

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
#include <libmrubyc.h>
#include "task.c"

extern const uint8_t code[];

#define MEMSIZE (1024*30)
static uint8_t mempool[MEMSIZE];

void setup() {
  delay(1000);

  mrbc_init(mempool, MEMSIZE);
  mrbc_define_wio_methods();

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
mruby/c for Wio cell lib はBSD License(aka 3-clause license)のもとで配布いたします。
