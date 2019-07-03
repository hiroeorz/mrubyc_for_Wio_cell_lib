puts "MQTT Client for mruby/c"

wio = Wio.new
wio.power_supply_cellular(true)
wio.power_supply_led(true)
wio.turn_on_or_reset
sleep 1
wio.activate("soracom.io", "sora", "sora")

MQTTClient.open("test.mosquitto.org", 1883, "mrubyc") do |mqtt|
  puts "ok connected"
  mqtt.publish("test", "topic from mruby/c on Wio Board.")
  mqtt.subscribe("test")

  while true
    data = mqtt.get_subscribed_data
    if data
      puts "recived! #{data["test"]}"
    end

    mqtt.wait_loop(1)
  end
end

puts "finished."

