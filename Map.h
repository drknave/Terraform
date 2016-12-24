#include "MapCell.h"
using namespace std;

#ifndef MAP_H
#define MAP_H

class Map {

private:
	MapCell ** mapCells;
	int mapRows;
	int mapColumns;

public:
	Map(int rows, int columns);
	~Map();
	MapCell ** getMapCells();
	int getMapRows();
	int getMapColumns();
	void printMap();
};

Map::Map(int rows, int columns) {

	mapCells = new MapCell * [rows];

	for(int i = 0; i < rows; i++) {
		mapCells[i] = new MapCell[columns];
	}

	mapRows = rows;
	mapColumns = columns;
}

Map::~Map() {

	for(int i = 0; i < mapRows; i++) {
		delete [] mapCells[i];
	}

	delete [] mapCells;

	mapCells = 0;
	mapRows = 0;
	mapColumns = 0;
}

MapCell ** Map::getMapCells() {
	return mapCells;
}

int Map::getMapRows() {
	return mapRows;
}

int Map::getMapColumns() {
	return mapColumns;
}

void Map::printMap() {
	
	// How can I use the int returned from printCell?
	for(int i = 0; i < mapRows; i++) {
		for(int j = 0; j < mapColumns; j++) {
			mapCells[i][j].printCell();
		}

		printf("\n");
	}
}

#endif