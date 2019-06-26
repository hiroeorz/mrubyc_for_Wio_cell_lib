#
# MQTTClient, mrubyc class library
#
#  Copyright (C) 2019 Shin Hiroe
#
#  This file is distributed under BSD 3-Clause License.
#

class MQTTClient

  def initialize
    @callback = Proc.new{ puts "call from proc object"}
    @_received_data = nil
  end

  def get_subscribed_data
    data = @_received_data
    return nil if @_received_data.nil?
    @_received_data = nil
    return data
  end

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

  def wait_loop(seconds)
    loop_msec(seconds * 1000)
  end

  def receive_callback(topic, payload)
    @callback.call(topic, payload) if @callback
  end

end
