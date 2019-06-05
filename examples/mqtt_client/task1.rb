puts "MQTT Client for mruby/c"

wio = Wio.new
wio.power_supply_cellular(true)
wio.turn_on_or_reset
sleep 1

wio.activate("soracom.io", "sora", "sora")
mqtt_client = MQTTClient.new()
success = mqtt_client.connect("test.mosquitto.org")

MQTTClient.open("test.mosquitto.org") do |mqtt_client|
  puts "ok connected."
end

=begin
if success
  puts "ok connected."
  result = mqtt_client.subscribe("test")
  puts "subscribe result: #{result}"

  mqtt_client.publish("test", "topic from mruby/c on Wio Board.")
  puts "publish result:   #{result}"

  mqtt_client.wait_loop(3)
else
  puts "error: connect failure."
end

mqtt_client.disconnect
=end

while true
  sleep 30
end
