#include <iostream>
#include <random>
#include <cmath>

using namespace std;

/*
1) Generate a script (any language you wish) that simulates at least 1,000,000 couples,
each of whom has two children. Use a random number generator to simulate the sex of
the child as well as the day of the week the child was born.
a. Use your script to approximate the probability that a couple has two girls, given
that they have at least one girl born on a Monday. Verify it matches what we
computed in class.
b. Modify your script so that it also simulates the month that a child is born (you
may assume each of the 12 months is equally likely if you wish). Then use this
script to approximate the probability that a couple has two girls, given that they
have at least one girl born in January.
c. Compute the answer to part b above exactly, citing which probability rules you
are using at each step.
d. Include a printout of your code for part b with this assignment.
 */

// Improvements: Maybe use std::thread to make quicker.
// Could use std::chrono library or boost library to test precise timing for fun :P

// CONSTANTS
constexpr int MONDAY = 2;
constexpr int BOY = 10;
constexpr int GIRL = 11;
constexpr int JANUARY = 1;
constexpr int DECEMBER = 12;

// RANDOM NUMBER GENERATOR
std::random_device rd; // Non-deterministic random number generator
std::mt19937 gen(rd()); // Seed

int decideWeekday() {
    std::uniform_int_distribution<> dist_weekday(1, 7); // 1 being Sunday, 7 being Saturday
    return dist_weekday(gen);
}

int decideGender() {
    std::uniform_int_distribution<> dist_gender(BOY, GIRL); // 1 being Sunday, 7 being Saturday
    return dist_gender(gen);
}

int decideMonth() {
    std::uniform_int_distribution<> dist_month(JANUARY, DECEMBER); // 1 being January, 12 being December
    return dist_month(gen);
}

struct Child {
    Child() : gender(decideGender()), weekday(decideWeekday()), month(decideMonth()) {}

    int gender;
    int weekday;
    int month;
};

class Parent {

public:
    // CONSTRUCTORS
    Parent();

    // ACCESSORS
    bool hasTwoGirls() const {
        return child_one.gender == GIRL && child_two.gender == GIRL;
    }
    bool hasGirlOnMonday() const {
        return (child_one.weekday == MONDAY && child_one.gender == GIRL ||
                child_two.weekday == MONDAY && child_two.gender == GIRL);
    }
    bool noChildrenOnMonday() const {
        return child_one.gender != GIRL && child_two.gender != GIRL;
    }
    bool hasGirlInJanuary() const {
        return (child_one.month == JANUARY && child_one.gender == GIRL ||
                child_two.month == JANUARY && child_two.gender == GIRL);
    }
    bool noChildrenInJanuary() const {
        return child_one.month != JANUARY && child_two.month != JANUARY;
    }

    int getChildGender(int child_number) const {
        if(child_number == 1)      {  return child_one.gender;  }
        else if(child_number == 2) {  return child_two.gender;  }
        else {
            cout << "Incorrect child number!" << endl;
            return -1;
        }
    }
    int getChildWeekday(int child_number) const {
        if(child_number == 1)      {  return child_one.weekday;  }
        else if(child_number == 2) {  return child_two.weekday;  }
        else {
            cout << "Incorrect child number!" << endl;
            return -1;
        }
    }
    int getChildMonth(int child_number) const {
        if(child_number == 1)      {  return child_one.month;  }
        else if(child_number == 2) {  return child_two.month;  }
        else {
            cout << "Incorrect child number!" << endl;
            return -1;
        }
    }

private:
    Child child_one; // Uses default constructor to decide gender, weekday, and month randomly
    Child child_two;
};

Parent::Parent() : child_one(), child_two() {}

double runPartOne() {
    int parentHasGirlOnMonday = 0;
    int parentHasTwoGirlsOnMonday = 0;
    int parentHasTwoGirls = 0;

    for(int i = 0; i < 1000000; i++) { // O(n) is the most efficient for 1,000,000
        Parent parent; // Space complexity is efficient

        if(parent.hasGirlOnMonday()) {
            parentHasGirlOnMonday++;

            if(parent.hasTwoGirls()) {
                parentHasTwoGirlsOnMonday++;
            }
        }
        if(parent.hasTwoGirls()) {
            parentHasTwoGirls++;
        }
    }

//    cout << "Parents that have a girl born on Monday: " << parentHasGirlOnMonday << endl;
//    cout << "Parents that have two girls: " << parentHasTwoGirls << endl;
//    cout << "Parents that have two girls with at least one on a Monday: " << parentHasTwoGirlsOnMonday << endl;

    double probability = ((1.0 - pow(6.0 / 7.0, 2)) * parentHasTwoGirls) / parentHasGirlOnMonday;

    cout << "Probability of parents that have two girls given they have a girl born on Monday: "
         << probability << endl;

    return probability;
}

double runPartTwo() {
    /* Modify your script so that it also simulates the month that a child is born (you
    may assume each of the 12 months is equally likely if you wish). Then use this
    script to approximate the probability that a couple has two girls, given that they
    have at least one girl born in January. */

    int parentHasGirlInJan = 0;
    int parentHasTwoGirlsInJan = 0;
    int parentHasTwoGirls = 0;

    for(int i = 0; i < 1000000; i++) {
        Parent parent;

        if(parent.hasGirlInJanuary()) {
            parentHasGirlInJan++;

            if(parent.hasTwoGirls()) {
                parentHasTwoGirlsInJan++;
            }
        }
        if(parent.hasTwoGirls()) {
            parentHasTwoGirls++;
        }
    }

    double probability = static_cast<double>(parentHasTwoGirlsInJan) / parentHasGirlInJan;

//    cout << "Parents that have a girl born in January: " << parentHasGirlInJan << endl;
//    cout << "Parents that have two girls: " << parentHasTwoGirls << endl;
//    cout << "Parents that have two girls born born in January: " << parentHasTwoGirlsInJan << endl;

    cout << "Probability of parents that have two girls given they have one girl born in January: "
         << probability << endl;

    return probability;
}

void countNums(string &str) {
    /*
     * Helper functions for another question to count occurrences of 1, 2, 3, or 4
     */
    int four_count = 0;
    int three_count = 0;
    int two_count = 0;
    int one_count = 0;
    int zero_count = 0;

    for(int i = 0; i < str.size(); i++) {
        switch(str[i]) {
            case '0':
                zero_count++;
                break;
            case '1':
                one_count++;
                break;
            case '2':
                two_count++;
                break;
            case '3':
                three_count++;
                break;
            case '4':
                four_count++;
                break;
            default:
                continue;
        }
    }

    cout << "Four Count: " << four_count << endl;
    cout << "Three Count: " << three_count << endl;
    cout << "Two Count: " << two_count << endl;
    cout << "One Count: " << one_count << endl;
    cout << "Zero Count: " << zero_count << endl;
}

//int main() {
//
//    string str = "2121001011020230110312020201011210112110";
//
//    countNums(str);
//
//    return 0;
//}