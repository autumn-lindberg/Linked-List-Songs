#pragma once
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

class Song {
	private:
		char * name;
		char * artist;
		float length;
		int likes;
	public:
		// default constructor
		Song();
		// parameterized constructor
		Song(char * name, char * artist, float length, int likes);
		// copy constructor
		Song(const Song & src);
		// destructor
		~Song();
		// copy assignment operator
		Song & operator = (const Song & src);
    // overloaded output operator
    friend ostream & operator << (ostream & out, const Song & src);
		// display song
		void display() const;
		// getters
		char * getName() const;
		char * getArtist() const;
		float getLength() const;
		int getLikes() const;
		// setters
		void setName(char * newName);
		void setArtist(char * newArtist);
		void setLength(float newLength);
		void setLikes(int newLikes);
};

