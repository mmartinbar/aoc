import java.io.File
import kotlin.math.abs

enum class Direction(val dir: String) {
    UP("U"),
    DOWN("D"),
    LEFT("L"),
    RIGHT("R");

    companion object {
        fun byLetter(dir: String): Direction? {
            return values().firstOrNull { it.dir.equals(dir, true) }
        }
    }
}

fun move(direction: Direction?, pos: Pair<Int, Int>): Pair<Int, Int> {
    when (direction) {
        Direction.UP -> return pos.copy(second = pos.second + 1)
        Direction.DOWN -> return pos.copy(second = pos.second - 1)
        Direction.LEFT -> return pos.copy(first = pos.first - 1)
        Direction.RIGHT -> return pos.copy(first = pos.first + 1)
        else -> return pos
    }
}

fun touching(head: Pair<Int, Int>, tail: Pair<Int, Int>): Boolean {
    val (hx, hy) = head
    val (tx, ty) = tail

    return (abs(hx - tx) <= 1) && (abs(hy - ty) <= 1) 
}

fun tail_directions(head: Pair<Int, Int>, tail: Pair<Int, Int>): List<Direction> {
    val (hx, hy) = head
    val (tx, ty) = tail

    val moves = mutableListOf<Direction>()

    if (hx > tx) {
        moves.add(Direction.RIGHT)
    } else if (hx < tx) {
        moves.add(Direction.LEFT)
    }

    if (hy > ty) {
        moves.add(Direction.UP)
    } else if (hy < ty) {
        moves.add(Direction.DOWN)
    }

    return moves
}

fun main() {
    var knots = mutableListOf<Pair<Int, Int>>()
    for (i in 0..9) {
        knots.add(Pair(0, 0))
    }
    val visited_pos = mutableSetOf<Pair<Int, Int>>(knots.last())

    File("input.txt").forEachLine {
        val tokens = it.split(" ")
        val direction = Direction.byLetter(tokens[0])
        val moves = Integer.parseInt(tokens[1])
        for (i in 1..moves) {
            knots[0] = move(direction, knots[0])

            for (idx in 1..9) {
                val head = knots[idx - 1]
                val tail = knots[idx]
                    
                if (!touching(head, tail)) {
                    val tail_dirs = tail_directions(head, tail)
                    for (dir in tail_dirs) {
                        knots[idx] = move(dir, knots[idx])
                    }
                }
            }

            visited_pos.add(knots.last())
        }
    }

    println("Num elems: " + visited_pos.count())
}
