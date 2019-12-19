class SHT35

  def initialize(iic_addr = 0x45)
    @iic_addr = iic_addr
    init(iic_addr)
  end

  def enable?
    !heater_status.nil?
  end

  def get_temperature
    get_temperature_with_addr(@iic_addr)
  end

  def get_humidity
    get_humidity_with_addr(@iic_addr)
  end

  def get_temp_and_humi
    result = get_temp_and_humi_with_addr(@iic_addr)
    return [nil, nil] if result.nil?
    return result
  end

  def heater_status
    heater_status_with_addr(@iic_addr)
  end

end
