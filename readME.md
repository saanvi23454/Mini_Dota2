# Dota2 Middle Lane Simulation

## Overview
This project simulates a **Dota2 middle lane battle**, where heroes from opposing teams (Radiant and Dire) move toward each other on a lane. The heroes have specific attributes like position, health, and team allegiance. The objective is to simulate battles as heroes encounter each other and determine which heroes survive after all possible battles are resolved.

This project is still a **work in progress**, with room for enhancements. The current implementation focuses on determining the health of remaining heroes after all battles are completed. Additional metrics and features are planned for future iterations.

---

## How to Run the C++ Code on Your Machine

### Prerequisites
- A C++ compiler (e.g., `g++`)
- A terminal or an Integrated Development Environment (IDE) that supports C++

### Instructions
1. **Clone the repository**:
    ```bash
    git clone https://github.com/saanvi23454/Mini_Dota2.git
    ```
2. **Navigate to the project directory**:
    ```bash
    cd Mini_Dota2
    ```
3. **Compile the C++ file**:
    ```bash
    g++ Dota2.cpp -o dota2_simulation
    ```
4. **Run the executable**:
    ```bash
    ./dota2_simulation
    ```
---

## Game Rules
1. There are `n` heroes on the middle lane.
2. Each hero has three attributes:
    - **Position**: The location on the lane (unique integers).
    - **Health**: The health value of the hero.
    - **Team**: Either 'R' for Radiant or 'D' for Dire.
3. Radiant heroes move upwards, while Dire heroes move downwards.
4. Heroes move simultaneously at the same speed.
5. **Battle Mechanics**:
    - When two heroes meet at the same position, a battle occurs.
    - The hero with less health is eliminated, and the health of the other hero decreases by 1.
    - If both heroes have equal health, they are both removed.
6. The game continues until no more battles are possible.
7. The result is an array showing the health of the remaining heroes in their original input order.

---

## Input Format
The program expects the following inputs:

1. **Number of heroes (n)**: An integer.
2. **Positions array**: A 0-indexed array of integers where each value represents the position of a hero.
3. **Health array**: A 0-indexed array of integers where each value represents the health of a hero.
4. **Team string**: A string of characters ('R' for Radiant, 'D' for Dire) where each character indicates the team of the corresponding hero.

## Example TestCase
Input : (each on newline)
- 4
- 3 5 2 6
- 10 10 15 12
- RDRD

Output: [14]
