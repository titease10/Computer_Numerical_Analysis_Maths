
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <cstring>
#include <sstream>
#include <climits>
#include <set>
#include <unordered_set>
#include <algorithm>

std::map<std::string, std::vector<std::string>> friendshipGraph;
std::map<std::string, std::vector<std::string>> conspiracyGraph;
std::set<std::string> allPeople;

void printHelp(void) {
    std::cout << "USAGE\n\t./game_of_graphs [--links fr p1 p2 | --plots fr cr n]\n\nDESCRIPTION\n\tfr\tfile containing friendship relations between people\n\tpi\tname of someone in the friendships file\n\tcr\tfile containing conspiracies intentions\n\tn\tmaximum length of friendship paths" << std::endl;
}

int checkArgs(int argc, char* argv[]) {
    if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        printHelp();
        return 0;
    }

    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << "--links fr p1 p2 | --plots fr cr n" << std::endl;
        return 1;
    }

    if (std::string(argv[1]) != "--links" && std::string(argv[1]) != "--plots") {
        std::cerr << "Usage: " << argv[0] << "--links fr p1 p2 | --plots fr cr n" << std::endl;
        return 1;
    }
    if (std::string(argv[1]) == "--plots")
        if (std::stoi(argv[4]) < 0) {
            std::cerr << "Usage: --plots fr cr n whit n >= 0" << std::endl;
            return 1;
        }

    return 0;
}

int calculateDegreeOfSeparation(const std::string& source, const std::string& target) {
    std::queue<std::pair<std::string, int>> bfsQueue;
    std::map<std::string, bool> visited;

    bfsQueue.push({source, 0});
    visited[source] = true;

    while (!bfsQueue.empty()) {
        auto current = bfsQueue.front();
        bfsQueue.pop();
        if (current.first == target) {
            return current.second;
        }
        for (const auto& friendName : friendshipGraph[current.first]) {
            if (!visited[friendName]) {
                bfsQueue.push({friendName, current.second + 1});
                visited[friendName] = true;
            }
        }
    }
    return -1;
}

int inputFriendGraph(std::string pathFile)
{
    std::ifstream file(pathFile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the friends report file." << std::endl;
        return 84;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string friend1, friend2;
        size_t firstSeparatorPos = line.find(" is ");
        size_t secondSeparatorPos = line.find(" with ");
        if (firstSeparatorPos != std::string::npos && secondSeparatorPos != std::string::npos) {
            friend1 = line.substr(0, firstSeparatorPos);
            friend2 = line.substr(secondSeparatorPos + 6);
        }
        if (friend1.empty() || friend2.empty()) {
            std::cerr << "Error: Empty person names in the friendships report file." << std::endl;
            return 84;
        }

        friendshipGraph[friend1].push_back(friend2);
        friendshipGraph[friend2].push_back(friend1);
    }
    file.close();
    return 0;
}

int linksParts(char* argv[])
{
    if (strcmp(argv[1], "--links") != 0)
        return 1;

    const std::string friendsReportFile = argv[2];
    std::string person1 = argv[3];
    std::string person2 = argv[4];

    if (!person1.empty() && person1.front() == '"' && person1.back() == '"') {
        person1 = person1.substr(1, person1.length() - 2);
    }
    if (!person2.empty() && person2.front() == '"' && person2.back() == '"') {
        person2 = person2.substr(1, person2.length() - 2);
    }

    if (inputFriendGraph(friendsReportFile) == 84)
        return 84;

    if (friendshipGraph.find(person1) == friendshipGraph.end() || friendshipGraph.find(person2) == friendshipGraph.end()) {
        std::cout << "Degree of separation between" << person1 << " and " << person2 << ": -1" << std::endl;
        return 0;
    }
    int degree = calculateDegreeOfSeparation(person1, person2);
    std::cout << "Degree of separation between " << person1 << " and " << person2 << ": " << degree << std::endl;
    return 0;
}

int inputconspiracyGraph(std::string pathFile)
{
    std::ifstream file(pathFile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the friends report file." << std::endl;
        return 84;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string friend1, friend2;
        size_t firstSeparatorPos = line.find(" is ");
        size_t secondSeparatorPos = line.find(" against ");

        if (firstSeparatorPos != std::string::npos && secondSeparatorPos != std::string::npos) {
            friend1 = line.substr(0, firstSeparatorPos);
            friend2 = line.substr(secondSeparatorPos + std::string(" against ").length());
        }
        if (friend1.empty() || friend2.empty()) {
            std::cerr << "Error: Empty person names in the friendships report file." << std::endl;
            return 84;
        }
        if (allPeople.find(friend1) == allPeople.end() || allPeople.find(friend2) == allPeople.end()) {
            std::cerr << "one or more cr file name does not exist in the fr file." <<std::endl;
            return 84;
        }
        conspiracyGraph[friend1].push_back(friend2);
    }
    file.close();
    return 0;
}

void displayPeopleInAlphabeticalOrder()
{
    std::cout << "Names:" << std::endl;
    std::vector<std::string> names;

    for (const auto& entry : friendshipGraph)
        names.push_back(entry.first);
    std::sort(names.begin(), names.end());
    for (const std::string& name : names)
        std::cout << name << std::endl;
    std::cout << std::endl;
}

std::vector<std::vector<int>> displayAdjacencyMatrix(int n) {
    int numPeople = allPeople.size();
    std::vector<std::vector<int>> shortestPathsMatrix(numPeople, std::vector<int>(numPeople, INT_MAX));
    int personIdx = 0;
    std::map<std::string, int> personToIndex;
    for (const std::string& person : allPeople) {
        personToIndex[person] = personIdx;
        shortestPathsMatrix[personIdx][personIdx] = 0;
        ++personIdx;
    }
    // Remplissage de la matrice avec les distances entre amis
    for (const auto& entry : friendshipGraph) {
        const std::string& personA = entry.first;
        int indexA = personToIndex[personA];
        for (const std::string& personB : entry.second) {
            int indexB = personToIndex[personB];
            shortestPathsMatrix[indexA][indexB] = 1;
            shortestPathsMatrix[indexB][indexA] = 1;
        }
    }
    for (int k = 0; k < numPeople; ++k) {
        for (int i = 0; i < numPeople; ++i) {
            for (int j = 0; j < numPeople; ++j) {
                if (shortestPathsMatrix[i][k] != INT_MAX && shortestPathsMatrix[k][j] != INT_MAX) {
                    shortestPathsMatrix[i][j] = std::min(shortestPathsMatrix[i][j], shortestPathsMatrix[i][k] + shortestPathsMatrix[k][j]);
                }
            }
        }
    }
    std::cout << "Relationships:" << std::endl;
    for (int i = 0; i < numPeople; ++i) {
        for (int j = 0; j < numPeople; ++j) {
            if (j != 0)
                std::cout << " ";
            if (shortestPathsMatrix[i][j] <= n) {
                std::cout << shortestPathsMatrix[i][j];
            } else {
                shortestPathsMatrix[i][j] = 0;
                std::cout << "0";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return shortestPathsMatrix;
}

std::vector<std::string> setConspirator(std::string enemy)
{
    std::vector<std::string> queenEnemies;
    for (const auto& entry : conspiracyGraph) {
        const std::string& person = entry.first;
        const std::vector<std::string>& conspirators = entry.second;
        for (const std::string& conspirator : conspirators) {
            if (conspirator == enemy) {
                queenEnemies.push_back(person);
                break;
            }
        }
    }
    return queenEnemies;
}

int takeIndex(const std::string& person)
{
    int index = 0;
    for (const std::string& name : allPeople) {
        if (name == person) {
            return index;
        }
        ++index;
    }
    return 0;
}

std::vector<std::vector<std::string>> conspiracyPaths(std::vector<std::vector<int>> adjacencyMatrix, std::vector<std::string> queenEnemies)
{
    std::vector<std::vector<std::string>> conspiracyPaths;
    int indexQueen = takeIndex("Cersei Lannister");
    for (const std::string& enemy : queenEnemies) {
        std::vector<std::string> conspiratorEnemy = setConspirator(enemy);
        std::vector<std::string> path;
        for (const std::string& conspirator : conspiratorEnemy) {
            int indexConspirator = takeIndex(conspirator);
            if (adjacencyMatrix[indexQueen][indexConspirator] > 0) {
                path.push_back(conspirator);
                path.push_back(enemy);
                conspiracyPaths.push_back(path);
                break;
            }
        }
        if (path.empty()) {
            path.push_back("No conspiracy possible against");
            path.push_back(enemy);
            conspiracyPaths.push_back(path);
        }
    }
    return conspiracyPaths;
}

bool customCompare(const std::vector<std::string>& a, const std::vector<std::string>& b) {
    if (a.empty()) return false;
    if (b.empty()) return true;

    if (a[0] == "No conspiracy possible against") return false;
    if (b[0] == "No conspiracy possible against") return true;
    if (a.size() == b.size()) {
        for (size_t i = 0; i < a.size(); ++i) {
            int cmp = a[i].compare(b[i]);
            if (cmp != 0) return cmp < 0;
        }
        return false;  // ils sont égaux
    }
    return a.size() < b.size();
}

int plotsParts(int argc, char**argv)
{
    if (strcmp(argv[1], "--plots") != 0)
        return 1;

    const std::string friendsReportFile = argv[2];
    const std::string conspiracyReportFile = argv[3];
    const int maxDegree = std::stoi(argv[4]);
    bool result = true;

    if (maxDegree <= 0) {
        std::cerr << "Error: Maximum degree of separation must be non-negative." << std::endl;
        return 84;
    }
    if (inputFriendGraph(friendsReportFile) == 84)
        return 84;
    for (const auto& entry : friendshipGraph) {
        allPeople.insert(entry.first);
        for (const std::string& friendName : entry.second) {
            allPeople.insert(friendName);
        }
    }
    if (inputconspiracyGraph(conspiracyReportFile) == 84)
        return 84;

    displayPeopleInAlphabeticalOrder();
    std::vector<std::vector<int>> adjacencyMatrix = displayAdjacencyMatrix(maxDegree);
    std::vector<std::string> queenEnemies = setConspirator("Cersei Lannister");
    std::vector<std::vector<std::string>> conspiracy = conspiracyPaths(adjacencyMatrix, queenEnemies);
    std::sort(conspiracy.begin(), conspiracy.end(), customCompare);
    std::cout << "Conspiracies:" << std::endl;
    for (const std::vector<std::string>& path : conspiracy) {
        for (const std::string& person : path) {
            if (person != path.front())
                std::cout << " ";
            std::cout << person;
            if (person != path.back() && person != "No conspiracy possible against")
                std::cout << " ->";
            if (person == "No conspiracy possible against")
                result = false;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Result:" << std::endl;
    if (result == false)
        std::cout << "There is only one way out: treason !" << std::endl;
    else
        std::cout << "The Crown is safe !" << std::endl;
    return 0;
}

int main(int argc, char* argv[]) {
    if (checkArgs(argc, argv) != 0)
        return 84;
    if (linksParts(argv) == 84)
        return 84;
    else if (plotsParts(argc, argv) == 84)
        return 84;
    return 0;
}
