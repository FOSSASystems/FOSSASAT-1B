#ifndef DEBUGGING_UTILITIES_H_INCLUDED
#define DEBUGGING_UTILITIES_H_INCLUDED

#include "FossaSat1B.h"

/**
 * @file debugging_utilities.h 
 * 
 */

/**
 * @defgroup debugging_h_defines Debugging Utility
 * 
 * @{
 */

// uncomment to enable debug output
// RadioLib debug can be enabled in RadioLib/src/TypeDef.h
#define FOSSASAT_DEBUG
//#define FOSSASAT_VERBOSE

#define FOSSASAT_DEBUG_PORT   Serial
#define FOSSASAT_DEBUG_SPEED  115200

#ifdef FOSSASAT_DEBUG
  #define FOSSASAT_DEBUG_BEGIN(...) { FOSSASAT_DEBUG_PORT.begin(__VA_ARGS__); }
  #define FOSSASAT_DEBUG_PRINT(...) { FOSSASAT_DEBUG_PORT.print(__VA_ARGS__); }
  #define FOSSASAT_DEBUG_PRINTLN(...) { FOSSASAT_DEBUG_PORT.println(__VA_ARGS__); }
  #define FOSSASAT_DEBUG_WRITE(...) { FOSSASAT_DEBUG_PORT.write(__VA_ARGS__); }
  #define FOSSASAT_DEBUG_PRINT_BUFF(BUFF, LEN) { \
    for(size_t i = 0; i < LEN; i++) { \
      FOSSASAT_DEBUG_PORT.print(F("0x")); \
      FOSSASAT_DEBUG_PORT.print(BUFF[i], HEX); \
      FOSSASAT_DEBUG_PORT.print('\t'); \
      FOSSASAT_DEBUG_PORT.write(BUFF[i]); \
      FOSSASAT_DEBUG_PORT.println(); \
    } }
  #define FOSSASAT_DEBUG_DELAY(MS) { delay(MS); }
#else
  #define FOSSASAT_DEBUG_BEGIN(...) {}
  #define FOSSASAT_DEBUG_PRINT(...) {}
  #define FOSSASAT_DEBUG_PRINTLN(...) {}
  #define FOSSASAT_DEBUG_WRITE(...) {}
  #define FOSSASAT_DEBUG_PRINT_BUFF(BUFF, LEN) {}
  #define FOSSASAT_DEBUG_DELAY(MS) {}
#endif

#ifdef FOSSASAT_VERBOSE
  #define FOSSASAT_VERBOSE_PRINT(...) { FOSSASAT_DEBUG_PORT.print(__VA_ARGS__); }
  #define FOSSASAT_VERBOSE_PRINTLN(...) { FOSSASAT_DEBUG_PORT.println(__VA_ARGS__); }
#else
  #define FOSSASAT_VERBOSE_PRINT(...) {}
  #define FOSSASAT_VERBOSE_PRINTLN(...) {}
#endif

/**
 * @}
 * 
 */
#endif
