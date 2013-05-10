=begin
Sam Auciello | 2013 | languages Exam
A script to recursively search for solutions to a crossword of three digit
squares of the form:

#   # # #   # # #   #
# # #   # # #   # # #
#   # # #   # # #   #
=end

# A solution object holds a sequence of squares that can be used to fill in the
# puzzle
class Solution
  attr_reader :squares
  
  def initialize
    @squares = []
  end
  
  # if 13 squares have successfully been enterred then the puzzle is solved
  def solved?
    return @squares.size == 13
  end
  
  def pop
    @squares.pop
  end
  
  # this is a pretty ad hoc check and it could be improved on in many ways.
  def << square
    case @squares.size
    when 0
      @squares << square
      return true
    when 1
      if square[0] == @squares[0][1]
        @squares << square
        return true
      end
    when 2
      if square[1] == @squares[1][2]
        @squares << square
        return true
      end
    when 3
      if square[0] == @squares[2][0]
        @squares << square
        return true
      end
    when 4
      if square[0] == @squares[2][2]
        @squares << square
        return true
      end
    when 5
      if square[0] == @squares[3][2] and square[2] == @squares[4][2]
        @squares << square
        return true
      end
    when 6
      if square[0] == @squares[5][1]
        @squares << square
        return true
      end
    when 7
      if square[1] == @squares[6][2]
        @squares << square
        return true
      end
    when 8
      if square[0] == @squares[7][0]
        @squares << square
        return true
      end
    when 9
      if square[0] == @squares[7][2]
        @squares << square
        return true
      end
    when 10
      if square[0] == @squares[8][2] and square[2] == @squares[9][2]
        @squares << square
        return true
      end
    when 11
      if square[0] == @squares[10][1]
        @squares << square
        return true
      end
    when 12
      if square[1] == @squares[11][2]
        @squares << square
        return true
      end
    end
    return false
  end
end

# A search object encapsulates the entire search process
class Search

  def initialize
    @unused_squares = (10..31).map{ |x| (x * x).to_s } # all 3 digit squares
    @solution = Solution.new
  end
  
  # do the search
  def run
    return @solution.squares if @solution.solved?
    @unused_squares.each do |square|
      if @solution << square 
        @unused_squares.delete square
        res = run
        return res if res.kind_of? Array
        @solution.pop
        @unused_squares << square
        @unused_squares.sort!
      end
    end
    return "No solution exists"
  end
end

puts Search.new.run

