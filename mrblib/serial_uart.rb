#
# SerialUART, mrubyc class library
#
#  Copyright (C) 2019 Shin Hiroe
#
#  This file is distributed under BSD 3-Clause License.
#

class SerialUART

  WAIT_READY_SLEEP_SEC = 0.1

  def wait_ready(wait_str_len = 1, max_wait_count = 10)
    count = 0

    while available() < wait_str_len
      return false if count >= max_wait_count
      count += 1
      sleep WAIT_READY_SLEEP_SEC
    end

    return true
  end

end
