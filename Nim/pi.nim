# nim c -d:release pi.nim

import random, os, strutils

proc inUnitCircle(x: float64, y: float64): bool =
    if x*x + y*y < 1.0:
        result = true
    else:
        result = false

proc monteCarloPi(reps: int64): int64 =
    var count = 0
    randomize()

    for i in countup(1, reps):
        if inUnitCircle(random(1.0), random(1.0)):
            inc(count)
    
    result = count

let reps = parseBiggestInt(paramStr(1))
let count = monteCarloPi(reps)
let pi = count.toBiggestFloat() / reps.toBiggestFloat() * 4.0

echo "pi: ", pi