#include <iostream>
#include <random>
#include <thread>

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

    int getSwitchWins() const { return timesSuccessSwitch; }
    int getNoSwitchWins() const { return timesSuccessNoSwitch; }


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
    /*
    According to Wikipedia,
    "Suppose you're on a game show, and you're given the choice of three doors:
    Behind one door is a car; behind the others, goats. You pick a door, say No.1,
    and the host, who knows what's behind the doors, opens another door, say
    No.3, which has a goat. He then says to you, "Do you want to pick door No.2?"
    Is it to your advantage to switch your choice?"

    Short answer: yes. This can be simulated to show that the probability of
    selecting the door with the car goes from 1/3 to 2/3 if you switch the door
    you originally chose.
    */

    // Adjust to simulate more runs
    const int totalRuns = 3'000'000;
    const int runsPerThread = totalRuns / 3;

    // Create 3 simulators and 3 threads
    RunMonteHallSimulation sim1, sim2, sim3;
    thread t1(&RunMonteHallSimulation::runSimulation, &sim1, runsPerThread / 3);
    thread t2(&RunMonteHallSimulation::runSimulation, &sim2, runsPerThread / 3);
    thread t3(&RunMonteHallSimulation::runSimulation, &sim3, runsPerThread / 3);

    // Wait for all threads to complete
    t1.join();
    t2.join();
    t3.join();

    // Aggregate results from threads
    int totalSwitchWins = sim1.getSwitchWins() + sim2.getSwitchWins() + sim3.getSwitchWins();
    int totalNoSwitchWins = sim1.getNoSwitchWins() + sim2.getNoSwitchWins() + sim3.getNoSwitchWins();

    cout << "Switch wins:     " << totalSwitchWins << endl;
    cout << "No switch wins:  " << totalNoSwitchWins << endl;

    double total = totalSwitchWins + totalNoSwitchWins;
    cout << "Switch %:        " << 100.0 * totalSwitchWins / total << "%" << endl;
    cout << "No switch %:     " << 100.0 * totalNoSwitchWins / total << "%" << endl;

    return 0;
}