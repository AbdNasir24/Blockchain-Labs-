#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include "../sha256.h" // Include the hashing utility

// --- Part 1: Proof of Work Implementation (Simplified for comparison) ---

std::string calculatePoWHash(int index, const std::string& prevHash, int& nonce) {
    std::string input = std::to_string(index) + prevHash + std::to_string(nonce);
    return sha256_hex_string(input);
}

void minePoWBlock(int difficulty) {
    std::cout << "Mining a Proof of Work block with difficulty " << difficulty << "..." << std::endl;
    std::string prevHash = "0";
    int nonce = 0;
    std::string target(difficulty, '0');
    
    auto start = std::chrono::high_resolution_clock::now();
    
    while (true) {
        std::string hash = calculatePoWHash(1, prevHash, nonce);
        if (hash.substr(0, difficulty) == target) {
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "PoW Block Mined! Nonce: " << nonce << std::endl;
            std::cout << "PoW Execution Time: " << duration.count() << " microseconds (" << duration.count() / 1000.0 << " ms)" << std::endl;
            break;
        }
        nonce++;
    }
}


// --- Part 2: Proof of Stake Implementation (Conceptual) ---

struct Validator {
    std::string address;
    int stake; // Represents the amount of currency staked
};

// Select a validator based on their stake (weighted random selection)
Validator chooseValidator(const std::vector<Validator>& validators) {
    int totalStake = 0;
    for (const auto& v : validators) {
        totalStake += v.stake;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, totalStake);
    int random_pick = distrib(gen);

    int currentStake = 0;
    for (const auto& v : validators) {
        currentStake += v.stake;
        if (random_pick <= currentStake) {
            return v;
        }
    }
    return validators.back(); // Should not happen
}

void forgePoSBlock(const std::vector<Validator>& validators) {
    std::cout << "\nForging a Proof of Stake block..." << std::endl;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    Validator chosenValidator = chooseValidator(validators);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "PoS Block Forged! Validator '" << chosenValidator.address << "' was chosen." << std::endl;
    std::cout << "PoS Execution Time: " << duration.count() << " microseconds (" << duration.count() / 1000.0 << " ms)" << std::endl;
}


// --- Part 3: Main function for comparison ---

int main() {
    std::cout << "--- Exercice 3: Proof of Work vs. Proof of Stake ---" << std::endl;
    std::cout << "This program compares the execution time for validating one block.\n" << std::endl;
    
    // --- PoW Demonstration ---
    int pow_difficulty = 5; // A reasonable difficulty for a quick demo
    minePoWBlock(pow_difficulty);

    // --- PoS Demonstration ---
    std::vector<Validator> validators = {
        {"Alice", 100},
        {"Bob", 50},
        {"Charlie", 250},
        {"Dave", 80}
    };
    forgePoSBlock(validators);

    // --- Conclusion ---
    std::cout << "\n--- Conclusion ---" << std::endl;
    std::cout << "As demonstrated, Proof of Work requires significant computational effort, and its execution time increases exponentially with difficulty." << std::endl;
    std::cout << "Proof of Stake, on the other hand, is nearly instantaneous as it replaces the computational puzzle with a weighted selection algorithm. This makes it much faster and more energy-efficient." << std::endl;
    std::cout << "(Note: The speed of your specific PoW implementation depends on your computer's performance.)" << std::endl;

    return 0;
}