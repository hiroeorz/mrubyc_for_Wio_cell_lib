puts "Get Time from mruby/c"

wio = Wio.new
wio.power_supply_cellular(true)
wio.turn_on_or_reset
sleep 1

while true
  signal = wio.get_received_signal_strength
  puts "signal: #{signal} dBm"
  sleep 3
end
