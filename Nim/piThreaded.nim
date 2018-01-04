# nim c --threads:on -d:release piThreaded.nim
import random, os, strutils, threadpool

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

let reps = parseInt(paramStr(1))
let cores = 16

var counts = newSeq[FlowVar[int64]](cores)
for i in 0..<counts.len():
    counts[i] = spawn monteCarloPi(int64(reps/cores))

var count: int64 = 0
for i in 0..<counts.len():
    count += ^counts[i]

let pi = count.toBiggestFloat() / reps.toBiggestFloat() * 4.0
echo "pi: ", pi