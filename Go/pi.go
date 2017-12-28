package main

import (
	"math/rand"
	"os"
	"runtime"
	"strconv"
	"sync"
	"time"

	"github.com/fatih/color"
)

func main() {
	cores := runtime.NumCPU()
	runtime.GOMAXPROCS(cores)

	var wait sync.WaitGroup
	counts := make([]int, cores)
	samples, _ := strconv.Atoi(os.Args[1])

	start := time.Now()
	wait.Add(cores)

	for i := 0; i < cores; i++ {
		go monteCarloPi(samples/cores, &counts[i], &wait)
	}

	wait.Wait()

	total := 0
	for i := 0; i < cores; i++ {
		total += counts[i]
	}

	pi := (float64(total) / float64(samples)) * 4

	runtime := time.Since(start)
	yellow := color.New(color.FgYellow)
	yellow.Println("Time: ", runtime)
	cyan := color.New(color.FgCyan)
	cyan.Println("pi: ", pi)
}

func monteCarloPi(reps int, result *int, wait *sync.WaitGroup) {
	var x, y float64
	count := 0
	seed := rand.NewSource(time.Now().UnixNano())
	random := rand.New(seed)

	for i := 0; i < reps; i++ {
		x = random.Float64()
		y = random.Float64()

		if x*x+y*y < 1.0 {
			count++
		}
	}

	*result = count
	wait.Done()
}
