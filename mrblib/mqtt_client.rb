class MQTTClient

  def self.open(host, port, connect_id, &block)
    client = MQTTClient.new
    success = client.connect(host, port, connect_id)

    if success
      block.call(client)
    else
      puts "ERROR: MQTT connect failure!"
    end
  end

  def wait_loop(seconds)
    loop_msec(seconds * 1000)
  end

end
