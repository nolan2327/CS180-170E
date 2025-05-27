#include <iostream>
#include <random>

using namespace std;

class RunMonteHallSimulation {
public:
    RunMonteHallSimulation()
            : gen(rd()), dist_door(0, 2), timesSuccessSwitch(0),
              timesSuccessNoSwitch(0) {}

    void runSimulation(int runs) {
        // Simulate switching doors and not switching
        for(int i = 0; i < 3; i++) {
            int playerChoice = i;

            for (int j = 0; j < runs; ++j) {
                int car = dist_door(gen); // Random door with car
                int montyOpens;

                // Monty opens a door that:
                // - Is not the player's choice
                // - Does not hide the car
                do {
                    montyOpens = dist_door(gen);
                } while (montyOpens == playerChoice || montyOpens == car);

                // Determine remaining unopened door to switch to
                int switchChoice = 3 - playerChoice - montyOpens;

                // Stay outcome
                if (playerChoice == car) {
                    timesSuccessNoSwitch++;
                }

                // Switch outcome
                if (switchChoice == car) {
                    timesSuccessSwitch++;
                }
            }
        }
    }

    void printResults() const {
        cout << "When switching doors: " << timesSuccessSwitch << endl;
        cout << "When not switching doors: " << timesSuccessNoSwitch << endl;
    }

private:
    std::random_device rd;                 // For seeding
    std::mt19937 gen;
    std::uniform_int_distribution<> dist_door;  // Distribution using [1, 3]

    int timesSuccessSwitch;
    int timesSuccessNoSwitch;
};

int main() {
    RunMonteHallSimulation sim;

    sim.runSimulation(1000);

    sim.printResults();
}