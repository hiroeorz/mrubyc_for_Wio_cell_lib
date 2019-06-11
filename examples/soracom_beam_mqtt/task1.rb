puts "MQTT Client for mruby/c"

wio = Wio.new
wio.power_supply_cellular(true)
wio.turn_on_or_reset
sleep 1

wio.activate("soracom.io", "sora", "sora")

imsi = wio.get_imsi
send_data = {"di" => [1, 2, 3], "ai" => [20, 30, 40], "alert" => 0, "flag" => false}

MQTTClient.open("beam.soracom.io", 1883, "") do |mqtt|
  puts "ok connected."
  
  3.times do
    mqtt.publish("ds", send_data.to_json)
  end

  puts "MQTT message sent to AWS IoT."
end

puts "connection closed."

loop do
  sleep 1
end
