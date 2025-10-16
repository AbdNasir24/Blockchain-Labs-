#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "../sha256.h" // Include the hashing utility

// A node in the Merkle Tree
struct MerkleNode {
    std::string hash;
    std::unique_ptr<MerkleNode> left;
    std::unique_ptr<MerkleNode> right;

    MerkleNode(std::string h) : hash(h), left(nullptr), right(nullptr) {}
};

// Function to build the Merkle Tree and return the root hash
std::string buildMerkleTree(const std::vector<std::string>& transactions) {
    if (transactions.empty()) {
        return sha256_hex_string("");
    }

    // 1. Create leaf nodes from transaction data
    std::vector<std::string> level;
    for (const auto& tx : transactions) {
        level.push_back(sha256_hex_string(tx));
    }

    // 2. Build the tree level by level
    while (level.size() > 1) {
        // If the number of nodes is odd, duplicate the last one
        if (level.size() % 2 != 0) {
            level.push_back(level.back());
        }

        std::vector<std::string> next_level;
        // Combine pairs of hashes to create the next level
        for (size_t i = 0; i < level.size(); i += 2) {
            std::string combined_hash = level[i] + level[i + 1];
            next_level.push_back(sha256_hex_string(combined_hash));
        }
        level = next_level; // Move to the next level up
    }

    // The last remaining hash is the Merkle Root
    return level[0];
}

int main() {
    std::cout << "--- Exercice 1: Merkle Tree ---" << std::endl;

    // Example 1: A list of transactions
    std::vector<std::string> transactions1 = {
        "Transaction A -> B: 10 BTC",
        "Transaction C -> D: 5 BTC",
        "Transaction E -> F: 2 BTC",
        "Transaction G -> H: 8 BTC"
    };

    std::cout << "\nCalculating Merkle Root for 4 transactions..." << std::endl;
    std::string merkleRoot1 = buildMerkleTree(transactions1);
    std::cout << "Merkle Root: " << merkleRoot1 << std::endl;

    // Example 2: An odd number of transactions
    std::vector<std::string> transactions2 = {
        "Data 1",
        "Data 2",
        "Data 3"
    };

    std::cout << "\nCalculating Merkle Root for 3 transactions (odd number)..." << std::endl;
    std::string merkleRoot2 = buildMerkleTree(transactions2);
    std::cout << "Merkle Root: " << merkleRoot2 << std::endl;

    // Example 3: A single transaction
    std::vector<std::string> transactions3 = {
        "Only one transaction"
    };

    std::cout << "\nCalculating Merkle Root for 1 transaction..." << std::endl;
    std::string merkleRoot3 = buildMerkleTree(transactions3);
    std::cout << "Merkle Root: " << merkleRoot3 << std::endl;

    return 0;
}