#include <iostream>
#include <string>
#include <cmath>
#include <unistd.h>
#include "Map.h"
#include "MapCell.h"
using namespace std;

#define NORMAL  	"\x1B[0m"
#define RED  			"\x1B[31m"
#define GREEN  		"\x1B[32m"
#define YELLOW  	"\x1B[33m"
#define BLUE  		"\x1B[34m"
#define MAGENTA  	"\x1B[35m"
#define CYAN  		"\x1B[36m"
#define WHITE  		"\x1B[37m"

// Note - terminal is not monowidth
#define WAVE			"\u034C"
#define SOLID			"\u2588"

const int DEFAULT_ROWS 		= 20;
const int DEFAULT_COLUMNS = 20;

const int DEFAULT_LAND_BLOCK_FACTOR = 1.00;

// Prototypes
void processCommandLineArgs(int argc, char ** argv);
Map generateMap();
void floodTheMap(Map & map);
void generateLandMasses(Map & map);
void generateLandBlock(Map & map);

// Global variables
bool debugging = false;
int rows = DEFAULT_ROWS;
int columns = DEFAULT_COLUMNS;
double landBlockFactor = DEFAULT_LAND_BLOCK_FACTOR;

int main(int argc, char * argv[]) {
	
	// Get rows, columns, and debugging state from args
	processCommandLineArgs(argc, argv);

	Map map = generateMap();

	map.printMap();

	// Revert terminal text color to normal state
	printf(NORMAL "\n");

	return 0;
}

/**
 * Go through command line args and set global variables accordingly
 * {int} argc
 * {char * []} argv
 */
void processCommandLineArgs(int argc, char * argv[]) {

  int c;
	opterr = 0;

  while ((c = getopt (argc, argv, "r:c:b:d")) != -1) {
    switch (c) {
      case 'r':
        rows = atoi(optarg);
        break;
      case 'c':
        columns = atoi(optarg);
        break;
      case 'b':
      	landBlockFactor = atof(optarg);
      	break;
      case 'd':
        debugging = true;
        break;
      case '?':
        if (optopt == 'r' || optopt == 'c' || optopt == 'b') {
          printf("Option -%c requires an argument.\n", optopt);
        } else if(optopt == 'd') {
        	printf("Option -%c does not accept an argument.\n", optopt);
        } else if (isprint (optopt)) {
          printf("Unknown option `-%c'.\n", optopt);
        } else {
          printf("Unknown option character `\\x%x'.\n", optopt);
        }
        break;
      default:
        abort ();
    }
  }
}

/**
 * Calls the individual map generation component methods
 */
Map generateMap() {

	if(debugging) {
		cout << "Generating map..." << endl;
	}

	Map map = Map(rows, columns);

	floodTheMap(map);
	generateLandMasses(map);

	return map;
}

/**
 * Initializes each cell in the map to water
 * {Map &} map
 */
void floodTheMap(Map & map) {

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < columns; j++) {
			map.getMapCells()[i][j] = MapCell(SOLID, BLUE);
		}
	}
}

/**
 * Randomly generates blocks of land and places them on the map
 * {Map &} map
 */
void generateLandMasses(Map & map) {

	// Determine how many blocks of land to generate -- for now using square root of max(rows, columns)
	// Maybe add some factor in here that the user can set at some point?
	int maxDimension = fmax(rows, columns);
	int randomMax = sqrt(maxDimension);

	// Seeding the randomizer
	srand(time(NULL));
	int blocks = (rand() % randomMax) + 1;

	// Adjust the number of blocks by the inverse of the landBlockFactor
	blocks *= (1 / landBlockFactor);

	if(debugging) {
		printf("Generating %i blocks:\n", blocks);
	}

	// Create the blocks
	for(int i = 0; i < blocks; i++) {
		generateLandBlock(map);
	}
}

/**
 * Generates a land block of random size and location
 * {Map &} map
 */
void generateLandBlock(Map & map) {

	// Get block size -- using rand with range of [1, rows/columns]
	int blockHeight = (rand() % ((int)(rows * landBlockFactor))) + 1;
	int blockWidth = (rand() % ((int)(columns * landBlockFactor))) + 1;

	// Get block starting point -- this will be top left corner of the block
	int maximumX = columns - blockWidth;
	int maximumY = rows - blockHeight;

	int blockX = rand() % (maximumX + 1);
	int blockY = rand() % (maximumY + 1);

	if(debugging) {
		printf("Block with dimensions %ix%i created at (%i, %i)\n", blockWidth, blockHeight, blockX, blockY);
	}

	for(int x = blockX; x < (blockX + blockWidth); x++) {
		for(int y = blockY; y < (blockY + blockHeight); y++) {
			map.getMapCells()[y][x].setCellColor(GREEN);
		}
	}
}