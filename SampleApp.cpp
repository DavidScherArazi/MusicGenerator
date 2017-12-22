/*
	This is part of CFugue, a C++ Runtime for MIDI Score Programming
	Copyright (C) 2009 Gopalakrishna Palem

	For links to further information, or to contact the author,
	see <http://cfugue.sourceforge.net/>.
*/

// SampleApp.cpp
//
// Demonstrates the usage of CFugue as a Statically Linked Library
//
// CFugue is under active development.
// Please refer to documentation and latest releases at: http://cfugue.sourceforge.net/

#include "Song.h"
#include "stdafx.h"
#include "stdlib.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <cctype>

#include "CFugueLib.h"

void playPrecalculatedSong();
int chooseScaleMsg();
int mainMenu();
void makeSongWithParams();
int getIntRepOfKey(std::string key);

int main(int argc, char* argv[])
{
	srand( (unsigned) time(0));
	int choice = 1;
	std::cout << "\t\t\tWelcome to Music Generator!\n" << "\t   By Jeff Burns, David Scher-Arazi, and Alyssa Schubert" << std::endl;
	choice = mainMenu();
	while (choice != 0) {
		switch (choice) {
			case 1:
				makeSongWithParams(); //generate random song with params
				break;
			case 2:
				playPrecalculatedSong(); //use already generated matrix
				break;
			default: 
				break; //do nothing
		}
		std::cout << "\n... done playing song! Make another selection: ";
		choice = mainMenu();
	}
		
	return 0;
}

int chooseScaleMsg() {
	int choice;

	std::cout << "\nChoose a scale!" << std::endl;
	std::cout << "[1] Minor Penatonic\n" << "[2] Major\n" << "[3] Natural Minor\n" << "Please enter choice: ";
	std::cin >> choice;

	return choice;
}

int mainMenu() {
	int choice;
	std::cout << "\nMain Menu" << std::endl;
	std::cout << "\n[0] exit\n[1] Generate song with built-in paramters\n[2] Play song using another song's note distribution" << std::endl;
	std::cout << "Please enter choice: ";
	std::cin >> choice;
	return choice;
}

void makeSongWithParams() {
	int scaleChoice = chooseScaleMsg();
	int choice;
	int instruments;
	std::vector<int> instList;
	std::cout << "Please choose number of instruments (max 10): ";
	std::cin >> instruments;

	std::cout << "Select " << instruments << " out of the following list of instruments (separate the numbers by spaces):\n";
	std::cout << "[0] Piano\n[1] Guitar\n[2] Drums\n[3] Trumpet\n[4] Cello\n[5] Flute\n[6] Bassoon\n[7] Ocarina\n[8] Tuba\n[9] Violin" << std::endl;
	for(int i = 0; i < instruments; i++) {
		std::cin >> choice;
		switch (choice) {
			case 0:
				instList.push_back(0);
				break;
			case 1:
				instList.push_back(24);
				break;
			case 2:
				instList.push_back(114);
				break;
			case 3:
				instList.push_back(56);
				break;
			case 4:
				instList.push_back(42);
				break;
			case 5:
				instList.push_back(73);
				break;
			case 6:
				instList.push_back(70);
				break;
			case 7:
				instList.push_back(79);
				break;
			case 8:
				instList.push_back(58);
				break;
			case 9:
				instList.push_back(40);
				break;
			default:
				instList.push_back(52);
		}

	}
	Scale scale;

	switch (scaleChoice) {
	case 1:
		scale = MINPEN;
		break;
	case 2:
		scale = MAJ;
		break;
	case 3:
		scale = NATMIN;
		break;
	default:
		scale = MINPEN;
	}

	std::string key;
	std::cout << "\nFinally, choose the key in the form of [Letter][Sharp (optional)][Octave (3 to 5)]: ";
	std::cin >> key;
	Song song(scale, getIntRepOfKey(key), instList);
	song.play();
}

int getIntRepOfKey(std::string key) {
	int result;
	switch (key[0]) {
		case 'C':
			result = 0;
			break;
		case 'D':
			result = 2;
			break;
		case 'E':
			result = 4;
			break;
		case 'F':
			result = 5;
			break;
		case 'G':
			result = 7;
			break;
		case 'A':
			result = 9;
			break;
		case 'B':
			result = 11;
			break;
		default:
			result = 0;
	}
	if (key[1] == '#') {
		result += 1;
		if (key[2] != '-') {
			result = result + (12 * (key[2] - '0'));
		}
	}
	else if (isdigit(key[1])) {
		result = result + (12 * (key[1] - '0'));
	}

	return result;
}

void playPrecalculatedSong() {
	Song song;
	song.play();
}