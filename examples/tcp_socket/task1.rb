puts "TCP Socket send recv from mruby/c"

wio = Wio.new
wio.power_supply_cellular(true)
wio.turn_on_or_reset

sleep 5
wio.activate

sleep 5
sock = wio.tcp_socket_open("some.smpt.com", 25) # change your own smtp host

result = wio.socket_send(sock, "HELO mruby\r\n")
puts "send #{result}"

sleep 5
recv = wio.socket_receive(sock, 1024)
puts "recv #{recv}"

wio.socket_close(sock)
puts "socket closed"

wio.deactivate
puts "deactivated."

while true
  sleep 3
end
