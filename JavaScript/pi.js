function inUnitCircle (x, y) {
  if (x * x + y * y < 1.0) {
    return true
  } else {
    return false
  }
}

function monteCarloPi (reps) {
  var count = 0

  for (var i = 0; i < reps; i++) {
    if (inUnitCircle(Math.random(), Math.random())) {
      count++
    }
  }

  return count
}

let reps = process.argv[2]
let count = monteCarloPi(reps)
let pi = count / reps * 4

console.log('pi: ' + pi)
