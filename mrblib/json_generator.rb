# -*- coding: utf-8 -*-
#
#  add to_json method to mrubyc classes. 
#
#  Copyright (C) 2019 Shin Hiroe
#
#  This file is distributed under BSD 3-Clause License.
#

class String
  
  def to_json
    "\"#{self}\""
  end

end

class Fixnum

  def to_json
    self.to_s
  end

end

class Float

  def to_json
    "#{self}"
  end

end

class TrueClass
  
  def to_json
    "true"
  end

end

class FalseClass
  
  def to_json
    "false"
  end

end

class NilClass

  def to_json
    "NULL"
  end

end

class Array

  def to_json
    "[" + collect{ |e| e.to_json }.join(",") + "]"
  end

end

class Hash

  def to_json
    method_self = self # Array#each内でのselfはprocを返すので一旦変数にとっておく
    elements = []

    self.keys.each do |k|
      v = method_self[k]
      elements.push("\"#{k}\":#{v.to_json}")
    end

    "{" + elements.join(",") + "}"
  end

end
