class ModbusRTU

  attr_reader :address, :function
  attr_accessor :data_list

  def initialize
    @address = nil
    @function = nil
    @data_list = []
  end

  def address=(val)
    puts "Invalid Address: #{val}" if val < 0 or 247 < val
    @address = val
  end

  def function=(val)
    puts "Invalid Function: #{val}" if val < 1 or 255 < val
    @function = val
  end

  #
  # バイナリ化して連結したデータにCRCを付加して返す。
  #
  def format
    if @address.nil?
      puts "Invalid Address : #{@address}" 
      return nil
    end

    if @function.nil?
      puts "Invalid Function: #{@function}"
      return nil
    end
    
    buffer = []
    buffer << @address
    buffer << @function

    @data_list.each do |data|
      buffer << data
    end

    crc = calc_crc(buffer)
    buffer << ( crc & 0x00FF)
    buffer << ((crc & 0xFF00) >> 8)
    return buffer
  end

  #
  # 受信したバイナリデータをパースしてModbusRTUオブジェクトを返す。
  #
  # CRCが一致しなかった場合は nil を返します。
  #
  def parse(array)
    address = array[0]
    function = array[1]
    data_list = array[2, array.size - 4]
    return nil unless check_response_crc(array)

    response = ModbusRTU.new
    response.address = address
    response.function = function
    response.data_list = data_list
    return response
  end

  def check_response_crc(array)
    data_size = array.size - 4
    crc_array = array[2 + data_size, 2]
    response_crc = (crc_array[1] << 8) | crc_array[0]
    crc = calc_crc(array[0, 2 + data_size])

    unless crc == response_crc
      puts "Invalid CRC in response: response_crc=#{response_crc} : crc=#{crc}"
      return nil
    end

    return response_crc == crc
  end

  #
  # CRCを計算して返す。
  #
  # bufferはNumeric型のArray。
  #
  def calc_crc(buffer)
    crc = 0xFFFF
    
    buffer.each do |byte|
      crc ^= byte

      8.times do
        carry_flag = crc & 1
        crc = crc >> 1
        crc ^= 0xA001 if carry_flag == 1
      end
    end

    return crc
  end

end