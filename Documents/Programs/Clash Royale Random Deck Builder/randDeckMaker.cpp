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

int getIndex(const string arr[], int size, string card);
bool inArray(int arr[], int size, int card);
void printDeck(int deck[], int deckSize, const string cardList[]);

int main() {
  const int NUM_CARDS = 42;
  const int DECK_SIZE = 8;
  const int MAX_BAN_SIZE = NUM_CARDS - DECK_SIZE;
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
  int randDeck[DECK_SIZE];
  int bannedCards[NUM_CARDS];
  int numBans;
  int randCard;
  int banID;
  bool newRandCard;
  bool isBannedCard;
  bool newBan;
  string quit = "";
  string ban;
  srand(time(0));
  
  // Controls the removal of cards from the total pool
  cout << "Thank you for using the Random Deck Builder\n";
  while (quit != "quit") {
    ban = "";
    numBans = 0;
    while (ban != "done" && numBans < MAX_BAN_SIZE) {
      cout << "\nEnter the name of a card to remove from the random pool.\n";
      cout << "Type \"done\" to finish your removals and generate a deck.\n";
      getline(cin, ban);
      banID = getIndex(CARD_LIST, NUM_CARDS, ban);
      newBan = !inArray(bannedCards, numBans, banID);
      if (ban != "done") {
        if (banID < 0) {
          cout << ban << " is not a valid card. Type the name exactly as it ";
          cout << "appears on the in-game card.\n";
        }
        else if (banID >= 0 && newBan) {
          bannedCards[numBans] = banID;
          numBans++;
          cout << ban << " was successfully removed.\n";
          if (numBans >= MAX_BAN_SIZE) {
            cout << "Max ban size reached.\n";
          }
        }
        else {
          cout << "Card was previously removed from the pool.\n";
        }
      }
    }
    
    // Generates the random deck
    for (int i = 0; i < DECK_SIZE; i++) {
      newRandCard = false;
      isBannedCard = true;
      while (!newRandCard || isBannedCard) {
        randCard = rand() % 42;
        newRandCard = !inArray(randDeck, DECK_SIZE, randCard);
        isBannedCard = inArray(bannedCards, numBans, randCard);
      }
      randDeck[i] = randCard;
    }
    
    // Controls the loop of the program
    cout << "Here is your random deck.\n";
    printDeck(randDeck, DECK_SIZE, CARD_LIST);
    cout << "Would you like to generate a new deck? Type \"quit\" to quit.\n";
    getline(cin, quit);
  }
  
  return 0;
}

// REQUIRES size >= 0 and size < the size of arr[]; arr[] is not empty;
//          card is not null
// EFFECTS  returns the first index of arr[] if card appears within arr[]
//          otherwise, returns -1
int getIndex(const string arr[], int size, string card) {
  for (int i = 0; i < size; i++) {
    if (card == arr[i]) {
      return i;
    }
  }
  return -1;
}

// REQUIRES size >= 0 and size < the size of arr[]; arr[] is not empty
// EFFECTS  returns true if card is in arr[];
//          otherwise, returns false
bool inArray(int arr[], int size, int card) {
  for (int i = 0; i < size; i++) {
    if (card == arr[i]) {
      return true;
    }
  }
  return false;
}

// REQUIRES All elements in deck[] are >= 0 and < the size of cardList[];
//          deckSize > 0; cardList[] is not empty
// MODIFIES cout
// EFFECTS  prints a deck to cout
void printDeck(int deck[], int deckSize, const string cardList[]) {
  cout << "{";
  for (int i = 0; i < deckSize; i++) {
    cout << "\n\t" << cardList[deck[i]];
  }
  cout << "\n}\n";
}