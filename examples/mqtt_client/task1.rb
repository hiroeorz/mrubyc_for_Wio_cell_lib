puts "MQTT Client for mruby/c"

wio = Wio.new
wio.power_supply_cellular(true)
wio.turn_on_or_reset
sleep 1
wio.activate("soracom.io", "sora", "sora")

MQTTClient.open("test.mosquitto.org", 1883, "mrubyc") do |mqtt|
  puts "ok connected."
  mqtt.publish("test", "topic from mruby/c on Wio Board (in block).")
  mqtt.subscribe("test")

  loop do
    mqtt.wait_loop(3)
  end
end
