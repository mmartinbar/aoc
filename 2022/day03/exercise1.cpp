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

void computeCompartment(bool (&minors)[26], bool (&majors)[26], string &half, int len) {
    for (int i = 0; i < len; i++) {
        char item = half[i];
        if (item >= 'a' && item <= 'z') {
            minors[item - 'a'] = true;    
        } else if (item >= 'A' && item <= 'Z') {
            majors[item - 'A'] = true;
        }
    }
}

char getMatchingItem(bool (&minors1)[26], bool (&minors2)[26], bool (&majors1)[26], bool (&majors2)[26]) {
    for (int i = 0; i < 26; i++) {
        if (minors1[i] && minors2[i]) {
            return 'a' + i;
        } else if (majors1[i] && majors2[i]) {
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

    while (std::getline(infile, line))
    {
        bool firstHalfMinors[26] = {0};
        bool firstHalfMajors[26] = {0};
        bool secondHalfMinors[26] = {0};
        bool secondHalfMajors[26] = {0};
        int halflen = line.length() / 2;
        std::string firstHalf = line.substr(0, halflen);
        std::string secondHalf = line.substr(halflen);
        
        computeCompartment(firstHalfMinors, firstHalfMajors, firstHalf, halflen);
        computeCompartment(secondHalfMinors, secondHalfMajors, secondHalf, halflen);

        char matchingItem = getMatchingItem(firstHalfMinors, secondHalfMinors, firstHalfMajors, secondHalfMajors);
        int priority = getPriority(matchingItem);

        accPriority += priority;
    }

    cout << "total prio: " << accPriority << "\n";

	return 0;
}

