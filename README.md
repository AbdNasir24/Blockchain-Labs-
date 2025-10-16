# Simplified Blockchain Implementation in C++

This repository contains the C++ source code for the "Atelier 1: Implémentation complète d'une blockchain simplifiée en C++" workshop. Each exercise is located in its own directory.

## Prerequisites

You need a C++ compiler that supports the C++11 standard, such as `g++`.
## Steps to Clone the Repository

git clone https://github.com/AbdNasir24/Blockchain-Labs-.git

## Project Files

-   `sha256.h`: A simple, header-only library for SHA-256 hashing used across all exercises.
-   `exercice1_merkle_tree/`: Contains the implementation of a Merkle Tree.
-   `exercice2_proof_of_work/`: Contains the implementation of a blockchain using the Proof of Work (PoW) consensus mechanism.
-   `exercice3_proof_of_stake_comparison/`: Contains a simplified implementation of Proof of Stake (PoS) and compares its block validation time against Proof of Work.

## Compilation and Execution

Navigate into the directory of the exercise you want to run and use the following commands.

### Exercice 1: Merkle Tree

```bash
# Navigate to the directory
cd exercice1_merkle_tree

# Compile the source code
g++ -std=c++11 -o merkle_tree main.cpp

# Run the executable
./merkle_tree
```

### Exercice 2: Proof of Work

```bash
# Navigate to the directory
cd exercice2_proof_of_work

# Compile the source code
g++ -std=c++11 -o proof_of_work main.cpp

# Run the executable
./proof_of_work
```

### Exercice 3: Proof of Stake vs Proof of Work

```bash
# Navigate to the directory
cd exercice3_proof_of_stake_comparison

# Compile the source code
g++ -std=c++11 -o comparison main.cpp

# Run the executable
./comparison
```
