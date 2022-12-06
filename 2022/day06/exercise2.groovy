int WINDOW_SIZE = 14;

File file = new File("input.txt")
String fileContent = file.text

// Initialization
Map windowMap = ['c':1,'b':2,'h':1,'m':4,'q':3,'n':1,'v':1,'f':1]
Set<Character> charsToBlame = ['b','m','q']

for (int i = WINDOW_SIZE; i < fileContent.length(); i++) {
    // Remove old character
    char oldChar = fileContent[i - WINDOW_SIZE];
    int newTimes = windowMap."$oldChar" - 1;
    if (newTimes == 0) {
        windowMap.remove((String)"$oldChar");
    } else {
        windowMap."$oldChar" = newTimes;
        if (newTimes == 1) {
            charsToBlame.remove((String)"$oldChar");
        }
    }

    // Put new character
    char newChar = fileContent[i];
    if (windowMap."$newChar") {
        windowMap."$newChar" = windowMap."$newChar" + 1;
        charsToBlame.add((String)"$newChar");
    } else {
        windowMap."$newChar" = 1;
    }
    
    // Check if no chars to blame 
    if (charsToBlame.isEmpty()) {
        println("Position is: " + (i + 1));
        break;
    }
}
