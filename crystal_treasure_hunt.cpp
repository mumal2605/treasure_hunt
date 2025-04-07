#include <iostream>
#include <vector>
using namespace std;

class Adventurer {
public:
    int x, y, energy, score;

    Adventurer(int startX, int startY, int initialEnergy) {
        x = startX;
        y = startY;
        energy = initialEnergy;
        score = 0;
    }

    void move(char direction, int M, int N) {
        if (energy <= 0) {
            cout << "No energy left." << endl;
            return;
        }

        int newX = x, newY = y;
        if (direction == 'U') newY--;
        else if (direction == 'D') newY++;
        else if (direction == 'L') newX--;
        else if (direction == 'R') newX++;

        if (newX >= 0 && newX < N && newY >= 0 && newY < M) {
            x = newX;
            y = newY;
        }
        energy--;
    }
};

class Game {
    int M, N;
    vector<vector<int>> treasureGrid;
    vector<vector<int>> trapGrid;
    Adventurer adventurer;

public:
    Game(int m, int n, int startX, int startY, int initialEnergy)
        : M(m), N(n), adventurer(startX, startY, initialEnergy) {
        treasureGrid = vector<vector<int>>(M, vector<int>(N, -1));
        trapGrid = vector<vector<int>>(M, vector<int>(N, -1));
    }

    void addTreasure(int x, int y, int value) {
        treasureGrid[y][x] = value;
    }

    void addTrap(int x, int y, int penalty) {
        trapGrid[y][x] = penalty;
    }

    void processMoves(const string& moves) {
        for (char move : moves) {
            if (move == 'X') break;
            if (adventurer.energy <= 0) break;

            adventurer.move(move, M, N);

            int curr_X = adventurer.x;
            int curr_Y = adventurer.y;

            if (treasureGrid[curr_Y][curr_X] != -1) {
                adventurer.score += treasureGrid[curr_Y][curr_X];
                treasureGrid[curr_Y][curr_X] = -1;
            }

            if (trapGrid[curr_Y][curr_X] != -1) {
                adventurer.energy -= trapGrid[curr_Y][curr_X];
                if (adventurer.energy <= 0) break;
            }
        }

        cout << "Final Score: " << adventurer.score << endl;
        cout << "Final Energy: " << adventurer.energy << endl;
        cout << "Final Position: (" << adventurer.x << ", " << adventurer.y << ")" << endl;
    }
};
