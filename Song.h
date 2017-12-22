#pragma once
#include "CFugueLib.h"
#include <vector>
#include <cmath>
#include <string>
#include <iostream>

const double E = 2.7182818;
const double PI = 4 * atan(1.0);
const int SONG_LENGTH = 48;
enum Scale { MAJ, MINPEN, NATMIN };

class Song {
private:
	std::vector<std::vector<double>> matrix;
	std::string song;

public:
	Song(Scale scale, int startingNote, std::vector<int> instruments); //randomly generates from params
	Song(); //select a prepared distribution of notes to generate music from
	void play();

};