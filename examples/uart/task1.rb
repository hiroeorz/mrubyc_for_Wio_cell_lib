# -*- coding: utf-8 -*-
puts "SerialUART control from mruby/c"

wio = Wio.new(115200)
wio.power_supply_grove(true)   # Groveの電源をON
uart = SerialUART.new(9600, 2)    # シリアルポートのスピードを9600bps,パリティ偶数で初期化

def checkcode(str)
  check_code = str[0].ord
  i = 0

  str.each_byte do |b|
    if i > 0
      check_code = check_code ^ b
    end

    i += 1
  end

  return sprintf("%02X", check_code)
end

def hex_str(val, len = 4)
  return sprintf("%0#{len}X", val)
end

def request_data(val)
  str = "@00R#{hex_str(val)}"
  return "#{str}#{checkcode(str)}*\r"
end

while true
  uart.clear!                  # バッファをクリアする
  str = request_data(0)
  puts "send: #{str}"
  uart.print(str)

  #uart.print("@00R000012*\r")        # データを書き込む
  uart.wait_ready(8)           # 8バイト読み込める状態になるまで待機
  str = uart.gets              # 改行(\r)までデータを読み込む(改行が\r以外、例えば\r\nなどの場合は第一引数で渡す)
  puts "recv: #{str}"
  sleep 3
end
