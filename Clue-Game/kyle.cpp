
//
//  main.cpp
//  Clue-Game
//
//  Created by Julia on 7/16/16.
//  Copyright Â© 2016 Julia. All rights reserved.
//
/*------------------------------------------------------------------------------------------------------------------------
 
 Ok, so I changed a few things. I realized that the deck as a vector would make it pretty hard to remove the confidential (answer) cards from the deck so that they can be shuffled and distributed. I created three separate decks (Weapons, Suspects, and Locations), shuffled them individually and chose a card from each. I then added them to the end of the vector cards which appears in the Deck class. There may have been a better way to do this, I'm not sure, but it works. Now the deck picks the confidential (answer cards first then shuffles the rest of the deck for distribution. However, the vectors confidential and cards are both outside of their classes. I didn't think this would be a problem, but I'm fairly new to C/C++ so you'll have to let me know.
 
 ------------------------------------------------------------------------------------------------------------------------*/
/*
 
 This is what I did: 
    - I noticed that the confidential envelope was always returning the same three cards, and the Random shuffle was not actually randomly shuffling, so I fixed it and everything is now randomly shuffling, so everytime we don't recieve the same cards
        and ignore the warning signs
    - I created a suggestion and accusation Class, and starting working on that. Got a little confused with some of the stuff and I wrote what I was confused on in those respected classes
    - I also started working on Game Play, trying to get it working like we want it too
 -Kyle Erchinger
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
# include <ctime>
#include <cstdlib>
#include <random>

using namespace std;

class Room {
public:
    string name;
    string abbreviation;
    vector<Room*> connectedRooms;
    void addConnectedRoom(Room* room) {
        connectedRooms.push_back(room);
    };
    Room(string roomName, string roomAbbreviation) {
        name = roomName;
        abbreviation = roomAbbreviation;
    };
    void debugPrint() {
        cout << "This room is the " << name << endl;
        cout << "It is connected to the ";
        for (int i = 0; i < connectedRooms.size(); i++) {
            cout << connectedRooms[i]->name << ", ";
        }
        cout << endl;
    };
    
};

Room* findRoomWithAbbreviation(string abbreviation, vector<Room*> rooms) {
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i]->abbreviation.compare(abbreviation) == 0){
            return rooms[i];
        }
    }
    return NULL;
}


class Board {
public:
    vector<Room*> rooms;
    void addRoom(Room* roomToAdd) {
        rooms.push_back(roomToAdd);
    };
    void debugPrint() {
        for (int i = 0; i < rooms.size(); i++) {
            rooms[i]->debugPrint();
        }
    };
    Board() {
        Room* kitchen = new Room("Kitchen", "K");
        Room* ballroom = new Room("Ballroom", "B");
        Room* conservatory = new Room("Conservatory", "C");
        Room* billiardRoom = new Room("Billiard Room", "BR");
        Room* library = new Room("Library", "L");
        Room* study = new Room("Study", "S");
        Room* hall = new Room("Hall", "H");
        Room* lounge = new Room("Lounge", "LO");
        Room* diningRoom = new Room("Dining Room", "D");
        addRoom(kitchen);
        addRoom(ballroom);
        addRoom(conservatory);
        addRoom(billiardRoom);
        addRoom(library);
        addRoom(study);
        addRoom(hall);
        addRoom(lounge);
        addRoom(diningRoom);
        kitchen->addConnectedRoom(ballroom);
        kitchen->addConnectedRoom(diningRoom);
        kitchen->addConnectedRoom(study);
        ballroom->addConnectedRoom(kitchen);
        ballroom->addConnectedRoom(conservatory);
        conservatory->addConnectedRoom(ballroom);
        conservatory->addConnectedRoom(billiardRoom);
        conservatory->addConnectedRoom(lounge);
        billiardRoom->addConnectedRoom(conservatory);
        billiardRoom->addConnectedRoom(library);
        library->addConnectedRoom(billiardRoom);
        library->addConnectedRoom(study);
        study->addConnectedRoom(library);
        study->addConnectedRoom(hall);
        study->addConnectedRoom(kitchen);
        hall->addConnectedRoom(study);
        hall->addConnectedRoom(lounge);
        lounge->addConnectedRoom(hall);
        lounge->addConnectedRoom(diningRoom);
        lounge->addConnectedRoom(conservatory);
        diningRoom->addConnectedRoom(lounge);
        diningRoom->addConnectedRoom(kitchen);
    }
    
};

class Player {
public:
    string name;
    Room* playerLocation;
    Player(string playerName) {
        name = playerName;
    }
    void move(){
        string newLocation;
        cout << "You are currently in the " << playerLocation->name << "." << endl;
        cout << "From here, you can move to the ";
        for (int i = 0; i < playerLocation->connectedRooms.size(); i++) {
            cout << playerLocation->connectedRooms[i]->name << " (" << playerLocation->connectedRooms[i]->abbreviation << "), " << endl;
        }
        cout << "Please enter the abbreviation of the room you would like to move to." << endl;
        cin >> newLocation;
        Room* newRoom = findRoomWithAbbreviation(newLocation, playerLocation->connectedRooms);
        if (newRoom != NULL) {
            playerLocation = newRoom;
        }
        
    }
};

enum CardType {
    Weapon,
    Suspect,
    Location
};

#define NUM_WEAPONS 6

enum WeaponType {
    Candlestick,
    Knife,
    LeadPipe,
    Revolver,
    Rope,
    Wrench
};

string getWeaponTypeString(WeaponType type) {
    switch (type) {
        case Candlestick:
            return "Candlestick";
        case Knife:
            return "Knife";
        case LeadPipe:
            return "Lead Pipe";
        case Revolver:
            return "Revolver";
        case Rope:
            return "Rope";
        case Wrench:
            return "Wrench";
    }
}

#define NUM_SUSPECTS 6

enum SuspectType {
    Scarlet,
    Mustard,
    White,
    Green,
    Peacock,
    Plum
};

string getSuspectTypeString(SuspectType type) {
    switch (type) {
        case Scarlet:
            return "Miss Scarlet";
        case Mustard:
            return "Colonel Mustard";
        case White:
            return "Mrs. White";
        case Green:
            return "Mr. Green";
        case Peacock:
            return "Mrs. Peacock";
        case Plum:
            return "Professor Plum";
    }
}

#define NUM_LOCATIONS 9

enum LocationType {
    Kitchen,
    Ballroom,
    Conservatory,
    BilliardRoom,
    Library,
    Study,
    Hall,
    Lounge,
    DiningRoom
};

string getLocationTypeString(LocationType type) {
    switch (type) {
        case Kitchen:
            return "Kitchen";
        case Ballroom:
            return "Ballroom";
        case Conservatory:
            return "Conservatory";
        case BilliardRoom:
            return "Billiard Room";
        case Library:
            return "Library";
        case Study:
            return "Study";
        case Hall:
            return "Hall";
        case Lounge:
            return "Lounge";
        case DiningRoom:
            return "Dining Room";
    }
};

class Card {
public:
    CardType type;
    Card(CardType t) {
        type = t;
    }
};

class WeaponCard : public Card {
public:
    WeaponType weaponType;
    WeaponCard(WeaponType type) : Card(Weapon) {
        weaponType = type;
    }
};

class SuspectCard : public Card {
public:
    SuspectType suspectType;
    SuspectCard(SuspectType type) : Card(Suspect) {
        suspectType = type;
    }
};

class LocationCard : public Card {
public:
    LocationType locationType;
    LocationCard(LocationType type) : Card(Location) {
        locationType = type;
    }
};


//__________________________________________________-____________-_-------------------------------------------------------------------------------------------------------
// I beleive this does not need to be changed
vector<Card*> confidential;

class Envelope{
public:
    void printConfidential(){
        for (int i = 0; i < confidential.size(); i++) {
            Card* card = confidential[i];
            if (card->type == Weapon) {
                WeaponCard* weapon = (WeaponCard*)card;
                cout <<"We have a weapon card: " << getWeaponTypeString(weapon->weaponType)  << endl;
            }else if(card->type == Suspect) {
                SuspectCard* suspect = (SuspectCard*)card;
                cout << "We have a suspect card: " << getSuspectTypeString(suspect->suspectType)  << endl;
            }else if (card->type == Location){
                LocationCard* location = (LocationCard*)card;
                cout << "We have a location card: " << getLocationTypeString(location->locationType)  << endl;
            }
        }
    }
};
//__________________________________________________-____________-_-------------------------------------------------------------------------------------------------------

vector<Card*> cards;

class WeaponDeck {
public:
    
    vector<Card*> weaponCards;
    WeaponDeck() {
        for(int i = 0; i<NUM_WEAPONS; i++){
            WeaponCard* card = new WeaponCard((WeaponType)i);
            weaponCards.push_back(card);
        }
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(weaponCards.begin(), weaponCards.end(), default_random_engine(seed));
        //random_shuffle(weaponCards.begin(), weaponCards.end()); this was not working!
        confidential.push_back(weaponCards.back());
        weaponCards.pop_back();
        for(int i = 0; i<weaponCards.size(); i++){
            cards.push_back(weaponCards[i]);
        }
    }
    void printWeaponDeck(){
        for (int i = 0; i < weaponCards.size(); i++) {
            Card* card = weaponCards[i];
            if (card->type == Weapon) {
                WeaponCard* weapon = (WeaponCard*)card;
                cout <<"We have a weapon card: " << getWeaponTypeString(weapon->weaponType)  << endl;
            }
        }
    }
    
};

class SuspectDeck {
public:
    vector<Card*> suspectCards;
    SuspectDeck() {
        for(int i = 0; i<NUM_SUSPECTS; i++){
            SuspectCard* card = new SuspectCard((SuspectType)i);
            suspectCards.push_back(card);
        }
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(suspectCards.begin(), suspectCards.end(), default_random_engine(seed));
        //random_shuffle(suspectCards.begin(), suspectCards.end()); // again it was not working
        confidential.push_back(suspectCards.back());
        suspectCards.pop_back();
        for(int i = 0; i<suspectCards.size(); i++){
            cards.push_back(suspectCards[i]);
        }
    }
    
    void printSuspectDeck(){
        for (int i = 0; i < suspectCards.size(); i++) {
            Card* card = suspectCards[i];
            if (card->type == Suspect) {
                SuspectCard* suspect = (SuspectCard*)card;
                cout <<"We have a suspect card: " << getSuspectTypeString(suspect->suspectType)  << endl;
            }
        }
    }
    
};

class LocationDeck {
public:
    vector<Card*> locationCards;
    LocationDeck() {
        for(int i = 0; i<NUM_LOCATIONS; i++){
            LocationCard* card = new LocationCard((LocationType)i);
            locationCards.push_back(card);
        }
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(locationCards.begin(), locationCards.end(), default_random_engine(seed));
        //random_shuffle(locationCards.begin(), locationCards.end()); // agian wasn't working
        confidential.push_back(locationCards.back());
        locationCards.pop_back();
        for(int i = 0; i<locationCards.size(); i++){
            cards.push_back(locationCards[i]);
        }
    }
    
    void printLocationDeck(){
        for (int i = 0; i < locationCards.size(); i++) {
            Card* card = locationCards[i];
            if (card->type == Location) {
                LocationCard* location = (LocationCard*)card;
                cout <<"We have a location card: " << getLocationTypeString(location->locationType)  << endl;
            }
        }
    }
    
};

// I don;t get why we need this... cause we have 3 seperate decks anyways, so it seems like this combines all the cards, and does that actually happen??
class Deck {
public:
   /* vector<Card*> cards;
     Deck() {
     for (int i = 0; i < NUM_WEAPONS; i++) {
     WeaponCard* card = new WeaponCard((WeaponType)i);
     cards.push_back(card);
     }
     
     for (int i = 0; i < NUM_SUSPECTS; i++) {
     SuspectCard* card = new SuspectCard((SuspectType)i);
     cards.push_back(card);
     }
     
     
     for (int i = 0; i < NUM_LOCATIONS; i++) {
     LocationCard* card = new LocationCard((LocationType)i);
     cards.push_back(card);
     }
     }*/
    void debugPrint() {
        for (int i = 0; i < cards.size(); i++) {
            Card* card = cards[i];
            if (card->type == Weapon) {
                WeaponCard* weapon = (WeaponCard*)card;
                cout <<"We have a weapon card: " << getWeaponTypeString(weapon->weaponType)  << endl;
            }
            else if (card->type == Suspect) {
                SuspectCard* suspect = (SuspectCard*)card;
                cout <<"We have a suspect card: " << getSuspectTypeString(suspect->suspectType)  << endl; // SUSPECT CARD CANT BE MRS SCARLET... and the last two times a Runned the Program the Confidential Envelope contains Mrs. Scarlet as Killer
            }
            else if (card->type == Location) {
                LocationCard* location = (LocationCard*)card;
                cout <<"We have a location card: " << getLocationTypeString(location->locationType)  << endl;
            }
        }
        
    }
    
    
    
    void shuffle(){
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        ::shuffle(cards.begin(), cards.end(), default_random_engine(seed));
        //random_shuffle(cards.begin(), cards.end()); // again was not working
    }
};

class Accusation{
public:
    bool checkAccusationisCorrect(string killer1, string weaponused1, string crimescene1){// order of cards is weapon, suspect, location
        string weaponconfidential;
        string suspectconfidential;
        string locationconfidential;
        for (int q = 0; q <confidential.size(); q++){
            if (confidential[q]->type == Weapon){
                WeaponCard* weapon1 = (WeaponCard*)confidential[q];
                weaponconfidential = getWeaponTypeString(weapon1->weaponType);
            }else if( confidential[q]-> type == Suspect){
                SuspectCard* suspect1 = (SuspectCard*)confidential[q];
                suspectconfidential = getSuspectTypeString(suspect1->suspectType);
            }else if( confidential[q]->type == Location){
                LocationCard* location1 = (LocationCard*)confidential[q];
                locationconfidential = getLocationTypeString(location1->locationType);
            }
        }
       if ((weaponused1 == weaponconfidential) && (killer1 == suspectconfidential)&&(crimescene1==locationconfidential)){ return true;}
        return false;
    }
    
};
// Kind of confused on what to do here, as I don't know what the other cards the players have, don;t know what to do basically
class Suggestion{
public:
    bool CheckSuggestion();
    
};

// Stuff we need in the Pogram:
// way to exit the program
// score card to help player keep track of whether or not he or she is going to win, and need actual game play going
int main(int argc, const char * argv[]) {
    char input;
    char input1;
    string killer;
    string weaponused;
    string crimescene;
    string suspect;
    string suspectedweapon;
    
    Board clueBoard;
    vector<Player*> players;
    string location;
    Player* player = new Player("Miss Scarlet");
    // tell the player what his/her individual cards are
    cout << "Weapon Cards: " << endl;
     WeaponDeck wDeck;
     wDeck.printWeaponDeck();
     
     cout << "Suspect Cards: " << endl;
     SuspectDeck sDeck;
     sDeck.printSuspectDeck();
     
     cout << "Location Cards: " << endl;
     LocationDeck lDeck;
     lDeck.printLocationDeck();
     
     cout << "CONFIDENTIAL ENVELOPE: " << endl;
     Envelope answers;
     answers.printConfidential();
     
     
     cout << "Shuffled Deck: " << endl; // IT SEEMS AS THOUGH THIS IS SHUFFLING ALL THE THE CARDS TOGHETHER, RATHER THAN THE 3 INDIVIDUAL DECKS
     Deck deck;
     deck.shuffle();
     deck.debugPrint();
    
    
    cout << "Miss Scarlet can start in the Lounge (LO) or the Hall (H). Please enter your location." << endl;
    cin >> location;
    Room* startingLocation = findRoomWithAbbreviation(location, clueBoard.rooms);
    player->playerLocation = startingLocation;

      while (1) {
          cout<< "Would you Like to make an Accusation? (y/n)"<<endl;
          cin >> input1;
          if( input1 == 'y'){
              cout<< "The Murderer is: "<<endl;
              cin.ignore();
              getline(cin, killer);
              cout<< "The Weapon the murderer used to Kill is: "<<endl;
              getline(cin, weaponused);
              cout<< "The Room the murderer murdered Mr. Boddy is: "<<endl;
              getline(cin, crimescene);
              Accusation accuser;
              if( accuser.checkAccusationisCorrect(killer, weaponused, crimescene) == true){ cout<<"You WIN!!!"<<endl; break;}
              else{ cout<<" You lose! GAME OVER!!"<<endl; break;}
          };
          
         player->move();
          
          cout<< " Would you like to make a suggestion? (y/n) "<< endl;
          cin>> input;
          if( input == 'y'){
              cout<< "Who is the suspect? "<<endl;
              cin>> suspect;
              cout<< "what is the suspected weapon? "<<endl;
              cin >> suspectedweapon;
              // How can you get what Room the person is in for the suggestion??
              // search cards of eaach CP in order, if one of the cp cards refutes the players suggestion, reveal it to the player, and players turn ends ONLY REVEAL 1 HINT????
              
              //else player may either end turn or make an accusation
          }
          
     }
    
    /*cout << "Weapon Cards: " << endl;
    WeaponDeck wDeck;
    wDeck.printWeaponDeck();
    
    cout << "Suspect Cards: " << endl;
    SuspectDeck sDeck;
    sDeck.printSuspectDeck();
    
    cout << "Location Cards: " << endl;
    LocationDeck lDeck;
    lDeck.printLocationDeck();
    
    cout << "CONFIDENTIAL ENVELOPE: " << endl;
    Envelope answers;
    answers.printConfidential();
    
    
    cout << "Shuffled Deck: " << endl; // IT SEEMS AS THOUGH THIS IS SHUFFLING ALL THE THE CARDS TOGHETHER, RATHER THAN THE 3 INDIVIDUAL DECKS
    Deck deck;
    deck.shuffle();
    deck.debugPrint();
    */
    
    return 0;
}