# Wio

本ドキュメントは[Wio cell lib for Arduino リファレンスマニュアル](https://seeedjp.github.io/Wiki/Wio_cell_lib_for_Arduino/reference-ja.html)のmruby/c版になります。

## 初期化

```ruby
wio = Wio.new
```

## インスタンスメソッド

### power_supply_cellular

```ruby
wio.power_supply_cellular(on)
```

#### 引数

|引数|説明|
|:--|:--|
|on|電源供給のオン/オフ。オンしたいときはtrue、オフしたいときはfalseを指定します。|

#### 説明

通信モジュールの電源供給をオン/オフします。
通信モジュールは電源供給オンの後に、起動操作（TurnOnOrReset）しないと利用できません。
本関数を実行した後の、通信モジュールの操作は0.5秒以上待ってください。（通信モジュールの動作が安定するまで待つ。）

### power_supply_led

```ruby
wio.power_supply_led(on)
```

#### 引数

|引数|説明|
|:--|:--|
|on|電源供給のオン/オフ。オンしたいときはtrue、オフしたいときはfalseを指定します。|

#### 説明

フルカラーLEDへの電源供給をオン/オフします。

### power_supply_grove

```ruby
wio.power_supply_grove(on)
```

#### 引数

|引数|説明|
|:--|:--|
|on|電源供給のオン/オフ。オンしたいときはtrue、オフしたいときはfalseを指定します。|

#### 説明

Groveコネクター D20/A4/A6/I2C/UARTの電源供給をオン/オフします。
> Groveコネクター D38の電源は常時オンです。

### led_set_rgb

```ruby
wio.led_set_rgb(red, green, blue)
```

#### 引数

|引数|説明|
|:--|:--|
|red|赤色の度合い。0～255を指定します。|
|green|緑色の度合い。0～255を指定します。|
|blue|青色の度合い。0～255を指定します。|

#### 説明

フルカラーLEDを点灯します。
消灯したいときは、red/green/blue全てに0を指定します。

### turn_on_or_reset

```ruby
wio.turn_on_or_reset
```

#### 戻り値

|説明|
|:--|
|成功したときはtrue、失敗したときはfalseを返します。|

#### 説明

通信モジュールを起動操作します。
通信モジュールが電源オンしていないときは電源オン、電源オンしているときはリセットします。
本関数を実行する前に、通信モジュールへ電源供給（power_supply_cellular）してください。

### turn_off

```ruby
wio.turn_off
```

#### 戻り値

|説明|
|:--|
|成功したときはtrue、失敗したときはfalseを返します。|

#### 説明

通信モジュールを停止操作します。

### get_imei

```ruby
wio.get_imei
```

#### 戻り値

|説明|
|:--|
|成功したときはIMEIの文字列、失敗したときはnilを返します。|

#### 説明

IMEIを取得します。

### get_imsi

```ruby
wio.get_imsi
```

#### 戻り値

|説明|
|:--|
|成功したときはIMSIの文字列、失敗したときはnilを返します。|

#### 説明

SIMのIMSIを取得します。

### get_phone_number

```ruby
wio.get_phone_number
```

#### 戻り値

|説明|
|:--|
|成功したときは電話番号の文字列、失敗したときはnilを返します。|

#### 説明

取り付けられたSIMの電話番号を取得します。

### get_received_signal_strength

```ruby
wio.get_received_signal_strength
```

#### 戻り値

|説明|
|:--|
|受信信号強度[dBm]を返します。失敗したときはnilを返します。|

#### 説明

通信モジュールが受信している信号強度[dBm]を取得します。

### get_time

```ruby
time = wio.get_time
puts "#{time['year']} / #{time['month']} / #{time['day']} #{time['hour']}:#{time['min']}:#{time['sec']}"
```

#### 戻り値

|説明|
|:--|
|成功したときはハッシュオブジェクト、失敗したときはnilを返します。|

#### 説明

通信モジュールが保持している日時を取得します。
ハッシュオブジェクトから、パラメータ名で値を取り出せます。


### wait_for_cs_registration

```ruby
wio.wait_for_cs_registration(timeout = 120000)
```

#### 引数

|引数|説明|
|:--|:--|
|timeout|タイムアウト時間[ミリ秒]。|

#### 戻り値

|説明|
|:--|
|成功したときはtrue、失敗したときはfalseを返します。|

#### 説明

CSネットワークに登録完了するまで待ちます。

### wait_for_ps_registration

```ruby
wio.wait_for_ps_registration(timeout = 120000)
```

#### 引数

|引数|説明|
|:--|:--|
|timeout|タイムアウト時間[ミリ秒]。|

#### 戻り値

|説明|
|:--|
|成功したときはtrue、失敗したときはfalseを返します。|

#### 説明

PSネットワークに登録完了するまで待ちます。

### activate

```ruby
wio.activate("soracom.io", "sora", "sora")
```

#### 引数

|引数|説明|
|:--|:--|
|apn|接続先APN|
|username|ユーザー名|
|password|パスワード|
|wait_time|タイムアウト時間[ミリ秒]。|

#### 戻り値

|説明|
|:--|
|成功したときはtrue、失敗したときはfalseを返します。|

#### 説明

データ通信を有効にします。

### deactivate

```ruby
wio.deactivate
```

#### 戻り値

|説明|
|:--|
|成功したときはtrue、失敗したときはfalseを返します。|

#### 説明

データ通信を無効にします。

### tcp_socket_open

```ruby
wio.tcp_socket_open(host, port)
```

#### 引数

|引数|説明|
|:--|:--|
|host|接続先のホスト名。|
|port|接続先のポート番号。|

#### 戻り値

|説明|
|:--|
|成功したときは接続ID、失敗したときはnilを返します。|

#### 説明

指定したホスト名、ポート番号に、ソケット通信を接続します。
同時に12個まで接続することが可能です。

### udp_socket_open

```ruby
wio.udp_socket_open(host, port)
```

#### 引数

|引数|説明|
|:--|:--|
|host|接続先のホスト名。|
|port|接続先のポート番号。|

#### 戻り値

|説明|
|:--|
|成功したときは接続ID、失敗したときはnilを返します。|

#### 説明

指定したホスト名、ポート番号に、UDPソケット通信を接続します。
同時に12個まで接続することが可能です。

### socket_send

```ruby
wio.socket_send(connectId, data)
```

#### 引数

|引数|説明|
|:--|:--|
|connectId|接続ID。|
|data|送信するデータ。|

#### 戻り値

|説明|
|:--|
|成功したときはtrue、失敗したときはfalseを返します。|

#### 説明

指定した接続へデータを送信します。
一度に送信できるデータは1460バイト以下です。

### socket_receive

```ruby
wio.socket_receive(connectId, data_size, timeout = 120000)
```

#### 引数

|引数|説明|
|:--|:--|
|connectId|接続ID。|
|data_size|dataのバイト数。|
|timeout|タイムアウト時間[ミリ秒]。|

#### 戻り値

|説明|
|:--|
|受信したデータがあるときは文字列、なければnilを返す。|

### socket_read

```ruby
wio.socket_read(sock, bytes, buffer_size = 1024, timeout = 120)
```

#### 引数

|引数|説明|
|:--|:--|
|connectId|接続ID。|
|data_size|dataのバイト数。|
|buffer_size|受信バッファのサイズ|
|timeout|タイムアウト時間[ミリ秒]。|

#### 戻り値

|説明|
|:--|
|受信したデータがあるときは文字列、なければnilを返す。|

#### 説明

指定した接続に受信したデータを取得します。
受信したデータが無いときはnilを返します。
タイムアウト時間を指定したときは、その時間、受信を待ちます。

### socket_close

```ruby
wio.socket_close(connectId)
```

#### 引数

|引数|説明|
|:--|:--|
|connectId|接続ID。|

#### 戻り値

|説明|
|:--|
|成功したときはtrue、失敗したときはfalseを返します。|

#### 説明

指定した接続をクローズします。

### http_get

```ruby
wio.http_get(url, buffer_size = 1024)
```

#### 引数

|引数|説明|
|:--|:--|
|url|接続するURL。例："http://test.co.jp", "https://test.co.jp" |
|buffer_size|データの受信に用いるバッファのサイズ|

#### 戻り値

|説明|
|:--|
|成功したときはデータの文字列、失敗したときはnilを返します。|

#### 説明

指定したURLから、HTTP通信でGETします。

### http_post

```ruby
wio.http_post(url, data)
```

#### 引数

|引数|説明|
|:--|:--|
|url|接続するURL。例："http://test.co.jp", "https://test.co.jp" |
|data|送信するデータ。|

#### 戻り値

|説明|
|:--|
|HTTPステータスコード。|

#### 説明

指定したURLへ、HTTP通信でPOSTします。

### send_ussd

```ruby
wio.send_ussd(in)
```

#### 引数

|引数|説明|
|:--|:--|
|in|送信するデータ。|
|out|受信したデータを取得する変数。|

#### 戻り値

|説明|
|:--|
|成功したときは受信したデータ、失敗したときはnilを返します。|

#### 説明

USSDでメッセージ交換します。

### system_reset

```ruby
wio.system_reset
```

#### 説明

CPUをリセットします。
