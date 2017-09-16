#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include <list>


using namespace std;



//
//	COMPONENTS / TYPES / CLASSES
//		DEFINED HERE
//

#define DIE(x) cerr << "Error: " << (x) << endl; exit(1)

// The Mode defines where the card is in game 
enum Mode {HAND,PLAYER_A,PLAYER_B};

enum Direction {TOP, BOTTOM, LEFT, RIGHT};

class Card
{
	public:
	Mode mode;
 
	// ATK:LEFT   DEF:RIGHT   SPD:TOP   PWR:BOTTOM
	int atk, def, spd, pwr;
	string name;
	bool empty = true;

	Card(){} // Empty Constructor

	// Constructor to init with values
	Card(string name, int atk, int def, int spd, int pwr)
	{
		this->name = name;
		this->atk = atk;
		this->def = def;
		this->spd = spd;
		this->pwr = pwr;
		empty = false;
	}

	static vector<Card> ReadCards(string filename="carddb.dat")
	{
		vector<Card> ret = vector<Card>();	
		
		ifstream db(filename.c_str());
		if(!db.is_open())
		{
			DIE("Could not open Card database, exiting");
		}

		string line;
		while( getline(db, line))
		{
			size_t pos = 0;
			string token;
			vector<string> data;			

			while ((pos = line.find(":")) != string::npos)
			{
				token = line.substr(0, pos);
				line.erase(0, pos + 1);
				data.push_back(token);
			}
			data.push_back(line);

			Card c = Card(data[0], stoi(data[1]), stoi(data[2]),
					stoi(data[3]), stoi(data[4]));

			ret.push_back(c);
		}

		return ret;
	}

};

//
//	DEBUG UTILS
//	AND FUNCTIONS
//
std::ostream &operator<<(std::ostream &os, Card const &c)
{ 
	return os << c.name << "[" << c.atk << "," << c.def << "," \
		 << c.spd << "," << c.pwr << "]";
}




// 	MAIN GAME LOGIC
//	DEFINED HERE

#define ROWS 5
#define COLS 5

Card field[COLS][ROWS];

int main(void)
{
	vector<Card> cards = Card::ReadCards();
	return 0;
}
