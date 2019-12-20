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

  def reset_check
    reset_check_with_addr(@iic_addr)
  end

  def soft_reset
    soft_reset_with_addr(@iic_addr)
  end

  def change_heater_status(status)
    status_num = status ? 1 : 0
    change_heater_status_with_addr(@iic_addr, status_num)
  end

  def read_reg_status
    read_reg_status_with_addr(@iic_addr)
  end

end
