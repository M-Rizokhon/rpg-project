#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <random>
#include <limits>
#include <vector>
using namespace std;

// one global RNG
random_device rd;
mt19937 gen(rd());

// ---------------------------------------------------------------------------
enum class ItemType{Weapon, Armor};

class Item {
private:
	string name;
	ItemType type;
	int bonusAttack;
	int bonusDefense;

public:
	Item(string name, ItemType type, int attack = 0, int defense = 0);

	string getName() const;
	ItemType getType() const;
	int getBonusAttack() const;
	int getBonusDefense() const;
};


// constructor
Item::Item(string name, ItemType type, int attack, int defense)
	: name(name), type(type), bonusAttack(attack), bonusDefense(defense) {
}


// getter functions
string Item::getName() const { return name; }
ItemType Item::getType() const { return type; }
int Item::getBonusAttack() const { return bonusAttack; }
int Item::getBonusDefense() const { return bonusDefense; }



// ---------------------------------------------------------------------------

class Character {
private:
	string name;
	int health;
	int attack_power;
	int defense;
	int xp;
	int level;
	int potions;
	int gold;

	vector<Item> inventory;
	Item* equippedWeapon;
	Item* equippedArmor;

public:
	Character(string name, int attack_power, int defense, int health = 100);
	void printStats() const;
	void printShortStats() const;
	void takeDamage(int dmg);
	void attack(Character& target);
	
	string getName() const;
	bool isAlive() const;

	void gainXP(int amount);
	bool usePotion();
	void addPotion();

	void gainGold(int amount);
	int getGold() const;
	bool spendGold(int amount);
	void increaseAttack(int value);
	void increaseDefense(int value);

	void addItem(const Item& item);
	void showInventory() const;
	void equipItem(int index);
	int getTotalAttack() const;
	int getTotalDefense() const;
};

// constructor
Character::Character(string name, int attack_power, int defense, int health) :
	name(name), attack_power(attack_power), defense(defense),
	health(health), xp(0), level(1), potions(2), gold(0) {
	equippedWeapon = nullptr;
	equippedArmor = nullptr;
}


// a function to print the Character stats
void Character::printStats() const {
	cout << name << "'s Stats:\n"
		<< "Health: " << health << '\n'
		<< "Attack: " << attack_power << '\n'
		<< "Defense: " << defense << '\n'
		<< "Level: " << level << '\n'
		<< "XP: " << xp << "/100\n"
		<< "Potions: " << potions << '\n'
		<< "Gold: " << gold << endl;
}


// a function to print a short stats of the character
void Character::printShortStats() const {
	cout << name << "'s health: " << health << '\n';
}


// a function to simulate a damage, that reduces the character's health
void Character::takeDamage(int dmg) {
	int final_damage = dmg - getTotalDefense();

	// if damage is less than 1
	// it will be assigned to 1 anyway
	if (final_damage < 1)
		final_damage = 1;

	health -= final_damage;

	// health should never go below zero
	if (health < 0)
		health = 0;
}


// a function to simulate an attack on another character
void Character::attack(Character& target) {
	
	uniform_int_distribution<> damageDist(getTotalAttack() - 5, getTotalAttack() + 5);
	uniform_real_distribution<> critDist(0.0, 1.0);


	// calculating base damage
	int damage = damageDist(gen);

	// 20% chance for critical hit
	if (critDist(gen) < 0.2) {
		cout << "CRITICAL HIT by " << name << "!\n";
		damage *= 2;
	}

	// Deal the damage
	target.takeDamage(damage);
	cout << name << " attacks " << target.getName() << " for " << damage << " damage!\n";
}


// function to get the name
string Character::getName() const {
	return name;
}


// check if the character is alive
bool Character::isAlive() const {
	return health > 0;
}


void Character::gainXP(int amount) {
	xp += amount;
	if (xp >= 100) {
		level++;
		attack_power += 5;
		defense += 5;
		health = 100;
		xp -= 100;
		cout << name << " leveled up to level " << level << '!' << endl;
	}
}


// function to use potions and increase health points
bool Character::usePotion() {
	if (potions > 0 && health < 100) {
		health += 30;
		if (health > 100) health = 100;
		potions--;
		cout << name << " used a healing potion! Health restored to " << health << "." << endl;
		return true;
	}
	else if (potions == 0) {
		cout << name << " has no potions left." << endl;
	}
	else { cout << name << " is already at full health." << endl; }
	
	return true;
}

// add potion to a character
void Character::addPotion() { potions++; }





// function to get the gold of enemy after defeating them
void Character::gainGold(int amount) {
	gold += amount;
	cout << name << " picked up " << amount << " gold!\n";
}


int Character::getGold() const {
	return gold;
}


bool Character::spendGold(int amount) {
	if (gold >= amount) {
		gold -= amount;
		return true;
	}
	cout << "Not enough gold!\n";
	return false;
}


void Character::increaseAttack(int value) {
	attack_power += value;
}

void Character::increaseDefense(int value) {
	defense += value;
}



// adding an item to the inventory
void Character::addItem(const Item& item) {
	inventory.push_back(item);
	cout << name << " picked up " << item.getName() << endl;
}


// display all items in the inventory
void Character::showInventory() const {
	cout << "\nInventory:\n";
	for (size_t i = 0; i < inventory.size(); ++i) {
		cout << i + 1 << ". " << inventory[i].getName() << " (";
		if (inventory[i].getType() == ItemType::Weapon)
			cout << "+" << inventory[i].getBonusAttack() << " ATK";
		else
			cout << "+" << inventory[i].getBonusDefense() << " DEF";
		cout << ")\n";
	}
}


void Character::equipItem(int index) {
	if (index < 1 || index > inventory.size()) {
		cout << "Invalid selection.\n";
		return;
	}

	Item& item = inventory[index - 1];

	if (item.getType() == ItemType::Weapon) {
		equippedWeapon = &item;
		cout << "Equipped weapon: " << item.getName() << '\n';
	}
	else {
		equippedArmor = &item;
		cout << "Equipped armor: " << item.getName() << '\n';
	}
}


int Character::getTotalAttack() const {
	int bonus = equippedWeapon ? equippedWeapon->getBonusAttack() : 0;
	return attack_power + bonus;
}

int Character::getTotalDefense() const {
	int bonus = equippedArmor ? equippedArmor->getBonusDefense() : 0;
	return defense + bonus;
}	





// -----------------------------------------------------------------------------------------------

// a function to generate a random character enemy
Character generateRandomEnemy(int difficulty_level) {

	uniform_int_distribution<> attackDist(10 + difficulty_level * 2, 20 + difficulty_level * 2);
	uniform_int_distribution<> defenseDist(5 + difficulty_level, 10 + difficulty_level);
	uniform_int_distribution<> healthDist(80, 120);

	string names[] = { "Goblin", "Skeleton", "Bandit", "Zombie", "Dark Elf", "Orc Warrior" };
	uniform_int_distribution<> nameDist(0, 5);

	string name = names[nameDist(gen)] + "Lv" + to_string(difficulty_level);
	int attack = attackDist(gen);
	int defense = defenseDist(gen);
	int health = healthDist(gen);

	return Character(name, attack, defense, health);
}


void lootDrop(Character& hero, mt19937& gen) {
	uniform_real_distribution<> dropChance(0.0, 1.0);
	uniform_int_distribution<> goldDrop(10, 50);
	uniform_int_distribution<> itemTypeDist(0, 1);   // 0 - weapon, 1 - armor
	uniform_int_distribution<> statBoost(3, 10);

	double roll = dropChance(gen);

	if (roll < 0.4)
		hero.gainGold(goldDrop(gen));
	else if (roll < 0.7) {
		cout << hero.getName() << " found a potion.\n";
		hero.addPotion();
	}
	else if (roll < 0.95) {
		// creating a random item
		ItemType type = itemTypeDist(gen) == 0 ? ItemType::Weapon : ItemType::Armor;
		int boost = statBoost(gen);
		string itemName = (type == ItemType::Weapon ? "Sword +" : "Armor +") + to_string(boost);
		Item newItem(itemName, type, type == ItemType::Weapon ? boost : 0, type == ItemType::Armor ? boost : 0);
		hero.addItem(newItem);
	}
	else
		cout << "No loot dropped this time.\n";
}



void shop(Character& hero) {
	cout << "\nWelcome to the shop!\n";
	cout << "Your gold: " << hero.getGold() << endl;

	cout << "1. Buy Potion (30 gold)\n";
	cout << "2. Increase Attack (+1) (50 gold)\n";
	cout << "3. Increase Defense (+1) (50 gold)\n";
	cout << "4. Exit shop\n";

	int choice;
	cin >> choice;

	switch (choice) {
	case 1:
		if (hero.spendGold(30)) {
			hero.addPotion();
			cout << "You bought potion\n";
			break;
		}
	case 2:
		if (hero.spendGold(50)) {
			hero.increaseAttack(1);
			cout << "Attack increased!\n";
			break;
		}
	case 3:
		if (hero.spendGold(50)) {
			hero.increaseDefense(1);
			cout << "Defense increased!\n";
			break;
		}
	case 4:
		cout << "Leaving the shop!\n";
		break;
	default:
		cout << "Invalid choice!\n";
	}
}




// ---------------------------------------------------------------------------

int main() {
	Character hero("Knight", 20, 10);
	
	for (int i = 1; i <= 3; ++i) {
		cout << "=== ENCOUNTER " << i << " ===\n";
		Character enemy = generateRandomEnemy(i);
		enemy.printStats();
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));


		// Battle loop
		while (hero.isAlive() && enemy.isAlive()) {
			hero.attack(enemy);
			enemy.printShortStats();
			if (!enemy.isAlive()) break;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			cout << "\n\n";

			enemy.attack(hero);
			hero.printShortStats();
			if (!hero.isAlive()) break;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			cout << "\n\n";
		}

		if (hero.isAlive()) {
			cout << hero.getName() << " defeated " << enemy.getName() << '!' << endl;
			hero.gainXP(100);
			lootDrop(hero, gen);

			cout << "Do you want to view inventory and equip items? (y/n): ";
			char invChoice;
			cin >> invChoice;

			if (invChoice == 'y' || invChoice == 'Y') {
				hero.showInventory();
				cout << "Enter the item number to equip (0 to skip): ";
				int index;
				cin >> index;

				if (cin.fail() || index < 0) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Skipping.\n";
				}
				else if (index > 0) {
					hero.equipItem(index);
				}
			}

			
			cout << "Would you like to use a potion to heal? (y/n): ";
			char choice;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (choice == 'y' || choice == 'Y')
				hero.usePotion();


			cout << "\nEnter shop before next battle? (y/n): ";
			cin >> choice;
			if (choice == 'y' || choice == 'Y') {
				shop(hero);
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
			cout << "\n==============================\n\n";
		}
		else {
			cout << hero.getName() << " was slain in battle...\n";
			break;
		}
	}

	if (hero.isAlive()) {
		cout << hero.getName() << " has cleared the dungeon!\n";
		hero.printStats();
	}
	else {
		cout << "Game over!\n";
	}


	return 0;
}




