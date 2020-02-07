# mruby/c for Wio(3G, LTE, LTE M1/NB1)

## About
mruby/c for Wio はSeeed社が開発した以下の基板上で [mruby/c](https://github.com/mrubyc/mrubyc) を動作させるためのライブラリです。

* [Wio3G SORACOM EDITION](https://soracom.jp/products/module/wio_3g_soracom_edition/)
* [Wio LTE JP Version](https://soracom.jp/products/module/wio_lte/)
* [Wio LTE M1/NB1](https://soracom.jp/products/module/wio_lte_m1_nb1/)

mruby/cでコードを書いたLED制御サンプル（クリックで再生）。
[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/eMzv5k-YnNI/0.jpg)](http://www.youtube.com/watch?v=eMzv5k-YnNI)

## Arduino IDE側の準備

1. Arduino IDEを起動し、 `スケッチ` -> `ライブラリをインクルード` -> `ライブラリを管理` をクリックし、ライブラリマネージャを起動します。
2. `Wio 3G` `Wio LTE M1/NB1` の場合は、 `Wio cell lib` で検索し、 `Wio cell lib for Arduino` の最新版をインストールします。
2. `Wio LTE` の場合は、 `Wio LTE` で検索し、 `Wio LTE for Arduino` の最新版をインストールします。

以下の3つのライブラリをインストールします。いずれもArduinoIDEからインストール可能ですが、IDEから入れるとコンパイルエラーが発生するためgithubからmasterブランチをcloneしてください.

### Arduino Client for MQTT のインストール

1. [SeeedJP/pubsubclient](https://github.com/SeeedJP/pubsubclient)のREADMEに従い、 `Arduino Client for MQTT` をインストールします。

### Grove_SHT31_Temp_Humi_Sensor のインストール

[Seeed-Studio/Grove_SHT31_Temp_Humi_Sensor](https://github.com/Seeed-Studio/Grove_SHT31_Temp_Humi_Sensor)をインストールします.

```
$ cd ~/Documents/Arduino/libraries/
# git clone https://github.com/Seeed-Studio/Grove_SHT31_Temp_Humi_Sensor.git
```

### Seeed_SHT35 のインストール

[Seeed-Studio/Seeed_SHT35](https://github.com/Seeed-Studio/Seeed_SHT35)をインストールします.

```
$ cd ~/Documents/Arduino/libraries/
# git clone https://github.com/Seeed-Studio/Seeed_SHT35.git
```

### Grove_BMP280 のインストール

[Seeed-Studio/Grove_BMP280](https://github.com/Seeed-Studio/Grove_BMP280)をインストールします.

```
$ cd ~/Documents/Arduino/libraries/
# git clone git@github.com:Seeed-Studio/Grove_BMP280.git
```

### Grove_BME680 のインストール

[Seeed-Studio/Seeed_BME680](https://github.com/Seeed-Studio/Seeed_BME680/blob/master/examples/seeed_bme680_test/seeed_bme680_test.ino)をインストールします.

```
$ cd ~/Documents/Arduino/libraries/
# git clone git@github.com:Seeed-Studio/Seeed_BME680.git
```

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

基本クラス
* [Wioクラス](https://github.com/hiroeorz/mrubyc_for_Wio_cell_lib/blob/master/doc/Wio.md)
* [SerialUARTクラス](https://github.com/hiroeorz/mrubyc_for_Wio_cell_lib/blob/master/doc/SerialUART.md)
* [MQTTClientクラス](https://github.com/hiroeorz/mrubyc_for_Wio_cell_lib/blob/master/doc/MQTT.md)
* [JSONクラス](https://github.com/hiroeorz/mrubyc_for_Wio_cell_lib/blob/master/doc/JSON.md)

Groveセンサー
* [SHT31クラス](https://github.com/hiroeorz/mrubyc_for_Wio_cell_lib/blob/master/doc/SHT31.md)
* [SHT35クラス](https://github.com/hiroeorz/mrubyc_for_Wio_cell_lib/blob/master/doc/SHT35.md)
* [BMP280クラス](https://github.com/hiroeorz/mrubyc_for_Wio_cell_lib/blob/master/doc/BMP280.md)

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

* 初期状態で Wio <-> PC 間の通信スピードは `115200bps` です。  `puts` などの出力を見る場合はシリアルモニタの速度を `115200bps` に設定してください。
* 通信速度を変更する場合は `Wio` クラスのインスタンスを生成する際に引数で通信速度を渡してください・
  * 例: `wio = Wio.new(9600)`


また、簡易なJSONパーサ、ジェネレータも持っています。

```ruby:examples/json/task1.rb
  {:di => [1, 2, 3], :ai => [20, 30, 40], :alert => 0, :flag => false}.to_json
  #=> "{\"di\":[1,2,3],\"ai\":[20,30,40],\"alert\":0,\"flag\":false}"

  JSON.parse('{"name": "hiroe", "age": 43, "weight": 70.2, "lover": null}')
  #=> {"name" => "hiroe", "age" => 43, "weight" => 70.2, "lover" => nil}
```

MQTTプロトコルを通じてSORACOM Beamに接続するmrubycコードは以下のように使います。

```ruby:examples/mqtt/task1.rb
wio = Wio.new
wio.power_supply_cellular(true)
wio.turn_on_or_reset
sleep 1

wio.activate("soracom.io", "sora", "sora")
send_data = {:di => [1, 2, 3], :ai => [20, 30, 40], :alert => 0, :flag => false}

MQTTClient.open("beam.soracom.io", 1883, "") do |mqtt|
  mqtt.subscribe("test")
  mqtt.publish("test", send_data.to_json)

  while true
    data = mqtt.get_subscribed_data

    if data
      puts "recived! #{data["test"]}"
    end
    
    mqtt.wait_loop(1)
  end
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

## Thanks

本ライブラリを実装するにあたり、kishimaさんの以下の電子書籍やレポジトリ等を参考にさせていただいています。
* [mruby/cの小さな世界](https://silentworlds.info/2018/09/17/post-620/)
* [kishima/libmrubycForWioLTEArduino](https://github.com/kishima/libmrubycForWioLTEArduino)
* [mruby/cで始めるオリジナルIoTデバイス作り](https://magazine.rubyist.net/articles/0059/0059-original_mrubyc_iot_device.html)

## Other

* 本ライブラリは[Wio_cell_lib_for_Arduino](https://github.com/SeeedJP/Wio_cell_lib_for_Arduino)および[Wio LTE for Arduino](https://github.com/SeeedJP/WioLTEforArduino)に依存します。
* 本ライブラリはmruby/c 2.0のソースコードを含んでいます。
* 作者は手元にWio3GとWioLTEしか持っていないため、Wio LTE N1/NB1での動作確認は行なっておりません。


## License
mruby/c for Wio cell lib はBSD License(aka 3-clause license)のもとで配布いたします。
