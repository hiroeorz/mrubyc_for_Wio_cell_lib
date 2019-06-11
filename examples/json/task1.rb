puts "JSON for mruby/c"

obj = {:di => [1, 2, 3], :ai => [20, 30, 40], :alert => 0, :flag => false}
json = obj.to_json
p json

obj = JSON.parse('"abc"')
p obj

obj = JSON.parse('true')
p obj

obj = JSON.parse(' ["foo", "bar"]')
p obj

obj = JSON.parse('  {"name": "hiroe", "age": 43, "weight": 70.2, "lover": NULL, "fb": "foobaa"}')
p obj

obj = JSON.parse('{"membars": ["hiroe", "ito", "takeshita"]}')
p obj

# todo
#obj = JSON.parse('{"me": {"name": "hiroe", "age": 43}}')
#p obj

loop do
  sleep 1
end
