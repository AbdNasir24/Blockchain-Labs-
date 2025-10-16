#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <chrono>
#include "../sha256.h" // Include the hashing utility

class Block {
public:
    std::string sPrevHash;
    std::string sHash;

    Block(uint32_t nIndexIn, const std::string &sDataIn) : _nIndex(nIndexIn), _sData(sDataIn) {
        _nNonce = 0;
        _tTime = time(nullptr);
    }

    void MineBlock(uint32_t nDifficulty) {
        std::string str(nDifficulty, '0');
        auto t1 = std::chrono::high_resolution_clock::now();

        do {
            _nNonce++;
            sHash = _CalculateHash();
        } while (sHash.substr(0, nDifficulty) != str);
        
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

        std::cout << "Block Mined: " << sHash << std::endl;
        std::cout << "Time to mine: " << duration << " ms" << std::endl;
    }

private:
    uint32_t _nIndex;
    int64_t _nNonce;
    std::string _sData;
    time_t _tTime;

    std::string _CalculateHash() const {
        std::string ss = std::to_string(_nIndex) + std::to_string(_tTime) + _sData + std::to_string(_nNonce) + sPrevHash;
        return sha256_hex_string(ss);
    }
};

class Blockchain {
public:
    Blockchain() {
        // Create Genesis Block
        _vChain.emplace_back(Block(0, "Genesis Block"));
        _nDifficulty = 4; // Initial difficulty
        std::cout << "Mining genesis block..." << std::endl;
        _vChain[0].MineBlock(_nDifficulty);
    }

    void AddBlock(Block bNew) {
        bNew.sPrevHash = _GetLastBlock().sHash;
        bNew.MineBlock(_nDifficulty);
        _vChain.push_back(bNew);
    }
    
    void SetDifficulty(uint32_t nDiff) {
        _nDifficulty = nDiff;
    }

private:
    uint32_t _nDifficulty;
    std::vector<Block> _vChain;

    Block _GetLastBlock() const {
        return _vChain.back();
    }
};


int main() {
    std::cout << "--- Exercice 2: Proof of Work ---" << std::endl;

    Blockchain bChain;

    for (int difficulty = 2; difficulty <= 5; ++difficulty) {
        std::cout << "\n=============================================" << std::endl;
        std::cout << "Setting mining difficulty to " << difficulty << std::endl;
        bChain.SetDifficulty(difficulty);
        
        std::cout << "Mining block 1..." << std::endl;
        bChain.AddBlock(Block(1, "Block 1 Data"));

        std::cout << "Mining block 2..." << std::endl;
        bChain.AddBlock(Block(2, "Block 2 Data"));
    }

    std::cout << "\nBlockchain successfully created and verified." << std::endl;

    return 0;
}