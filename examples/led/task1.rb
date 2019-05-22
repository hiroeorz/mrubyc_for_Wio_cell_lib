puts "LED control from mruby/c"

wio = Wio.new
wio.power_supply_led(true)
rgb = [255, 0, 0]

while true
  last = rgb.pop
  rgb.unshift(last)
  wio.led_set_rgb(rgb[0], rgb[1], rgb[2])
  sleep 0.3
end
