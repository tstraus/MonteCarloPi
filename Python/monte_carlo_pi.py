import random

def InUnitCircle (x: float, y: float):
    if x*x + y*y < 1.0:
        return True
    else:
        return False

def MonteCarloPi (reps: int):
    count = 0

    for rep in range(reps):
        if InUnitCircle(random.uniform(0.0, 1.0), random.uniform(0.0, 1.0)):
            count += 1

    return count

reps = 1000000
count = MonteCarloPi(reps)
pi = count / reps * 4

print("pi: " + str(pi))
