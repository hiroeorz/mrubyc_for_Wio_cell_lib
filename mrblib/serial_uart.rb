#
# SerialUART, mrubyc class library
#
#  Copyright (C) 2019 Shin Hiroe
#
#  This file is distributed under BSD 3-Clause License.
#

class SerialUART

  def wait_ready(wait_str_len = 1)
    while available() < wait_str_len
      sleep 0.1;
    end
  end

end
