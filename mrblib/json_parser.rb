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

  def search_object_end(start_mark, end_mark, s, idx)
    point = 0

    while idx < s.length
      idx += 1

      if start_mark != end_mark and start_mark == s[idx, 1]
        point -= 1
      end

      if end_mark == s[idx, 1]
        point += 1
        break if point > 0
      end
    end

    puts "invalid format: #{s}" if point < 0
    return idx
  end

  def split_objects(s)
    split_one_object(s, 0)
  end
  
  def split_key_value(str)
    index = str.index(":")
    key = parse_string(str[0, index].strip)
    val_str = str[index + 1, str.length - 1].strip

    val = if "{" == val_str[0]
            list_str = val_str[1, (val_str.length - 2)]
            liststr_to_kv(list_str)
          else
            split_one_object(val_str, 0)
          end

    [key, val]
  end

  def liststr_to_kv(list_str)
    myself = self
    point = 0
    start_index = 0
    end_index = 0
    array = []

    list_str.each_char do |c|
      end_index += 1
      
      if "{" == c or "[" == c
        point -= 1
      end

      if "}" == c or "]" == c
        point += 1
      end

      if point > -1 and c == ","
        str = list_str[start_index, (end_index - start_index - 1)] 
        start_index = end_index
        array << str.strip
      end

      if end_index == (list_str.length - 1)
        str = list_str[start_index, (end_index - start_index + 1)] 
        start_index = end_index + 1
        array << str.strip
      end
    end

    hash = {}

    array.each do |str|
      key_val_array = myself.split_key_value(str)
      key = key_val_array[0]
      val = key_val_array[1]
      hash[key] = val
    end

    hash
  end

  def parse_object(obj)
    myself = self
    list_str = obj[1, (obj.length - 2)]
    liststr_to_kv(list_str)
  end

  def parse_array(obj)
    myself = self
    str = obj[1, obj.length - 2]
    array = str.split(",")
    array2 = []

    i = 0
    while i < array.length
      e = array[i]
      array2 << myself.split_one_object(e.strip, 0)
      i += 1
    end
    
    return array2
  end

  def parse_number(obj)
    n = 0

    if obj.include?(".")
      n = obj.to_f
    else
      n = obj.to_i
    end

    n
  end

  def parse_string(obj)
    obj[1, (obj.length - 2)]
  end

  def is_number?(str)
    is_number = true
    idx = 0

    while idx < str.length
      s = str[idx, 1]

      letter_idx = 0
      char_check_result = false
      while letter_idx < NUMBER_LETTERS.length
        nl = NUMBER_LETTERS[letter_idx, 1]
        letter_idx += 1
        if s == nl
          char_check_result = true
        end
      end

      if char_check_result == false
        is_number = false
      end

      idx += 1
    end

    is_number
  end

  def split_one_object(s, idx)
    myself = self
    idx = skip_white_spaces(s, idx)
    start_chr = s[idx, 1]
    object_start = idx

    object_end   = if    start_chr == "{"
                     search_object_end("{", "}", s, idx)
                   elsif start_chr == "["
                     search_object_end("[", "]", s, idx)
                   elsif start_chr == "\""
                     search_object_end("\"", "\"", s, idx)
                   else
                     search_object_end(nil, ",", s, idx)
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
             myself.parse_number(obj)
           end
  end

end

class JSON < JSONParser
end
