# -*- coding: utf-8 -*-
#
#  JSON Generator to mrubyc classes. 
#
#  Copyright (C) 2019 Shin Hiroe
#
#  This file is distributed under BSD 3-Clause License.
#

class JSONParser
  WHITE_SPACES = [" ", "\t", "\r", "\n"]
  NUMBER_LETTERS = '0123456789+-.eE'

  def self.parse(text)
    JSONParser.new(text).parse_value
  end

  def initialize(s)
    @s = s
  end

  def parse_value
    split_objects(@s)
  end

  def skip_white_spaces(s, idx)
    while true
      if " "   == s[idx] or
          "\t" == s[idx] or
          "\r" == s[idx] or
          "\n" == s[idx]
        idx += 1
      else
        break
      end
    end

    return idx
  end

  def search_object_end(mark, s, idx)
    while idx < s.length
      idx += 1
      if mark == s[idx]
        break
      end
    end

    return idx
  end

  def split_objects(s)
    split_one_object(s, 0)
  end

  def parse_object(obj)
    myself = self
    str = obj[1, obj.length - 2]

    kv_array = str.split(",")
    valid_index = 0

    kv_array.each_with_index do |str, idx|
      next if idx == 0

      if str.include?(":")
        valid_index = idx
      else
        kv_array[valid_index] = [kv_array[valid_index], str].join(",")
      end
    end

    hash = {}

    kv_array.each do |kv_str|
      next unless kv_str.include?(":")
      kv_array = kv_str.split(":")
      k = kv_array[0]
      v = kv_array[1]
      key = myself.split_one_object(k, 0)
      val = myself.split_one_object(v, 0)
      hash[key] = val
    end

    hash
  end

  def parse_array(obj)
    myself = self
    str = obj[1, obj.length - 2]
    return str.split(",").collect{ |e| myself.split_one_object(e, 0) }
  end

  def parse_number(obj)
    if obj.include?(".")
      return obj.to_f
    else
      return obj.to_i
    end
  end

  def parse_string(obj)
    obj[1, (obj.length - 2)]
  end

  def is_number?(str)
    is_number = true

    str.each_byte do |s|
      char_result = false

      NUMBER_LETTERS.each_byte do |c|
        char_result = true if s == c
      end

      if char_result == false
        is_number = false
        break
      end
    end

    return is_number
  end

  def split_one_object(s, idx)
    idx = skip_white_spaces(s, idx)
    start_chr = s[idx, 1]
    object_start = idx

    object_end   = if    start_chr == "{"
                     search_object_end("}", s, idx)
                   elsif start_chr == "["
                     search_object_end("]", s, idx)
                   else
                     search_object_end(",", s, idx)
                   end
    obj = s[object_start, (object_end - object_start + 1)]

    return case start_chr
           when '{'
             parse_object(obj)
           when '['
             parse_array(obj)
           when '"'
             parse_string(obj)
           when "N"
             nil
           when "f"
             false
           when "t"
             true
           else
             if is_number?(obj)
               parse_number(obj)
             else
               obj
             end
           end
  end

end

class JSON < JSONParser
end
