#include <iostream> //In-Out stream so I can read and write to the console
#include <string> //In case I need to manage strings
#include <cstdlib> //For using random
#include <ctime> //Using this to seed RNG
#include <vector> //I love overcomplicated coding

using namespace std; //Cuz I need this for like literally everything ever

bool CorrectUI(vector<string> goodInputs, string input) { //simplifying if the player input is acceptable or not because I dont want to write ifs or switches 8,000 times
	for (string i : goodInputs)
	{
		if (input == i) {
			return true;
		}
	}
	return false;
}

class Enemy { //I may have borrowed this idea from a friend.
public:
	string name;
	string intro;
	int attack;
	int block;
	int aggro;
	int health;
	int goldDrop;
	Enemy(string na, string in, int at, int bl, int ag, int he, int go) {
		name = na;
		intro = in;
		attack = at;
		block = bl;
		aggro = ag;
		health = he;
		goldDrop = go;
	}
};

string LowercaseString(string input) { //Converts the string to lowercase so responses aren't case sensitive
	string temp = input;
	for (int i = 0; i < input.size(); i++) {
		temp[i] = tolower(input[i]);
	}
	return temp;
}

string Response() { //Gets the player input and returns it
	string input;
	getline(cin, input); //gets whole line, including spaces
	input = LowercaseString(input);
	//cout << input << "\n";
	return input;
}

string Response(string prompt) { //overload for giving a prompt
	cout << prompt;
	return Response();
}

void Welcome() {
	//welcome the player
	cout << "Note: Inputs are not case sensitive.\n\n";
	cout << "Welcome player!\nAre you ready to go on an adventure? (Y/N)\n";
}

void NameResponse(string playerName = "default") {
	switch (rand() % 5) { //just a unique response everytime a user inputs a name
	case 0:
		cout << playerName << "? That's a good name\n";
		break;
	case 1:
		cout << playerName << " suits you well!\n";
		break;
	case 2:
		cout << playerName << "? Very original!\n";
		break;
	case 3:
		cout << playerName << "? Like that musician?\n";
		break;
	case 4:
		cout << playerName << ". Damn, I'm sorry your parents hate you\n";
		break;
	default:
		cout << playerName << "? ew...\n";
		break;
	}
}

void GameLoop() {
	string playerName; //Using this so players can name their characters!!
	string playerInput; //Holder for player inputs
	vector<string> yesNo = { "y", "yes", "n", "no"};
	vector<string> actions = { "a", "attack", "b", "block" };

	Enemy shieldSkeleton("Shield Skeleton", "a skeleton wielding an iron shield", 3, 7, 1, 5, 5);
	Enemy swordSkeleton("Sword Skeleton", "a skeleton wielding an iron sword", 7, 2, 7, 5, 5);
	Enemy golem("Golem", "a hulking golem made of stone", 4, 4, 4, 15, 15);
	Enemy bat("Large Bat", "a large bat hanging in the room", 6, 2, 8, 4, 10);
	Enemy mimic("Chest Mimic", "a chest that seems to be breathing", 5, 6, 3, 10, 50);
	Enemy ghoul("Ghoul", "a shambling corpse of another adventurer", 5, 5, 6, 6, 15);

	Enemy enemies[] = { shieldSkeleton, swordSkeleton, golem, bat, mimic, ghoul };

	//seed the random number generator
	srand(time(0));

	Welcome();
	playerInput = Response();

	while (!CorrectUI(yesNo, playerInput)) //waits for a proper response
	{
		playerInput = Response("Please give a proper response!\n");
	}

	if (playerInput == "y" || playerInput == "yes") {
		cout << "That's wonderful! \nDo you mind telling me your name: ";
		getline(cin, playerName);
		NameResponse(playerName);
	}
	else {
		cout << playerName + " lives a long boring life and die of dysentery."; //Coward's way out
		return 0;
	}

	cout << "\n" + playerName + " wanders into a dungeon, preparing for a fight!\n";
	//set up the game
	int health = 20;
	int attack;
	int maxAttack = 6;
	int block;
	int maxBlock = 6;
	int turn = 0;
	int gold = 10;
	int room = 1;


	while (health > 0) { //While above zero health do the game loop
		if (room % 5 == 0) { //Checkpoint every five rooms that give you the chance to leave. You choose to continue your attack and block go up and your health is restored.
			cout << "\nYou enter a new room with nothing but a small fire, rest area, and some food.\n";
			playerInput = Response("Do you leave with a fortune of " + to_string(gold) + " gold? (Y/N) ");
			while (!CorrectUI(yesNo, playerInput)) //waits for a proper response
			{
				playerInput = Response("Please give a proper response!\n");
			}
			if (playerInput == "y" || playerInput == "yes") { //Player chooses to leave, game ends (gold = score)
				cout << "Choosing to leave before it's too late " + playerName + " leaves the dungeon with a small fortune of " + to_string(gold) + " gold!\n";
				cout << "They made it through " + to_string(room) + " rooms!\n";
				return 0;
			}
			else { //Player continues, increasing stats and restoring health!
				cout << "Deciding to push on, " + playerName + " has grown a little stronger!\n";
				maxAttack++;
				maxBlock++;
				health = 20;
				cout << "Block has grown a little stronger(" + to_string(maxBlock) + ")\n";
				cout << "Attack has grown a little stronger(" + to_string(maxAttack) + ")\n";
				cout << "Health has been restored!\n";
			}
			room++;
		}
		else { //Enemy encounters
			Enemy enemy = enemies[rand() % 6]; //Selects one of the 6 enemies
			int enemyRoll;
			turn = 0;
			cout << "\nWandering into a new room " + playerName + " finds " << enemy.intro << "\n";
			cout << playerName + " has " + to_string(health) + " health.\n";
			cout << "The " + enemy.name + " has " + to_string(enemy.health) + " health.\n";
			while (enemy.health > 0) { //Attack/Defend loop
				if (health <= 0) {
					cout << playerName + " has died.\n";
					cout << "They made it through " + to_string(room) + " rooms!";
					return 0;
				}
				turn++;
				cout << "\nIt's turn " + to_string(turn) + ".\n";
				playerInput = Response("Does " + playerName + " \"Attack(A)\" or \"Block(B)\": "); //prompt for player action

				while (!CorrectUI(actions, playerInput)) //waits for a proper response
				{
					playerInput = Response("Please choose a valid option\n");
				}

				int enemyAction = rand() % 10; //Chooses a random number that determines if the enemy attacks or blocks based off their aggro stats
				if (enemy.aggro < enemyAction) { //aggro less than action level, then they block
					if (playerInput == "a" || playerInput == "attack") { //player chooses to attack, then damage calc is enemy health - (player attack roll - enemy block)
						attack = (rand() % maxAttack) + 1;
						cout << playerName + " attacks for " + to_string(attack) + " points.\n";
						enemyRoll = rand() % enemy.block;
						cout << "The " + enemy.name + " blocks for " + to_string(enemyRoll) + " points.\n";
						if (attack > enemyRoll) {
							enemy.health -= attack - enemyRoll;
							cout << "Yes! " + playerName + " hit the " + enemy.name + " for " + to_string(attack - enemyRoll) + " points of damage! Leaving it with " + to_string(enemy.health) + " health left!\n";
						}
						else { //Attack is blocked
							cout << "No! " + playerName + "'s attack was blocked!\n";
						}
					}
					else { //player choose to block, no damage is done
						cout << "Everyone blocked, no damage is dealt.\n";
						if (health < 20) {
							cout << playerName + " heals for 1 point of health.\n";
							health++;
							cout << playerName + " has " + to_string(health) + " health.\n";
						}
					}
				}
				else { //aggro greater than or equal to action level, then they attack
					if (playerInput == "a" || playerInput == "attack") { //player chooses to attack, damage calc is enemy health - player attack roll and player health - enemy attack roll
						attack = (rand() % maxAttack) + 1;
						cout << playerName + " attacks for " + to_string(attack) + " points.\n";
						enemyRoll = rand() % enemy.attack;
						cout << "The " + enemy.name + " attacks for " + to_string(enemyRoll) + " points.\n";
						health -= enemyRoll;
						enemy.health -= attack;
						cout << playerName + " hit the " + enemy.name + " for " + to_string(attack) + " points of damge! Leaving it with " + to_string(enemy.health) + " health!\n";
						cout << "The " + enemy.name + " hit " + playerName + " for " + to_string(enemyRoll) + " points of damage! Leaving them with " + to_string(health) + " health!\n";
					}
					else { //player choose to block, damage calc is player health - (enemy damage roll - player block roll)
						block = (rand() % maxBlock) + 1;
						cout << playerName + " blocks for " + to_string(block) + " points.\n";
						enemyRoll = rand() % enemy.attack;
						cout << "The " + enemy.name + " attacks for " + to_string(enemyRoll) + " points.\n";
						if (block < enemyRoll) {
							health -= enemyRoll - block;
							cout << "No! The " + enemy.name + " hit the " + enemy.name + " for " + to_string(enemyRoll - block) + " points of damage! Leaving them with " + to_string(health) + " health left!\n";
							if (health < 20 && health > 0) {
								cout << playerName + " heals for 1 point of health.\n";
								health++;
								cout << playerName + " has " + to_string(health) + " health.\n";
							}
						}
						else { //Attack is blocked
							cout << "Yes! The " + enemy.name + "'s attack was blocked!\n";
							if (health < 20 && health > 0) {
								cout << playerName + " heals for 1 point of health.\n";
								health++;
								cout << playerName + " has " + to_string(health) + " health.\n";
							}
						}
					}
				}
			}
			int goldRoll = round((rand() % (enemy.goldDrop / 2)) + (enemy.goldDrop / 2));
			gold += goldRoll;
			cout << "The " + enemy.name + " has dropped " + to_string(goldRoll) + " gold.\nYou now have " + to_string(gold) + " gold!\n";
			room++;
		}
	};
	cout << playerName + " has died.\n";
	cout << "They made it through " + to_string(room) + " rooms!";
	return 0;

}

int main() { //Coming back to this project, I realize I must have been on crack or something. This is some gibberish.
	GameLoop();
}