import random
from sys import argv


def inUnitCircle (x: float, y: float):
    if x*x + y*y < 1.0:
        return True
    else:
        return False


def monteCarloPi (reps: int):
    count = 0

    for rep in range(reps):
        if inUnitCircle(random.uniform(0.0, 1.0), random.uniform(0.0, 1.0)):
            count += 1

    return count


reps = int(argv[1])
count = monteCarloPi(reps)
pi = count / reps * 4

print("pi: " + str(pi))
