# SHT35

本クラスは、Wio(3G, LTE, LTE N1/NB1)ボードGroveのI2Cで接続できる温度・湿度センサーのSHT35を制御するクラスです。

## 初期化

```ruby
wio = Wio.new
wio.power_supply_grove(true)   # Groveの電源をON
sht35 = SHT35.new              # 初期化
```

SHT35はIICのチャンネルが `0x44` と `0x45(default)` の２つあります。
省略された場合は `0x45` になります。
インスタンス生成時、第一引数にチャンネル番号を与えることができます。

```ruby
sht35 = SHT35.new(0x44)              # 初期化
```

### get_temperature

```ruby
tmp = sht35.get_temperature
```

#### 説明

温度を取得します。


### get_humidity

```ruby
tmp = sht35.get_humidity
```

#### 説明

湿度を取得します。


### get_temp_and_humi

```ruby
tmp,humi = sht35.get_temp_and_humi
```

#### 説明

湿度・湿度を一度に取得します。



