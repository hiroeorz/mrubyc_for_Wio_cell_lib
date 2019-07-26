# SHT31

本クラスは、Wio(3G, LTE, LTE N1/NB1)ボードGroveのI2Cで接続できる温度・湿度センサーのSHT31を制御するクラスです。

## 初期化

```ruby
wio = Wio.new
wio.power_supply_grove(true)   # Groveの電源をON
sht31 = SHT31.new              # 初期化
```

### get_temperature

```ruby
tmp = sht31.get_temperature
```

#### 説明

温度を取得します。


### get_humidity

```ruby
tmp = sht31.get_humidity
```

#### 説明

湿度を取得します。



