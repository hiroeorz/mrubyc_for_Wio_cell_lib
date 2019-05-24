# mruby/c for Wio3G Soracom Edition

## About
mruby/c for Wio3G Soracom Edition はSeeed社が開発し、ソラコム社が発売する[Wio3G SORACOM EDITION](https://soracom.jp/products/module/wio_3g_soracom_edition/)上で mruby/c を動作させるためのライブラリです。

![Wio3G SORACOM EDITION](https://soracom.jp/img/products_wio_3g_soracom_edition.png, "画像")

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

## Examples

`examples` ディレクトリ以下にサンプルを置いています。
各サンプルのディレクトリに移動し

```
$ make
```

とすると、rubyのソースからCのソースを吐き出します。
あとはArduino上でビルドし、Wio3Gにアップロードして実行してください。

## License
mruby/c for Wio3G Soracom Edition はBSD License(aka 3-clause license)のもとで配布いたします。
