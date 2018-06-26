require "./monte_carlo_pi/*"

# to run: crystal run src/monte_carlo_pi.cr -- 1000000
# to build: crystal build src/monte_carlo_pi.cr --release

def inUnitCircle(x, y)
  if x*x + y*y < 1.0
    return true
  else
    return false
  end
end

def monteCarloPi(reps)
  count = 0
  r = Random.new

  reps.times do
    if inUnitCircle(r.rand, r.rand)
      count += 1
    end
  end

  return count
end

reps = ARGV[0].to_u64
count = monteCarloPi(reps)
pi = count / reps.to_f64 * 4.0

puts "pi: #{pi}"