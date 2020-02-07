class BME680

  def initialize(iic_addr = 0x77)
    @iic_addr = iic_addr
    init(iic_addr)
  end

  def get_sensor_data
    temp, humi, press, gas = get_sensor_data_with_addr(@iic_addr)
    return BME680Result.new(temp, humi, press, gas)
  end

end

class BME680Result

  def initialize(temp, humi, press, gas)
    @temp = temp
    @humi = humi
    @press = press
    @gas = gas
  end

  def temperature
    @temp
  end

  def humidity
    @humi
  end

  def pressure
    @press
  end

  def gas
    @gas
  end
  
end
