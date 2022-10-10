#include "song.h"
using namespace std;

// default constructor
Song::Song() {
	this->name = nullptr;
	this->artist = nullptr;
	this->length = 0.0;
	this->likes = 0;
}
// aslo works like this
// Song::Song():name(nullptr), artist(nullptr), length(0), likes(0){}

// parameterized constructor
Song::Song(char * name, char * artist, float length, int likes) {
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->artist = new char[strlen(artist) + 1];
	strcpy(this->artist, artist);
	this->length = length;
	this->likes = likes;
}
// copy constructor
Song::Song(const Song & src) {
	this->name = new char[strlen(src.name) + 1];
	strcpy(this->name, src.name);
	this->artist = new char[strlen(src.artist) + 1];
	strcpy(this->artist, src.artist);
	this->length = src.length;
	this->likes = src.likes;
}
// destructor
Song::~Song() {
	if (this->name != nullptr) {
		delete [] this->name;
		this->name = nullptr;
	}
	if (this->artist != nullptr) {
		delete [] this->artist;
		artist = nullptr;
	}
	this->length = 0;
	this->likes = 0;
}
// copy assignment operator
Song & Song::operator = (const Song & src) {
  	if (this != &src) {
    if (this->name != nullptr) {
  		delete [] this->name;
  		this->name = nullptr;
  	}
  	if (this->artist != nullptr) {
  		delete [] this->artist;
  		artist = nullptr;
  	}
		this->name = new char[strlen(src.name) + 1];
		strcpy(this->name, src.name);
		this->artist = new char[strlen(src.artist) + 1];
		strcpy(this->artist, src.artist);
		this->length = src.length;
		this->likes = src.likes;
	}
	return *this;
}
// overloaded output operator
ostream & operator << (ostream & out, const Song & src) {
  src.display();
  return out;
}
// display song
void Song::display() const {
	cout << left;
	cout << setw(30) << this->name;
	cout << setw(20) << this->artist;
	cout << setw(8) << this->length;
	cout << setw(10) << this->likes << endl;
}
// getters
char * Song::getName() const {
	char * nameCopy = nullptr;
	if (this->name == nullptr) {
		return nullptr;
	}
	else {
		nameCopy = new char[strlen(this->name) + 1];
		strcpy(nameCopy, this->name);
		return nameCopy;
	}
}
char * Song::getArtist() const {
	char * artistCopy = nullptr;
	if (this->name == nullptr) {
		return nullptr;
	}
	else {
		artistCopy = new char[strlen(this->artist) + 1];
		strcpy(artistCopy, this->artist);
		return artistCopy;
	}
}
float Song::getLength() const {
	return this->length;
}
int Song::getLikes() const {
	return this->likes;
}
// setters
void Song::setName(char * newName) {
	if (this->name != nullptr) {
		delete [] this->name;
		this->name = nullptr;
	}
	if (newName != nullptr) {
		this->name = new char[strlen(newName) + 1];
		strcpy(this->name, newName);
	}
}
void Song::setArtist(char * newArtist) {
	if (this->artist != nullptr) {
		delete [] this->artist;
		this->artist = nullptr;
	}
	if (newArtist != nullptr) {
		this->artist = new char[strlen(newArtist) + 1];
		strcpy(this->artist, newArtist);
	}
	
}
void Song::setLength(float newLength) {
	this->length = newLength;
}
void Song::setLikes(int newLikes) {
	this->likes = newLikes;
}
