#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

struct Drone {
    int id;
    pair<int, int> start_pos;
    pair<int, int> end_pos;
    int start_time;
    vector<pair<int, int>> path;
};

struct CompareStartTime {
    bool operator()(const Drone& d1, const Drone& d2) {
        return d1.start_time > d2.start_time;
    }
};

int manhattan_distance(pair<int, int> p1, pair<int, int> p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

vector<pair<int, int>> find_path(pair<int, int> start, pair<int, int> end, int M, int N) {
    // Implement any standard pathfinding algorithm here like A* or Dijkstra's algorithm.
    // For simplicity, we'll just return a straight path from start to end.
    vector<pair<int, int>> path;
    int dx = end.first - start.first;
    int dy = end.second - start.second;
    int steps = max(abs(dx), abs(dy));
    int x_inc = dx / steps;
    int y_inc = dy / steps;
    int x = start.first;
    int y = start.second;
    for (int i = 0; i <= steps; i++) {
        path.push_back(make_pair(x, y));
        x += x_inc;
        y += y_inc;
    }
    return path;
}

int main() {
    int M, N, num_drones;
    cin >> M >> N >> num_drones;

    priority_queue<Drone, vector<Drone>, CompareStartTime> pq;
    for (int i = 0; i < num_drones; i++) {
        int x1, y1, x2, y2, start_time;
        cin >> x1 >> y1 >> x2 >> y2 >> start_time;
        Drone drone;
        drone.id = i;
        drone.start_pos = make_pair(x1, y1);
        drone.end_pos = make_pair(x2, y2);
        drone.start_time = start_time;
        drone.path = find_path(drone.start_pos, drone.end_pos, M, N);
        pq.push(drone);
    }

    int timer = 0;
    while (!pq.empty()) {
        Drone drone = pq.top();
        pq.pop();
        if (drone.start_time > timer) {
            // Wait until the start time of the drone is reached.
            timer = drone.start_time;
        }
        cout << "Drone " << drone.id << " path: ";
        for (pair<int, int> pos : drone.path) {
            // Move the drone along its path.
            timer++;
            cout << "(" << pos.first << "," << pos.second << ") ";
            if (pos == drone.end_pos) {
                // Drone has reached its destination.
                break;
            }
        }
        cout << endl;
        if (drone.path.back() != drone.end_pos) {
            // Drone has not reached its destination yet. Add it back to the priority queue.
            drone.start_time = timer;
            pq.push(drone);
        }
    }

    return 0;
}
