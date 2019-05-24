puts "HTTP GET and POST from mruby/c"

wio = Wio3G.new
wio.power_supply_cellular(true)
wio.turn_on_or_reset
sleep 3

wio.activate

signal = wio.get_received_signal_strength
puts "signal: #{signal} dBm"

# HTTP GET
recv = wio.http_get("http://abehiroshi.la.coocan.jp", 1024)
puts "recv(GET) #{recv}"

# HTTP POST
data = "{\"name\":\"shin\"}"
status_code = wio.http_post("http://abehiroshi.la.coocan.jp", data)
puts "HTTP STATUS CODE: #{status_code}"

wio.deactivate
puts "deactivated."

while true
  sleep 3
end
