#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int getPriority(char item) {
    if (item >= 'a' && item <= 'z') {
        return item - 'a' + 1;
    } else if (item >= 'A' && item <= 'Z') {
        return item - 'A' + 27;
    }
    return 0;
}

void computeRucksack(bool (&minors)[26], bool (&majors)[26], string &line, int len) {
    for (int i = 0; i < len; i++) {
        char item = line[i];
        if (item >= 'a' && item <= 'z') {
            minors[item - 'a'] = true;    
        } else if (item >= 'A' && item <= 'Z') {
            majors[item - 'A'] = true;
        }
    }
}

char getMatchingItem(bool (&minors1)[26], bool (&minors2)[26], bool (&minors3)[26], bool (&majors1)[26], bool (&majors2)[26], bool (&majors3)[26]) {
    for (int i = 0; i < 26; i++) {
        if (minors1[i] && minors2[i] && minors3[i]) {
            return 'a' + i;
        } else if (majors1[i] && majors2[i] && majors3[i]) {
            return 'A' + i;
        }
    }

    return 'a';
}

int main()
{
    std::ifstream infile("input.txt");
    std::string line;
    int accPriority = 0;

    bool firstRucksackMinors[26] = {0};
    bool firstRucksackMajors[26] = {0};
    bool secondRucksackMinors[26] = {0};
    bool secondRucksackMajors[26] = {0};
    bool thirdRucksackMinors[26] = {0};
    bool thirdRucksackMajors[26] = {0};

    int i = 0;

    while (std::getline(infile, line))
    {
        if (i == 0) {
            computeRucksack(firstRucksackMinors, firstRucksackMajors, line, line.length());
            i++;
        } else if (i == 1) {
            computeRucksack(secondRucksackMinors, secondRucksackMajors, line, line.length());
            i++;
        } else if (i == 2) {
            computeRucksack(thirdRucksackMinors, thirdRucksackMajors, line, line.length());
            i = 0;
        }
        
        if (i == 0) {
            char matchingItem = getMatchingItem(firstRucksackMinors, secondRucksackMinors, thirdRucksackMinors, firstRucksackMajors, secondRucksackMajors, thirdRucksackMajors);
            int priority = getPriority(matchingItem);

            accPriority += priority;

            memset(firstRucksackMinors, 0x00, 26);
            memset(secondRucksackMinors, 0x00, 26);
            memset(thirdRucksackMinors, 0x00, 26);
            memset(firstRucksackMajors, 0x00, 26);
            memset(secondRucksackMajors, 0x00, 26);
            memset(thirdRucksackMajors, 0x00, 26);
        }
    }

    cout << "total prio: " << accPriority << "\n";

	return 0;
}

