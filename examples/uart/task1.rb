# -*- coding: utf-8 -*-
puts "SerialUART control from mruby/c"

wio = Wio.new
wio.power_supply_grove(true)   # Groveの電源をON
uart = SerialUART.new(9600)    # シリアルポートのスピードを9600bps,パリティ無しで初期化

while true
  uart.clear!                  # バッファをクリアする
  uart.print("abcedfg")        # データを書き込む
  uart.wait_ready(8)           # 8バイト読み込める状態になるまで待機
  str = uart.gets              # 改行(\r)までデータを読み込む(改行が\r以外、例えば\r\nなどの場合は第一引数で渡す)
  puts "recv: #{str}"
  sleep 3
end
