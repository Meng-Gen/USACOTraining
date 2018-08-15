/*
ID: plover1
TASK: castle
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>

#define UNVISITED (-1)

using namespace std;

typedef vector< vector<int> > Maze;

Maze CreateMaze(int N, int M) {
    Maze maze(N);
    for (int i = 0; i < N; i++) {
        maze[i] = vector<int>(M, UNVISITED);
    }
    return maze;
}

void CleanMaze(Maze& maze, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            maze[i][j] = UNVISITED;
        }
    }
}

void DepthFirstSearch(Maze& maze, Maze& visited, int i, int j, int color) {
    if (visited[i][j] == UNVISITED) {
        visited[i][j] = color;
        if ((maze[i][j] & (1 << 0)) == 0) { // West
            DepthFirstSearch(maze, visited, i, j - 1, color);
        }
        if ((maze[i][j] & (1 << 1)) == 0) { // North
            DepthFirstSearch(maze, visited, i - 1, j, color);
        }
        if ((maze[i][j] & (1 << 2)) == 0) { // East
            DepthFirstSearch(maze, visited, i, j + 1, color);
        }
        if ((maze[i][j] & (1 << 3)) == 0) { // South
            DepthFirstSearch(maze, visited, i + 1, j, color);
        }
    }
}

int VisitCastle(Maze& maze, Maze& visited, int N, int M) {
    CleanMaze(visited, N, M);
    int room_count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (visited[i][j] == UNVISITED) {
                DepthFirstSearch(maze, visited, i, j, room_count++);
            }
        }
    }
    return room_count;
}

int VisitCastleWithoutNorthWall(Maze& maze, Maze& visited, int i, int j, int N, int M) {
    maze[i][j] ^= (1 << 1);
    maze[i - 1][j] ^= (1 << 3);
    int room_count = VisitCastle(maze, visited, N, M);
    maze[i - 1][j] ^= (1 << 3);
    maze[i][j] ^= (1 << 1);
    return room_count;
}

int VisitCastleWithoutEastWall(Maze& maze, Maze& visited, int i, int j, int N, int M) {
    maze[i][j] ^= (1 << 2);
    maze[i][j + 1] ^= (1 << 0);
    int room_count = VisitCastle(maze, visited, N, M);
    maze[i][j + 1] ^= (1 << 0);
    maze[i][j] ^= (1 << 2);
    return room_count;
}

int GetLargestRoom(Maze& visited, int N, int M, int room_count) {
    vector<int> room_sizes(room_count);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            room_sizes[visited[i][j]]++;
        }
    }
    int largest = 0;
    for (int i = 0; i < room_count; i++) {
        largest = max(largest, room_sizes[i]);
    }
    return largest;
}

int main() {
    ofstream fout("castle.out");
    ifstream fin("castle.in");

    int M, N;
    fin >> M >> N;
    Maze maze = CreateMaze(N, M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fin >> maze[i][j];
        }
    }

    Maze visited = CreateMaze(N, M);
    int room_count = VisitCastle(maze, visited, N, M);
    fout << room_count << '\n';
    fout << GetLargestRoom(visited, N, M, room_count) << '\n';
    int best_largest_room = 0;
    int best_module_x = 0;
    int best_module_y = 0;
    char best_module_wall = 0;
    for (int j = 0; j < M; j++) { // Choosing the module farthest to the west
        for (int i = N - 1; i >= 0; i--) { // Choosing the module farthest to the south
            if (i > 0 && (maze[i][j] & (1 << 1)) != 0) { // North first
                int room_count = VisitCastleWithoutNorthWall(maze, visited, i, j, N, M);
                int largest_room = GetLargestRoom(visited, N, M, room_count);
                if (largest_room > best_largest_room) {
                    best_largest_room = largest_room;
                    best_module_x = i + 1;
                    best_module_y = j + 1;
                    best_module_wall = 'N';
                }
            }
            if (j < M - 1 && (maze[i][j] & (1 << 2)) != 0) { // East
                int room_count = VisitCastleWithoutEastWall(maze, visited, i, j, N, M);
                int largest_room = GetLargestRoom(visited, N, M, room_count);
                if (largest_room > best_largest_room) {
                    best_largest_room = largest_room;
                    best_module_x = i + 1;
                    best_module_y = j + 1;
                    best_module_wall = 'E';
                }
            }
        }
    }
    fout << best_largest_room << '\n';
    fout << best_module_x << ' ' << best_module_y << ' ' << best_module_wall << '\n';

    return 0;
}