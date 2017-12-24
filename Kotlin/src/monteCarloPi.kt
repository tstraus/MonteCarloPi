import java.util.Random

/**
 * Created by tuckerstrausbaugh on 11/8/16.
 */

fun main(args: Array<String>) {
    val start = System.currentTimeMillis()
    val pi: Double = (piLoop(args[0].toInt()).toDouble() / args[0].toDouble()) * 4.0
    val end = System.currentTimeMillis()

    println("pi: $pi")
    println("time: " + (end - start) / 1000.0 + "s")
}

fun piLoop(reps: Int): Int {
    var count = 0

    for (i in 1..reps)
        if (monteCarloPi(Random().nextDouble(), Random().nextDouble()))
            count++

    return count
}

fun monteCarloPi(x: Double, y: Double): Boolean {
    return if (x*x + y*y < 1.0) true else false
}