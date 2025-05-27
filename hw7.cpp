#include <iostream>
#include <vector>
#include <random>
#include <unordered_set>
#include <utility>
#include <string>
#include <cassert>

using namespace std;

// RANDOM NUMBER GENERATOR
std::random_device rd1; // Non-deterministic random number generator
std::mt19937 gen1(rd1()); // Seed
std::uniform_int_distribution<> generator1(1, 100);// Generator

struct Precinct {
    Precinct() {
        partyA = generator1(gen1);
        partyB = generator1(gen1);
    }

    void seePrecincts() {
        cout << "Party A: " << partyA << endl;
        cout << "Party B: " << partyB << endl;
    }

    bool operator==(const Precinct& other) const { // For hash function
        return partyA == other.partyA && partyB == other.partyB;
    }

    int partyA;
    int partyB;
};

// This is AI generated. This is to hash our precincts properly because it's a
// custom-defined type, not an STD type
// Hash function for Precinct
namespace std {
    template<>
    struct hash<Precinct> {
        size_t operator()(const Precinct& p) const {
            return hash<int>()(p.partyA) ^ (hash<int>()(p.partyB) << 1);
        }
    };
}

/*
 *
 *
 // TEST CASES
QuestionFour test_case1("1010010100", "10", "100");
    test_case1.solution();
QuestionFour test_case2("10010010", "10", "00");
    test_case2.solution();
QuestionFour test_case3("00110011", "001", "01");
    test_case3.solution();
QuestionFour test_case4("1010010100", "10", "100");
    test_case4.solution();

QuestionFour test_case5("1001001001", "100", "01");
    test_case5.solution();
QuestionFour test_case6("00100110", "001", "10");
    test_case6.solution();
QuestionFour test_case7("1010010100", "10", "100");
    test_case7.solution();

// False = -1
// True = 1
QuestionFour test_case8("0101010101", "01", "10");
    // Subjective?
    assert(test_case8.solution() == 1);
QuestionFour test_case9("000000", "00", "000");
    assert(test_case9.solution() == 1);
    //TODO: This question bugs
QuestionFour test_case10("1010101010", "10", "10");
    assert(test_case10.solution() == -1);
QuestionFour test_case11("001001001001001001001001", "001", "00");
    assert(test_case11.solution() == 1);
QuestionFour test_case12("1000100011", "100", "01");
    assert(test_case12.solution() == -1);
 */

class QuestionFour {
public:
    QuestionFour(string sig, string x_pattern, string y_pattern) {
        signal = sig;
        x = x_pattern;
        y = y_pattern;

        size = signal.size();
        size_x = x.size();
        size_y = y.size();
    }

    int solution() const {
        int n = size;
        vector<vector<bool>> dp(n + 1, vector<bool>(n + 1, false));
        dp[0][0] = true; // base case: empty signal

        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                int pos = i + j;
                if (pos == 0 || pos > n) continue;

                char current_char = signal[pos - 1];

                // Try to take from x
                if (i > 0 && dp[i - 1][j]) {
                    char expected_x_char = x[(i - 1) % size_x];
                    if (current_char == expected_x_char) {
                        dp[i][j] = true;
                    }
                }

                // Try to take from y
                if (j > 0 && dp[i][j - 1]) {
                    char expected_y_char = y[(j - 1) % size_y];
                    if (current_char == expected_y_char) {
                        dp[i][j] = true;
                    }
                }
            }
        }

        // Check if any dp[i][j] where i + j == n is true
        for (int i = 0; i <= n; ++i) {
            int j = n - i;
            if (dp[i][j]) {
                cout << "Interleaving signal." << endl;
                return 1;
            }
        }

        cout << "Error! Pattern broken. Not an interweaving." << endl;
        return -1;
    }

private:
    string signal;
    string x;
    string y;
    int size;
    int size_x;
    int size_y;
};