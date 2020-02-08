# coding: utf-8
class BME680

  #
  # センサーへの初期化処理を行い、センサーオブジェクトを生成する。
  # 初期化に失敗すると@device_init_resultにfalseをセットする。
  #
  def initialize(iic_addr = 0x76)
    @iic_addr = iic_addr
    @device_init_result = init(iic_addr)
  end

  #
  # デバイスに対する初期化が成功していればtrue、失敗していたらfalseを返す.
  #
  def device_init_result
    @device_init_result
  end
  
  def get_sensor_data
    result  = get_sensor_data_with_addr(@iic_addr)
    return nil if result.nil?
    temp, humi, press, gas = result
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
