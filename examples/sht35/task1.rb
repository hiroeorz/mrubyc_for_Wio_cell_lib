sleep 10
puts "Get Temperature and Humidity from mruby/c"
sleep 3

wio = Wio.new
wio.power_supply_grove(true)

sht35 = SHT35.new

while true  
  tmp,hum = sht35.get_temp_and_humi
  puts "tmperature:#{tmp}C humidity:#{hum}"
  puts "ok"
  sleep 1
end
