# MQTTClient

本ドキュメントはWio3G, LTE, LTE M1/NB1 でMQTTクライアント機能を実現するMQTTClientクラスについての説明を記します。
本ライブラリは、現状QoS=0のみ対応しております。
また、サブスクライブ後のコールバックは実装中です.

## クラスメソッド

### open

```ruby
MQTTClient.open("test.mosquitto.org", 1883, "mrubyc") do |mqtt|
 (...)
end
```

#### 引数

|引数|説明|
|:--|:--|
|host|MQTTブローカーのホスト名|
|port|MQTTブローカーのポート番号。デフォルトは1883|
|connect_id|任意のクライアントID|

#### 説明

MQTTブローカーに接続します。
ブロックから抜けると自動的にMQTTセッションを終了します。
MQTTブローカーへ接続するためには、事前に ```wio.activate``` を実行して回線への接続を完了しておく必要があります.

## インスタンスメソッド

### publish

```ruby
MQTTClient.open("test.mosquitto.org", 1883, "mrubyc") do |mqtt|
  mqtt.publish("test", "message from mruby/c on Wio Board (in block).")
end
```

#### 引数

|引数|説明|
|:--|:--|
|topic|送信メッセージのトピック|
|payload|送信メッセージのペイロード|

#### 説明

MQTTメッセージを送信します。

### subscribe

```ruby
MQTTClient.open("test.mosquitto.org", 1883, "mrubyc") do |mqtt|
  mqtt.subscribe("test")

  loop do
    mqtt.wait_loop(3)
  end
end
```

#### 引数

|引数|説明|
|:--|:--|
|topic|サブスクライブ対象のトピック|

#### 説明

サブスクライブを開始します。


### wait_loop

```ruby
MQTTClient.open("test.mosquitto.org", 1883, "mrubyc") do |mqtt|
  mqtt.subscribe("test")

  loop do
    mqtt.wait_loop(3)
  end
end
```

#### 引数

|引数|説明|
|:--|:--|
|seconds|受信待機時間|

#### 説明

`subscribe` を実行したあと、データを待機します。


## サンプル

```ruby:mqtt.rb
puts "MQTT Client for mruby/c"

wio = Wio.new
wio.power_supply_cellular(true)
wio.turn_on_or_reset
sleep 1
wio.activate("soracom.io", "sora", "sora")

MQTTClient.open("test.mosquitto.org", 1883, "mrubyc") do |mqtt|
  puts "ok connected."
  mqtt.publish("test", "topic from mruby/c on Wio Board (in block).")
  mqtt.subscribe("test")

  loop do
    mqtt.wait_loop(3)
  end
end
```

### connected?

```ruby
MQTTClient.open("test.mosquitto.org", 1883, "mrubyc") do |mqtt|
  mqtt.connected? #=> true or false
end
```

#### 説明

MQTTが接続状態であればture, 接続状態でなければfalseを返します。


