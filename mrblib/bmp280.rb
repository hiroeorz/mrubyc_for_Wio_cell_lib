class BMP280

  def initialize(iic_addr = 0x77)
    @iic_addr = iic_addr
    init(iic_addr)
  end

  def enable?
    enable_with_addr(@iic_addr)
  end

  def get_temperature
    get_temperature_with_addr(@iic_addr)
  end

  def get_pressure
    get_pressure_with_addr(@iic_addr)
  end

  def get_altitude
    get_altitude_with_addr(@iic_addr)
  end

end
