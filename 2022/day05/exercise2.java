import java.util.ArrayList;
import java.util.Stack;
import java.util.stream.Stream;
import java.nio.file.Files;
import java.nio.file.Paths;

class Exercise2 {
    public static Stack<Character> getStack(String desc) {
        Stack<Character> stack = new Stack<Character>();
        desc.chars().forEach(c -> stack.push(Character.valueOf((char)c)));
        return stack;
    }

    public static ArrayList<Stack<Character>> initStacks() {
        ArrayList<Stack<Character>> stacks = new ArrayList<Stack<Character>>();
        stacks.add(getStack("QFMRLWCV"));
        stacks.add(getStack("DQL"));
        stacks.add(getStack("PSRGWCNB"));
        stacks.add(getStack("LCDHBQG"));
        stacks.add(getStack("VGLFZS"));
        stacks.add(getStack("DGNP"));
        stacks.add(getStack("DZPVFCW"));
        stacks.add(getStack("CPDMS"));
        stacks.add(getStack("ZNWTVMPC"));
        return stacks;
    }

    public static void main(String[] args) {
        ArrayList<Stack<Character>> stacks = initStacks();

        try (Stream<String> stream = Files.lines(Paths.get("moves.txt"))) {
            stream.forEach(move -> {
                String[] tokens = move.split(" ");
                int numMoves = Integer.parseInt(tokens[1]);
                int origin = Integer.parseInt(tokens[3]);
                int dest = Integer.parseInt(tokens[5]);

                Stack<Character> tempStack = new Stack<Character>();
                for (int i = 0; i < numMoves; i++) {
                    Character c = stacks.get(origin - 1).pop();
                    tempStack.push(c);
                }
                for (int i = 0; i < numMoves; i++) {
                    Character c = tempStack.pop();
                    stacks.get(dest - 1).push(c);
                }
            });
        } catch (Exception ex) {
            System.out.println("Unexpected error");
        }

        stacks.forEach(stack -> System.out.print(stack.pop()));
        System.out.println();
    }
}
