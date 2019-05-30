puts "hello mruby! I am task1 !"

$mutex = Mutex.new
$array = [0, 0, 0]

while true
  sleep 1
  p $array

  $mutex.lock
  $array[0] += 1
  $mutex.unlock
end
