/*
File:   ArduinoGOL.h
Author: J. Ian Lindsay
Date:   2016.11.24

License is attribution-only.
*/

#ifndef __ARDUINO_GOL_INCLUDE_H__
#define __ARDUINO_GOL_INCLUDE_H__


#define AGOL_OPT_TOPO_PLANE    0x0001
#define AGOL_OPT_TOPO_CYL_X    0x0002
#define AGOL_OPT_TOPO_CYL_Y    0x0004
#define AGOL_OPT_TOPO_TOROID   (AGOL_OPT_TOPO_CYL_X | AGOL_OPT_TOPO_CYL_Y)

#define AGOL_OPT_MEM_COMPACT   0x0010
#define AGOL_OPT_MEM_FAST      0x0020

#define AGOL_OPT_DEFAULTS (AGOL_OPT_MEM_FAST | AGOL_OPT_TOPO_TOROID)


template <uint16_t SIZE_X, uint16_t SIZE_Y> class ArduinoGOL {
  public:
    ArduinoGOL(uint16_t opts = AGOL_OPT_DEFAULTS);
    ~ArduinoGOL();

    /* Overrides from SensorWrapper */
    inline int      sizeX() {   return SIZE_X;    };
    inline int      sizeY() {   return SIZE_Y;    };
    inline uint32_t frame() {   return _frame;    };

    int randomize(int seed);
    int next(unsigned int steps);
    inline int next() {   return next(1);   };

    uint8_t getCell(unsigned int x, unsigned int y);

    static int compare(ArduinoGOL* a, ArduinoGOL* b);


  private:
    uint32_t _frame = 0;
    uint16_t _OPTS;
    uint8_t  _field[SIZE_X][SIZE_Y];
    char neighborhood = 'm';

    int _proc_life();


    static int _copy(uint8_t* dest, uint8_t* src);
};

#endif // __ARDUINO_GOL_INCLUDE_H__
