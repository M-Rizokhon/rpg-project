# Text-Based RPG Game

## Overview
This is a text-based Role-Playing Game (RPG) developed in C++ as a freshman-year project. The game immerses players in a fantasy world where they control a hero, battling randomly generated enemies, collecting loot, managing an inventory, and upgrading their character through a shop system. The project demonstrates proficiency in Object-Oriented Programming (OOP), the C++ Standard Template Library (STL), and game design principles.

## Features
- **Character System**: Players control a `Knight` with attributes like health, attack, defense, XP, level, potions, and gold. The `Character` class supports leveling up, using potions, and equipping items.
- **Combat Mechanics**: Turn-based battles with randomized damage, a 20% chance for critical hits, and defense-based damage reduction.
- **Inventory Management**: Players can collect and equip weapons and armor, which provide attack or defense bonuses.
- **Randomized Enemies**: Enemies are generated with varying stats based on difficulty level, using the `mt19937` random number generator for fairness and variety.
- **Loot System**: Defeated enemies may drop gold, potions, or items (40% chance for gold, 30% for potions, 25% for items, 5% no drop).
- **Shop System**: Players can spend gold to buy potions or upgrade attack/defense stats.
- **Polished User Experience**: Timed delays (`std::chrono`, `std::thread`) enhance the flow of combat and interactions.

## Technologies Used
- **Language**: C++17
- **Libraries**: 
  - Standard Template Library (`vector`, `random`, `chrono`, `thread`)
  - `iostream`, `string`, `limits` for I/O and input handling
- **Key Concepts**: OOP (classes, encapsulation), randomization (`mt19937`, `random_device`), pointers, modular design

## Installation
### Prerequisites
- A C++ compiler supporting C++17 (e.g., g++ 7.0 or later, clang, MSVC)
- Operating System: Windows, macOS, or Linux

### Setup
1. Clone or download the project files to your local machine.
2. Ensure you have a C++ compiler installed (e.g., `g++`).
3. Compile the code using the following command:
   ```bash
   g++ -std=c++17 main.cpp -o rpg_game
   ```
4. Run the executable:
   ```bash
   ./rpg_game
   ```

## How to Play
1. **Start the Game**: Run the compiled executable. You begin as a `Knight` with 100 health, 20 attack, 10 defense, 2 potions, and 0 gold.
2. **Combat**: Face three increasingly difficult enemies. Each battle is turn-based:
   - Your hero attacks, dealing randomized damage (with a 20% chance for a critical hit).
   - The enemy retaliates if still alive.
   - View health updates after each attack.
3. **Post-Battle**:
   - If you win, gain 100 XP (level up at 100 XP) and a random loot drop (gold, potion, or item).
   - Choose to view/equip items from your inventory or use a potion to heal.
   - Decide whether to visit the shop to spend gold on potions (+30 health, 30 gold), attack upgrades (+1, 50 gold), or defense upgrades (+1, 50 gold).
4. **Game End**: Clear all three encounters to win, or lose if your health reaches 0.

## Project Structure
- `Source.cpp`: Contains the game logic, including the main loop, enemy generation, loot drops, and shop functionality.
- **Classes**:
  - `Item`: Represents weapons or armor with attack/defense bonuses.
  - `Character`: Manages player/enemy stats, combat, inventory, and equipment.
- **Key Functions**:
  - `generateRandomEnemy`: Creates enemies with randomized stats.
  - `lootDrop`: Handles probabilistic loot drops after battles.
  - `shop`: Allows purchasing items or upgrades.

## Example Gameplay
```
=== ENCOUNTER 1 ===
GoblinLv1's Stats:
Health: 95
Attack: 12
Defense: 6
Level: 1
XP: 0/100
Potions: 2
Gold: 0

Knight attacks GoblinLv1 for 18 damage!
GoblinLv1's health: 77

GoblinLv1 attacks Knight for 5 damage!
Knight's health: 95

[Battle continues...]

Knight defeated GoblinLv1!
Knight gained 100 XP and leveled up to level 2!
Knight picked up 25 gold!
Do you want to view inventory and equip items? (y/n): n
Would you like to use a potion to heal? (y/n): n
Enter shop before next battle? (y/n): y

Welcome to the shop!
Your gold: 25
1. Buy Potion (30 gold)
2. Increase Attack (+1) (50 gold)
3. Increase Defense (+1) (50 gold)
4. Exit shop
```

## Limitations and Future Improvements
- **Error Handling**: Basic input validation is implemented, but more robust handling (e.g., loops for invalid inputs) could be added.
- **Memory Management**: Uses raw pointers for equipped items; could be improved with `std::unique_ptr` for safety.
- **Features**: Future versions could include:
  - A graph-based dungeon map with pathfinding (e.g., A* algorithm).
  - File I/O for saving/loading game state.
  - A graphical interface using SFML or raylib.
  - AI-driven enemy behaviors (e.g., decision trees).

## About the Developer
This project was developed by Muhammad Rizohon as a freshman-year project to demonstrate C++ programming skills and game design. It reflects self-learning of advanced C++ features (e.g., `mt19937`, `chrono`) and a passion for creating interactive applications. I am preparing for a Master’s in Computer Science at MIT and aim to build on this project with more complex algorithms and systems.

## License
This project is unlicensed and intended for educational purposes. Feel free to explore, modify, or extend the code!