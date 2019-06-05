class MQTTClient

  def self.open(host, port = 1883, id = nil)
    puts "self.open-------------------------------------------"
    p 0
    client = MQTTClient.new
    success = client.connect(host, port, "hello")    

    if success
      client.call_block
    else
      puts "ERROR: MQTT connect failure!"
    end
  end

  def call_block
    puts "call_block----------------------------"
    yield self
    disconnect
  end

  def wait_loop(seconds)
    loop_msec(seconds * 1000)
  end

end
