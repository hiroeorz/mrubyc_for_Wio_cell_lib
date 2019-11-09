#
# MQTTClient, mrubyc class library
#
#  Copyright (C) 2019 Shin Hiroe
#
#  This file is distributed under BSD 3-Clause License.
#

class MQTTClient

  def self.open(host, port, connect_id, &block)
    client = MQTTClient.new
    success = client.connect(host, port, connect_id)

    if success
      block.call(client)
      client.disconnect
    else
      puts "ERROR: MQTT connect failure!"
    end
  end

  def open(host, port, connect_id, &block)
    success = connect(host, port, connect_id)

    if success
      block.call(self)
      disconnect
    else
      puts "ERROR: MQTT connect failure!"
    end
  end

  def wait_loop(seconds)
    loop_msec(seconds * 1000)
  end

  def receive_callback(topic, payload)
    @callback.call(topic, payload) if @callback
  end

end
