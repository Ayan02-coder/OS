#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int pid;        // Process ID
    int burstTime;  // Burst time

    // Constructor
    Process(int id, int burst) : pid(id), burstTime(burst) {}
};

bool compareByBurstTime(const Process& a, const Process& b) {
    return a.burstTime < b.burstTime;
}

void calculateWaitingTime(const std::vector<Process>& processes, std::vector<int>& waitingTimes) {
    int n = processes.size();
    waitingTimes.resize(n);

    waitingTimes[0] = 0;

    for (int i = 1; i < n; i++) {
        waitingTimes[i] = processes[i - 1].burstTime + waitingTimes[i - 1];
    }
}

void calculateTurnaroundTime(const std::vector<Process>& processes, const std::vector<int>& waitingTimes, std::vector<int>& turnaroundTimes) {
    int n = processes.size();
    turnaroundTimes.resize(n);

    for (int i = 0; i < n; i++) {
        turnaroundTimes[i] = processes[i].burstTime + waitingTimes[i];
    }
}

void calculateAverageTimes(const std::vector<Process>& processes) {
    int n = processes.size();
    std::vector<int> waitingTimes, turnaroundTimes;

    calculateWaitingTime(processes, waitingTimes);
    calculateTurnaroundTime(processes, waitingTimes, turnaroundTimes);

    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    std::cout << "Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n";

    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTimes[i];
        totalTurnaroundTime += turnaroundTimes[i];

        std::cout << processes[i].pid << "\t\t" << processes[i].burstTime << "\t\t" << waitingTimes[i] << "\t\t" << turnaroundTimes[i] << "\n";
    }

    double averageWaitingTime = static_cast<double>(totalWaitingTime) / n;
    double averageTurnaroundTime = static_cast<double>(totalTurnaroundTime) / n;

    std::cout << "\nAverage Waiting Time: " << averageWaitingTime << "\n";
    std::cout << "Average Turnaround Time: " << averageTurnaroundTime << "\n";
}

int main() {
    int n; // Number of processes
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    std::vector<Process> processes;
    processes.reserve(n);

    for (int i = 1; i <= n; i++) {
        int burstTime;
        std::cout << "Enter the burst time for Process " << i << ": ";
        std::cin >> burstTime;

        processes.emplace_back(i, burstTime);
    }

    std::sort(processes.begin(), processes.end(), compareByBurstTime);

    calculateAverageTimes(processes);

    return 0;
}
