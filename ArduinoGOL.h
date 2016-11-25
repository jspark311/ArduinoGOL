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



class ArduinoGOL {
  public:
    ArduinoGOL(uint16_t x, uint16_t y, uint16_t opts = AGOL_OPT_DEFAULTS);
    ~ArduinoGOL();

    /* Overrides from SensorWrapper */
    inline int      sizeX() {   return _SIZE_X;   };
    inline int      sizeY() {   return _SIZE_Y;   };
    inline uint32_t frame() {   return _frame;    };

    int randomize(int seed);
    int next(unsigned int steps);
    inline int next() {   return next(1);   };

    unsigned int getCell(unsigned int x, unsigned int y);

    static int copy(ArduinoGOL* dest, ArduinoGOL* src);
    static int compare(ArduinoGOL* a, ArduinoGOL* b);


  private:
    const uint16_t _SIZE_X;
    const uint16_t _SIZE_Y;
    const uint16_t _OPTS;

    uint32_t _frame = 0;

    int _proc_life();
};

#endif // __ARDUINO_GOL_INCLUDE_H__
