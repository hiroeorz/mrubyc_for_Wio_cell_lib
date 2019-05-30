puts "hello mruby! I am task3 !"

while true
  sleep 0.3
  puts "task3"

  $mutex.lock
  $array[2] += 0.1
  $mutex.unlock
end
