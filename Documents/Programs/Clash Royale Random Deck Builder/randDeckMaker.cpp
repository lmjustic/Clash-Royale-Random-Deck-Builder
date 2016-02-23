/* randDeckMaker.cpp
 *
 * Luke Justice
 * February 23, 2016
 *
 * Creates a random battle deck for the iOS and Android game Clash Royale
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;

bool newElt(int arr[], int size, int elt);
void printDeck(int deck[], int deckSize, const string cardList[]);

int main() {
	const int NUM_CARDS = 42;
	const int DECK_SIZE = 8;
	const string CARD_LIST[NUM_CARDS] = {"Arrows", "Bomber", "Archers", "Knight",
																			 "Fireball", "Mini P.E.K.K.A", 
																			 "Musketeer", "Giant", "Prince", 
																			 "Baby Dragon", "Skeleton Army", "Witch",
																			 "Spear Goblins", "Goblins", 
																			 "Goblin Hut", "Valkyrie", "Lightning",
																			 "Goblin Barrel", "Skeletons", "Minions",
																			 "Tombstone", "Bomb Tower", 
																			 "Giant Skeleton", "Balloon", "Cannon",
																			 "Barbarians", "Rocket", "Barbarian Hut",
																			 "Rage", "X-Bow", "Tesla", 
																			 "Minion Horde", "Inferno Tower",
																			 "Hog Rider", "Freeze", "P.E.K.K.A",
																			 "Zap", "Wizard", "Mirror", "Mortar",
																			 "Elixir Collector", "Golem"};
	int randDeck[DECK_SIZE] = { -1, -1, -1, -1, -1, -1, -1, -1 };
	int randCard;
	bool newRandCard;
	string end = "";
	srand(time(0));
	
	cout << "Thank you for using the Random Deck Builder\n";
	while (end != "quit") {
		for (int i = 0; i < DECK_SIZE; i++) {
			newRandCard = false;
			while (!newRandCard) {
				randCard = rand() % 42;
				newRandCard = newElt(randDeck, DECK_SIZE, randCard);
			}
			randDeck[i] = randCard;
		}
		cout << "Here is your random deck\n";
		printDeck(randDeck, DECK_SIZE, CARD_LIST);
		cout << "Would you like to generate a new deck? Type \"quit\" to quit\n";
		cin >> end;
	}
	
	return 0;
}

// REQUIRES	size >= 0 and size < the size of arr[]
// EFFECTS	returns true if elt is not in arr[];
//					otherwise returns false
bool newElt(int arr[], int size, int elt) {
	for (int i = 0; i < size; i++) {
		if (elt == arr[i]) {
			return false;
		}
	}
	return true;
}

// REQUIRES	All elements in deck[] are >= 0 and < the size of cardList[];
//					deckSize > 0; cardList[] is not empty
// MODIFIES	cout
// EFFECTS	prints a deck to cout
void printDeck(int deck[], int deckSize, const string cardList[]) {
	cout << "{";
	for (int i = 0; i < deckSize; i++) {
		cout << "\n\t" << cardList[deck[i]];
	}
	cout << "\n}\n";
}