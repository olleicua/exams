class Array
  attr_accessor :sum
  def sum
    @sum = (reduce { |a, b| a + b } or 0) if @sum.nil?
    @sum
  end
  def << other
    @sum = (reduce { |a, b| a + b } or 0) if @sum.nil?
    other.sum = other.reduce { |a, b| a + b } if other.sum.nil? 
    num = other.pop
    push num
    @sum += num
    other.sum -= num
  end
end

class Partitioning
  def search
    if (@left.sum - @right.sum).abs > @numbers.sum
      return nil
    end
    if @numbers.empty?
      return [@left, @right]
    end
    @left << @numbers
    res = search
    return res if res
    @right << @left
    res = search
    return res if res
    @numbers << @right
    return nil
  end
  def partition numbers
    @numbers = numbers.sort
    @left = []
    @left << @numbers
    @right = []
    return search
  end
end

def check list, left, right
  list.sort == (left + right).sort and
    left.reduce { |a, b| a + b } == right.reduce { |a, b| a + b }
end

1.times do
  list = 100.times.map { rand 100 }
  res = Partitioning.new.partition list
  if res
    puts "BUG!" unless check list, *res
    puts "#{list.join ','} can be partitioned as #{res[0].join ','} | #{res[1].join ','}"
  else
    puts "#{list.join ','} can not be partitioned"
  end
end