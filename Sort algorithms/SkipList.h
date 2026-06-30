#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <map>
using namespace std;

template <typename T>
class SkipNode {
public:
    T key;
    SkipNode* next;
    SkipNode* below;

    explicit SkipNode(T k) : key(k), next(nullptr), below(nullptr) {}
};

template <typename T>
class SkipStructure {
protected:
    SkipNode<T>* topLevel;
    int heightLimit;
    float chance;

    int pickHeight() {
        int h = 1;
        while (h < heightLimit && (rand() / static_cast<float>(RAND_MAX)) < chance) {
            h++;
        }
        return h;
    }

    SkipNode<T>* newNode(T k) {
        return new SkipNode<T>(k);
    }

public:
    SkipStructure(int maxHeight, float probability)
        : heightLimit(maxHeight), chance(probability) {
        topLevel = new SkipNode<T>(numeric_limits<T>::min());
        SkipNode<T>* curr = topLevel;
        for (int i = 1; i < heightLimit; ++i) {
            SkipNode<T>* nextLevel = new SkipNode<T>(numeric_limits<T>::min());
            curr->below = nextLevel;
            curr = nextLevel;
        }
    }

    virtual ~SkipStructure() {
        while (topLevel) {
            SkipNode<T>* level = topLevel;
            topLevel = topLevel->below;
            while (level) {
                SkipNode<T>* next = level->next;
                delete level;
                level = next;
            }
        }
    }

    void add(T key) {
        vector<SkipNode<T>*> previousNodes(heightLimit, nullptr);
        SkipNode<T>* temp = topLevel;

        for (int i = heightLimit - 1; i >= 0; --i) {
            while (temp->next && temp->next->key < key) {
                temp = temp->next;
            }
            previousNodes[i] = temp;
            if (temp->below) temp = temp->below;
        }

        int nodeHeight = pickHeight();
        SkipNode<T>* newItem = nullptr;

        for (int i = 0; i < nodeHeight; ++i) {
            SkipNode<T>* freshNode = newNode(key);
            if (previousNodes[i]) {
                freshNode->next = previousNodes[i]->next;
                previousNodes[i]->next = freshNode;
            }
            if (newItem) freshNode->below = newItem;
            newItem = freshNode;
        }
    }

    void deleteKey(T key) {
        vector<SkipNode<T>*> prevNodes(heightLimit, nullptr);
        SkipNode<T>* cursor = topLevel;

        for (int i = heightLimit - 1; i >= 0; --i) {
            while (cursor->next && cursor->next->key < key) {
                cursor = cursor->next;
            }
            prevNodes[i] = cursor;
            if (cursor->below) cursor = cursor->below;
        }

        bool found = false;
        for (int i = 0; i < heightLimit; ++i) {
            if (prevNodes[i]->next && prevNodes[i]->next->key == key) {
                found = true;
                SkipNode<T>* target = prevNodes[i]->next;
                prevNodes[i]->next = target->next;
                delete target;
            }
        }

        if (!found) {
            cout << "Key " << key << " not found in the list.\n";
        }

        while (topLevel && !topLevel->next && topLevel->below) {
            SkipNode<T>* oldTop = topLevel;
            topLevel = topLevel->below;
            delete oldTop;
        }
    }

    bool find(T key) const {
        SkipNode<T>* searcher = topLevel;
        while (searcher) {
            while (searcher->next && searcher->next->key < key) {
                searcher = searcher->next;
            }
            if (searcher->next && searcher->next->key == key) {
                return true;
            }
            searcher = searcher->below;
        }
        return false;
    }

    void show() const {
        SkipNode<T>* level = topLevel;
        while (level) {
            SkipNode<T>* node = level;
            while (node) {
                if (node->key != numeric_limits<T>::min()) {
                    cout << node->key << " ";
                }
                node = node->next;
            }
            cout << endl;
            level = level->below;
        }
    }
};

class Player {
public:
    int playerID;
    int score;

    Player(int id = 0, int sc = 0) : playerID(id), score(sc) {}

    bool operator<(const Player& other) const {
        return playerID < other.playerID;
    }

    friend ostream& operator<<(ostream& os, const Player& player) {
        os << "Player ID: " << player.playerID << ", Score: " << player.score;
        return os;
    }
};

class GameBoard : public SkipStructure<int> {
public:
    map<int, int> playerScores;

    GameBoard(int maxLevel = 16, float probability = 0.5)
        : SkipStructure<int>(maxLevel, probability) {}

    void insert(const Player& player) {
        if (!find(player.playerID)) {
            add(player.playerID);
            playerScores[player.playerID] = player.score;
        } else {
            cout << "Player with ID " << player.playerID << " already exists.\n";
        }
    }

    void updateScore(int playerID, int newScore) {
        if (find(playerID)) {
            playerScores[playerID] = newScore;
        } else {
            cout << "Player with ID " << playerID << " not found.\n";
        }
    }

    void removePlayer(int playerID) {
        if (find(playerID)) {
            deleteKey(playerID);
            playerScores.erase(playerID);
            cout << "Player with ID " << playerID << " removed.\n";
        } else {
            cout << "Player with ID " << playerID << " not found.\n";
        }
    }

    vector<Player> getTopN(int N) {
        vector<Player> players;
        for (const auto& entry : playerScores) {
            players.emplace_back(Player(entry.first, entry.second));
        }
        sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
            return a.score > b.score;
        });
        if (N < static_cast<int>(players.size())) {
            players.resize(N);
        }
        return players;
    }

    int getScore(int playerID) const {
        auto it = playerScores.find(playerID);
        if (it != playerScores.end()) {
            return it->second;
        }
        cout << "Player with ID " << playerID << " not found.\n";
        return -1;
    }

    void display() const {
        cout << "Players:\n";
        for (const auto& entry : playerScores) {
            cout << "Player ID: " << entry.first << ", Score: " << entry.second << '\n';
        }
    }
};

inline void runSkipListDemo() {
    srand(static_cast<unsigned>(time(nullptr)));

    SkipStructure<int> myList(3, 0.5f);
    myList.add(15);
    myList.add(24);
    myList.add(3);
    myList.add(28);
    myList.add(18);
    myList.add(7);
    myList.add(12);

    cout << (myList.find(18) ? "18 is present!\n" : "18 is not found!\n");
    cout << "Current list contents:\n";
    myList.show();

    myList.deleteKey(18);
    cout << "After deleting 18, list contents:\n";
    myList.show();

    myList.deleteKey(3);
    myList.deleteKey(7);
    cout << "After deleting 3 and 7, list contents:\n";
    myList.show();

    myList.deleteKey(28);
    cout << "After deleting 28, list contents:\n";
    myList.show();

    cout << (myList.find(18) ? "18 is present!\n" : "18 is not found!\n");

    GameBoard leaderboard;
    leaderboard.insert(Player(1, 40));
    leaderboard.insert(Player(2, 55));
    leaderboard.insert(Player(3, 70));
    leaderboard.insert(Player(4, 95));

    cout << "\nLeaderboard:\n";
    leaderboard.display();

    leaderboard.updateScore(1, 100);
    cout << "\nAfter updating Player 1's score:\n";
    leaderboard.display();

    cout << "\nTop 3 players:\n";
    for (const auto& player : leaderboard.getTopN(3)) {
        cout << player << '\n';
    }

    cout << "\nRemove Player 2:\n";
    leaderboard.removePlayer(2);
    leaderboard.display();

    cout << "\nScore of Player 1: " << leaderboard.getScore(1) << endl;
    cout << "\nScore of Player 3: " << leaderboard.getScore(3) << endl;
    cout << "\nScore of Player 2: " << leaderboard.getScore(2) << endl;
}

#endif
