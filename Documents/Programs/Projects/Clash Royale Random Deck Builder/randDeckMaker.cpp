/* randDeckMaker.cpp
 *
 * Luke Justice
 * February 23, 2016
 *
 * Creates a random battle deck for the iOS and Android game Clash Royale
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int getIndex(const string arr[], int size, string card);
bool inArray(int arr[], int size, int card);
void printDeck(int deck[], int deckSize, const string cardList[]);

int main() {
  const int NUM_CARDS = 54;
  const int DECK_SIZE = 8;
  const int MAX_BAN_SIZE = NUM_CARDS - DECK_SIZE;
  const int NUM_LEGENDARIES = 5;
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
                                       "Elixir Collector", "Golem", "Poison",
                                       "Royal Giant", "Three Musketeers",
                                       "Dark Prince", "Ice Wizard", "Princess",
                                       "Fire Spirits", "Furnace", "Guards",
                                       "Lava Hound", "Miner", "Sparky"
                                      };
  const int LEGENDARY_IDS[NUM_LEGENDARIES] = {getIndex(CARD_LIST, NUM_CARDS, 
                                                       "Ice Wizard"),
                                              getIndex(CARD_LIST, NUM_CARDS, 
                                                       "Princess"),
                                              getIndex(CARD_LIST, NUM_CARDS,
                                                       "Lava Hound"),
                                              getIndex(CARD_LIST, NUM_CARDS,
                                                       "Miner"),
                                              getIndex(CARD_LIST, NUM_CARDS,
                                                       "Sparky")
                                             };
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
        if (ban == "Legendary" || ban == "Legendaries") {
          for (int i = 0; i < NUM_LEGENDARIES; i++) {
            if (!inArray(bannedCards, numBans, LEGENDARY_IDS[i])) {
              bannedCards[numBans] = LEGENDARY_IDS[i];
              numBans++;
            }
          }
          cout << "Legendary cards have been removed from the pool.\n";
        }
        else if (banID < 0) {
          cout << ban << " is not a valid card.\nType the name exactly as it ";
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
          cout << ban << " was previously removed from the pool.\n";
        }
      }
      cout << "\nRemoved Cards:\n";
      printDeck(bannedCards, numBans, CARD_LIST);
    }
    
    // Generates the random deck
    if (numBans == MAX_BAN_SIZE) {
      for (int i = 0; i < DECK_SIZE; i++) {
        if (!inArray(bannedCards, numBans, i)) {
          randDeck[i] = i;
        }
      }
    }
    else {
      for (int i = 0; i < DECK_SIZE; i++) {
        newRandCard = false;
        isBannedCard = true;
        while (!newRandCard || isBannedCard) {
          randCard = rand() % NUM_CARDS;
          newRandCard = !inArray(randDeck, DECK_SIZE, randCard);
          isBannedCard = inArray(bannedCards, numBans, randCard);
        }
        randDeck[i] = randCard;
      }
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