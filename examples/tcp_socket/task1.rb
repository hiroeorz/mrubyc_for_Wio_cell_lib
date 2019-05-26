puts "TCP Socket send recv from mruby/c"

wio = Wio.new
wio.power_supply_cellular(true)
wio.turn_on_or_reset
sleep 3

wio.activate("soracom.io", "sora", "sora")

signal = wio.get_received_signal_strength
puts "signal: #{signal} dBm"

sock = wio.tcp_socket_open("www.yahoo.co.jp", 80)
result = wio.socket_send(sock, "GET /\r\n")
puts "send #{result}"

recv = wio.socket_read(wio, sock, 14, 1024*10)
puts "recv #{recv}"

wio.socket_close(sock)
puts "socket closed"

wio.deactivate
puts "deactivated."

while true
  sleep 3
end
