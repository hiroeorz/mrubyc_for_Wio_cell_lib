puts "Get Time from mruby/c"

wio = Wio.new
wio.power_supply_cellular(true)
wio.turn_on_or_reset
sleep 5

while true
  time = wio.get_time
  puts "Time: #{time["year"]}/#{time["month"]}/#{time["day"]} #{time["hour"]}:#{time["min"]}:#{time["sec"]}"
  sleep 3
end
