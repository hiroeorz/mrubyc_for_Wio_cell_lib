#
# Wio, mrubyc class library
#
#  Copyright (C) 2019 Shin Hiroe
#
#  This file is distributed under BSD 3-Clause License.
#

class Wio

  def socket_read(sock, bytes, buffer_size = 1024, timeout = 120)
    recv = ""
    counter = timeout

    while true
      str = socket_receive(sock, buffer_size)
      recv << str if str

      if recv and recv.length >= bytes
        break
      end

      counter -= 0.1
      break if counter < 0.0
      sleep 0.1
    end

    return recv[0, bytes]
  end

end
