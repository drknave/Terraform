#include <string>
using namespace std;

#ifndef MAPCELL_H
#define MAPCELL_H

class MapCell {

private:
	string utfCharacter;
	string cellColor;

public:
	MapCell();
	MapCell(string ch, string col);
	string getUtfCharacter();
	void setUtfCharacter(string c);
	string getCellColor();
	void setCellColor(string c);
	int printCell();
};

MapCell::MapCell() {
	setUtfCharacter("X");
	setCellColor("\x1B[0m");
}

MapCell::MapCell(string character, string color) {
	setUtfCharacter(character);
	setCellColor(color);
}

string MapCell::getUtfCharacter() {
	return utfCharacter;
}

void MapCell::setUtfCharacter(string character) {
	utfCharacter = character;
}

string MapCell::getCellColor() {
	return cellColor;
}

void MapCell::setCellColor(string color) {
	cellColor = color;
}

int MapCell::printCell() {
	return printf("%s%s ", cellColor.c_str(), utfCharacter.c_str());
}

#endif