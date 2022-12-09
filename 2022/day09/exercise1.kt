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
    var head = Pair(0, 0)
    var tail = Pair(0, 0)
    val visited_pos = mutableSetOf<Pair<Int, Int>>(tail)

    File("input.txt").forEachLine {
        val tokens = it.split(" ")
        val direction = Direction.byLetter(tokens[0])
        val moves = Integer.parseInt(tokens[1])
        for (i in 1..moves) {
            head = move(direction, head)

            if (!touching(head, tail)) {
                val tail_dirs = tail_directions(head, tail)
                for (dir in tail_dirs) {
                    tail = move(dir, tail)
                }
            }

            visited_pos.add(tail)
        }
    }

    println("Num elems: " + visited_pos.count())
}
