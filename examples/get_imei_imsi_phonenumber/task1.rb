puts "Get IMEI from mruby/c"

wio = Wio.new
wio.power_supply_cellular(true)

wio.turn_on_or_reset
sleep 1

while true
  imei = wio.get_imei
  puts "IMEI: #{imei}"

  imsi = wio.get_imsi
  puts "IMSI: #{imsi}"

  phone_number = wio.get_phone_number
  puts "PhoneNumber: #{phone_number}"  

  sleep 3
end
