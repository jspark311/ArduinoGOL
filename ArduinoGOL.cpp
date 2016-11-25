/*******************************************************************************
* GoL
********************************************************************************
* This implementation of GoL was originally written by user creativename.
* Original commentary is preserved where it is still relevant.
*
* I have mutated the original source to fit this project. I mapped the board onto
*   a toroid. It was a bounded plane.
*
*      --- J. Ian Lindsay
*
*  http://runnable.com/u/creativename
*  http://runnable.com/UwQvQY99xW5AAAAQ/john-conway-s-game-of-life-for-c%2B%2B-nested-for-loops-and-2-dimensional-arrays
*
*  //A very simple C++ implementation of John Conway's Game of Life.
*  //This implementation uses several nested for loops as well as two-dimensional
*  //arrays to create a grid for the cells in the simulation to interact.
*  //The array that is displayed to the user is 50 x 100, but actual size
*  //of the array is 52 x 102.  The reason for this is to make the
*  //calculations easier for the cells on the outermost "frame" of the grid.
*******************************************************************************/

int ArduinoGOL::_copy(uint8_t* dest, uint8_t* src) {
  if ((nullptr != dest) && (nullptr != src)) {
    if (dest->sizeX() == src->sizeX()) {
      if (dest->sizeY() == src->sizeY()) {
        unsigned int s = sizeof(dest);
        for (unsigned int i = 0; i < s; i++) *(dest + i) = *(src + i);
        return 0;
      }
    }
  }
  return -1;
}


//Checks to see if two arrays are exactly the same.
//This is used to end the simulation early, if it
//becomes stable before the 100th generation. This
//occurs fairly often in the Von Neumann neighborhood,
//but almost never in the Moore neighborhood.
int ArduinoGOL::compare(ArduinoGOL* a, ArduinoGOL* b) {
  if ((nullptr != a) && (nullptr != b)) {
    if (a->sizeX() == b->sizeX()) {
      if (a->sizeY() == b->sizeY()) {
        //return 0;
      }
    }
  }
  return -1;
}



//The life function is the most important function in the program.
//It counts the number of cells surrounding the center cell, and
//determines whether it lives, dies, or stays the same.
int ArduinoGOL::_proc_life() {
  //Copies the main array to a temp array so changes can be entered into a grid
  //without effecting the other cells and the calculations being performed on them.
  uint8_t temp[sizeX()][sizeY()];
  copy(temp, _field);
  for(int j = GOL_BOARD_HEIGHT; j < (GOL_BOARD_HEIGHT*2); j++) {
    for(int i = GOL_BOARD_WIDTH; i < (GOL_BOARD_WIDTH*2); i++) {
      if(neighborhood == 'm') {
        //The Moore neighborhood checks all 8 cells surrounding the current cell in the array.
        int count = 0;
        count = array[(j-1)%GOL_BOARD_HEIGHT][i % GOL_BOARD_WIDTH] +
          array[(j-1)%GOL_BOARD_HEIGHT][(i-1) % GOL_BOARD_WIDTH] +
          array[j%GOL_BOARD_HEIGHT][(i-1) % GOL_BOARD_WIDTH] +
          array[(j+1)%GOL_BOARD_HEIGHT][(i-1) % GOL_BOARD_WIDTH] +
          array[(j+1)%GOL_BOARD_HEIGHT][i % GOL_BOARD_WIDTH] +
          array[(j+1)%GOL_BOARD_HEIGHT][(i+1) % GOL_BOARD_WIDTH] +
          array[j%GOL_BOARD_HEIGHT][(i+1) % GOL_BOARD_WIDTH] +
          array[(j-1)%GOL_BOARD_HEIGHT][(i+1) % GOL_BOARD_WIDTH];

        if(count < 2 || count > 3) temp[j%GOL_BOARD_HEIGHT][i % GOL_BOARD_WIDTH] = 0;  //The cell dies.
        else if(count == 2) temp[j%GOL_BOARD_HEIGHT][i % GOL_BOARD_WIDTH] = array[j%GOL_BOARD_HEIGHT][i % GOL_BOARD_WIDTH];  //The cell stays the same.
        else if(count == 3) temp[j%GOL_BOARD_HEIGHT][i % GOL_BOARD_WIDTH] = 1;  //The cell either stays alive, or is "born".
      }

      else if(neighborhood == 'v') {
        //The Von Neumann neighborhood checks only the 4 surrounding cells in the array,
        //(N, S, E, and W).
        int count = 0;
        count = array[(j-1)%GOL_BOARD_HEIGHT][i % GOL_BOARD_WIDTH] +
          array[j%GOL_BOARD_HEIGHT][(i-1) % GOL_BOARD_WIDTH] +
          array[(j+1)%GOL_BOARD_HEIGHT][i % GOL_BOARD_WIDTH] +
          array[j%GOL_BOARD_HEIGHT][(i+1) % GOL_BOARD_WIDTH];

        if(count < 2 || count > 3) temp[j%GOL_BOARD_HEIGHT][i % GOL_BOARD_WIDTH] = 0; //The cell dies.
        else if(count == 2) temp[j%GOL_BOARD_HEIGHT][i % GOL_BOARD_WIDTH] = array[j%GOL_BOARD_HEIGHT][i % GOL_BOARD_WIDTH];    //The cell stays the same.
        else if(count == 3) temp[j%GOL_BOARD_HEIGHT][i % GOL_BOARD_WIDTH] = 1;   //The cell either stays alive, or is "born".
      }
    }
   }
  return 0;
}


//This function prints the 50 x 100 part of the array, since that's the only
//portion of the array that we're really interested in.
uint8_t getCell(unsigned int x, unsigned int y) {
  return _field[x % sizeX()][y % sizeY()];
}


void ArduinoGOL::randomize(int seed) {
  srand(micros());
  for (int j = 1; j < sizeY(); j++) {
    for(int i = 1; i < sizeX(); i++) {
      _field[i][j] = rand() % 2;
    }
  }
  return 0;
}


int ArduinoGOL::next(unsigned int steps) {
  while (0 < steps--) {
    _proc_life();
  }
  return 0;
}
