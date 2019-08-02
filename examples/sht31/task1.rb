puts "Get Temperature and Humidity from mruby/c"

wio = Wio.new
wio.power_supply_grove(true)

sht31 = SHT31.new

while true  
  tmp = sht31.get_temperature
  hum = sht31.get_humidity

  puts "tmperature:#{tmp}C humidity:#{hum}"
  sleep 1
end
