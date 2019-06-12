class MyClass

  def my_loop(array)
    array.each do |v|
      self.tara(v)
    end
  end

  def tara(val)
    val
  end

end

my = MyClass.new
my.my_loop([1,2,3])

loop do
  sleep 1
end
