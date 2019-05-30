puts "hello mruby! I am task2 !"

while true
  sleep 2
  puts "task2"

  $mutex.lock
  $array[1] += 1
  $mutex.unlock
end
