// ArcadiaEngine.cpp - STUDENT TEMPLATE
// TODO: Implement all the functions below according to the assignment requirements

#include "ArcadiaEngine.h"

#include "PlayerTable/PlayerTable.h"
#include "LeaderBoard/LeaderBoard.h"
#include "AuctionTree/AuctionTree.h"

using namespace std;

// =========================================================
// PART A: DATA STRUCTURES (Concrete Implementations)
// =========================================================

// --- 1. PlayerTable (Double Hashing) ---


// --- 2. Leaderboard (Skip List) ---



// --- 3. AuctionTree (Red-Black Tree) ---

// =========================================================
// PART B: INVENTORY SYSTEM (Dynamic Programming)
// =========================================================

// =========================================================
// PART C: WORLD NAVIGATOR (Graphs)
// =========================================================

// =========================================================
// PART D: SERVER KERNEL (Greedy)
// =========================================================


void D_menu() {
    while (true) {
        cout << "\n=== Task Scheduler Menu ===\n";
        cout << "1. Test custom tasks\n";
        cout << "2. Exit\n";
        cout << "Select an option: ";
        int choice;
        cin >> choice;
        cin.ignore(); // flush newline

        if (choice == 2) break;

        if (choice == 1) {
            string input;
            cout << "Enter tasks (letters, case-insensitive, e.g., aAbB): ";
            getline(cin, input);

            // Validate length
            if (input.length() < 1 || input.length() > 104) {
                cout << "Invalid task length! Must be 1 <= tasks.length <= 104.\n";
                continue;
            }

            // Convert all letters to uppercase
            for (char &c : input) {
                if (isalpha(c)) c = toupper(c);
            }

            // Validate letters only
            bool valid = true;
            for (char c : input) {
                if (c < 'A' || c > 'Z') {
                    valid = false;
                    break;
                }
            }
            if (!valid) {
                cout << "Invalid tasks! All tasks must be letters.\n";
                continue;
            }

            int n;
            cout << "Enter cooldown n (0 <= n <= 100): ";
            cin >> n;
            cin.ignore();
            if (n < 0 || n > 100) {
                cout << "Invalid cooldown! Must be 0 <= n <= 100.\n";
                continue;
            }

            vector<char> tasks(input.begin(), input.end());
            int intervals = ServerKernel::minIntervals(tasks, n);
            cout << "Minimum intervals needed: " << intervals << endl;
        } else {
            cout << "Invalid option. Try again.\n";
        }
    }
}

// =========================================================
// FACTORY FUNCTIONS (Required for Testing)
// =========================================================

extern "C" {
    PlayerTable* createPlayerTable() { 
        return new ConcretePlayerTable(); 
    }

    Leaderboard* createLeaderboard() { 
        return new ConcreteLeaderboard(); 
    }

    AuctionTree* createAuctionTree() { 
        return new ConcreteAuctionTree(); 
    }
}