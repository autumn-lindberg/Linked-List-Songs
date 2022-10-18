#pragma once
#include "songList.h"
#include <fstream>
using namespace std;

int main();
bool getData(char * fileName, SongList & sl);
int getInt();
char * getInput();
char menu();
void executeOption(SongList * sl, char option);
float getFloat();
