import MonteCarloPi
import multiprocessing
from multiprocessing import Pool
from sys import argv

def wrapper (reps: int):
    return MonteCarloPi.pi(reps)

if __name__ == '__main__':
    reps = int(argv[1])
    cores = multiprocessing.cpu_count()
    pool = Pool(cores)

    subReps = [int(reps/cores)]*cores

    results = pool.map(wrapper, subReps)
   
    pi = sum(results) / cores

    print("pi: " + str(pi))