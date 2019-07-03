puts "MQTT Client for mruby/c"

wio = Wio.new
wio.power_supply_cellular(true)
wio.turn_on_or_reset
sleep 1

wio.activate("soracom.io", "sora", "sora")
send_data = {:di => [1, 2, 3], :ai => [20, 30, 40], :alert => 0, :flag => false}

MQTTClient.open("beam.soracom.io", 1883, "") do |mqtt|
  mqtt.subscribe("test")
  mqtt.publish("test", send_data.to_json)

  while true
    data = mqtt.get_subscribed_data

    if data
      puts "recived! #{data["test"]}"
    end
    
    mqtt.wait_loop(1)
  end
end
