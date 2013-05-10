# Sam Auciello | 2013 | Algorithms Exam
# This file solves the partition problem using a recursive backtracking search

# monkey patch arrays to keep track of their sums
class Array
  attr_accessor :sum
  def sum
    @sum = (reduce { |a, b| a + b } or 0) if @sum.nil?
    @sum
  end
  # I'm overloading the << operator to take two arrays and move the last number
  # from the second array to the end of the first array then update both sums
  def << other
    @sum = (reduce { |a, b| a + b } or 0) if @sum.nil?
    other.sum = other.reduce { |a, b| a + b } if other.sum.nil? 
    num = other.pop
    push num
    @sum += num
    other.sum -= num
  end
end

# a scoping wrapper for an individual partitioning attempt
class Partitioning
  attr_reader :steps
  # initialize some structures for the search and the run the search
  def partition numbers
    @steps = 0
    @numbers = numbers.sort
    @left = []
    @left << @numbers
    @right = []
    return search
  end
  # the main backtracking search function
  def search
    @steps += 1
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
end

# verify that a partitioning is valid
def check list, left, right
  list.sort == (left + right).sort and
    left.reduce { |a, b| a + b } == right.reduce { |a, b| a + b }
end

[5, 10, 20, 25].each do |size|
  puts "size: #{size}"
  puts "2^n: #{2**size}"
  5.times do
    list = size.times.map { rand 1000 }
    partitioning = Partitioning.new
    res = partitioning.partition list
    if res
      puts "BUG!" unless check list, *res
      puts "[ #{list.join ', '} ] can be partitioned as " +
        "[ #{res[0].join ', '} ] [ #{res[1].join ', '} ]"
    else
      puts "[ #{list.join ', '} ] can not be partitioned"
    end
    puts "steps: #{partitioning.steps}"
  end
  puts " ---"
end