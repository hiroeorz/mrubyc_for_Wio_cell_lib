# JSON

本ドキュメントはWio基板上で動作するJSONクラスについての説明を記します。

サンプルコードは[mrubyc_for_Wio_cell_lib/examples/json/task1.rb](https://github.com/hiroeorz/mrubyc_for_Wio_cell_lib/blob/master/examples/json/task1.rb)を参照してください.

## ジェネレータ

オブジェクトをJSON文字列に変換するには、オブジェクトに対して `to_json` メソッドをコールしてください。

```ruby
obj = {:di => [1, 2, 3], :ai => [20, 30, 40], :alert => 0, :flag => false}
json = obj.to_json

=> "{\"di\":[1,2,3],\"ai\":[20,30,40],\"alert\":0,\"flag\":false}"
```


## パーサ

JSON文字列をパースしてオブジェクトを生成するには、 `JSON.parse(json)` を実行します。

```ruby:Fixnum
obj = JSON.parse('12')
```

```ruby:String
obj = JSON.parse('"abc"')
```

```ruby:TrueClass,FalseClass
obj = JSON.parse('true')
```

```ruby:Array
obj = JSON.parse(' ["foo", "bar"]')
```

```ruby:Hash
obj = JSON.parse('  {"name": "hiroe", "age": 43, "weight": 70.2, "lover": NULL, "fb": "foobaa"}')
```

```ruby:Hash(Array value)
obj = JSON.parse('{"membars": ["hiroe", "ito", "takeshita"]}')
```

```ruby:Hash(Hash value)
obj = JSON.parse('{"me": {"name": "hiroe", "age": 43}}')
```
