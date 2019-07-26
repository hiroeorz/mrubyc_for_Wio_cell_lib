puts "Get Temperature and Pressure from mruby/c"

wio = Wio.new
wio.power_supply_grove(true)

bmp280 = BMP280.new
puts "bmp280 is enable? -> #{bmp280.enable?}"

while true  
  if bmp280.enable?
    tmp = bmp280.get_temperature
    press = bmp280.get_pressure
    altitude = bmp280.get_altitude
    puts "tmperature: #{tmp}C, pressure: #{press}Pa altitude: #{altitude}m"
    sleep 1
  end
end
