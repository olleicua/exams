counts = {}
256.times { |n| counts[n.chr] = 0 }
f = (open ARGV[0]).read
f.each_char { |char| counts[char] += 1 }
p counts.values \
  .map { |n| n.to_f / f.size } \
  .map { |n| n.zero? ? 0 : - (n * ((Math.log n) / (Math.log 256))) } \
  .reduce { |a, b| a + b }