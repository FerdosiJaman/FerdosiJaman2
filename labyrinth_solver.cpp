#include <iostream>
#include <vector>
#include <queue>
#include <stack>

struct Cell {
    int row;
    int col;
};

std::vector<std::vector<char>> labyrinth = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#'},
    {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', '#', '#', '#', '#', ' ', '#', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

std::vector<Cell> findNeighbors(Cell current) {
    std::vector<Cell> neighbors;
    neighbors.push_back({current.row - 1, current.col});
    neighbors.push_back({current.row + 1, current.col});
    neighbors.push_back({current.row, current.col - 1});
    neighbors.push_back({current.row, current.col + 1});
    return neighbors;
}

bool isValidCell(Cell cell) {
    int numRows = labyrinth.size();
    int numCols = labyrinth[0].size();
    return cell.row >= 0 && cell.row < numRows && cell.col >= 0 && cell.col < numCols &&
           labyrinth[cell.row][cell.col] == ' ';
}

std::vector<Cell> findPath(Cell start, Cell end) {
    std::vector<std::vector<bool>> visited(labyrinth.size(), std::vector<bool>(labyrinth[0].size(), false));
    std::vector<std::vector<Cell>> previous(labyrinth.size(), std::vector<Cell>(labyrinth[0].size(), {-1, -1}));

    std::queue<Cell> queue;
    queue.push(start);
    visited[start.row][start.col] = true;

    while (!queue.empty()) {
        Cell current = queue.front();
        queue.pop();

        if (current.row == end.row && current.col == end.col) {
            std::vector<Cell> path;
            Cell backtrack = end;
            while (backtrack.row != -1 && backtrack.col != -1) {
                path.push_back(backtrack);
                backtrack = previous[backtrack.row][backtrack.col];
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        std::vector<Cell> neighbors = findNeighbors(current);
        for (const auto& neighbor : neighbors) {
            if (isValidCell(neighbor) && !visited[neighbor.row][neighbor.col]) {
                queue.push(neighbor);
                visited[neighbor.row][neighbor.col] = true;
                previous[neighbor.row][neighbor.col] = current;
            }
        }
    }

    return {};  // Empty path (no solution)
}

void printLabyrinth() {
    for (const auto& row : labyrinth) {
        for (const auto& cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
}

void printPath(const std::vector<Cell>& path) {
    std::vector<std::vector<char>> labyrinthCopy = labyrinth;
    for (const auto& cell : path) {
        labyrinthCopy[cell.row][cell.col] = '.';
    }
    std::cout << "Solution path:\n";
    printLabyrinth();
}

int main() {
    Cell start = {1, 1};
