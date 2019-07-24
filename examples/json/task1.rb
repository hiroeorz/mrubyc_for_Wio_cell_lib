puts "JSON for mruby/c"

while true # check memory leak.

  obj = {:di => [1, 2, 3], :ai => [20, 30, 40], :alert => 0, :flag => false}
  json = obj.to_json
  p json

  obj = JSON.parse('12')
  p obj

  obj = JSON.parse('"abc"')
  p obj

  obj = JSON.parse('true')
  p obj

  obj = JSON.parse(' ["foo", "bar"]')
  p obj

  obj = JSON.parse('  {"name": "hiroe", "age": 43, "weight": 70.2, "lover":null, "fb": "foobaa"}')
  p obj

  obj = JSON.parse('{"membars": ["hiroe", "ito", "takeshita"]}')
  p obj

  obj = JSON.parse('{"counts": [1, 2, 3]}')
  p obj

  obj = JSON.parse('{"me": {"name": "hiroe", "age": 43}}')
  p obj

  # sample
  obj = JSON.parse('{"code":3, "bits":[1,2], "request_code":"D9658B82-5A0A-4AF4-8CB6-73E0B39BEE6D"}')
  p obj

  puts "------------- finish -------------"
  puts

  sleep 1
end
