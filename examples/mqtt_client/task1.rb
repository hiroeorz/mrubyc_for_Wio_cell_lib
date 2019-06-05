puts "MQTT Client for mruby/c"

wio = Wio.new
wio.power_supply_cellular(true)
wio.turn_on_or_reset
sleep 1

wio.activate("soracom.io", "sora", "sora")
mqtt_client = MQTTClient.new()
success = mqtt_client.connect("test.mosquitto.org")

if success
  puts "ok connected."
  mqtt_client.publish("test", "topic from mruby/c on Wio Board.")
  puts "message published."
else
  puts "error: connect failure."
end

mqtt_client.disconnect

while true
  sleep 30
end
