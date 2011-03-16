#ifndef __TYPE_HH_
# define __TYPE_HH_

# include <cstdint>

namespace cscript { namespace type {

/**
 * The value is an immediate value, i.e. it was not read in memory.
 */
const uint16_t IMMEDIATE = 0x200;

/**
 * The value is a pointer.
 */
const uint16_t POINTER = 0x80;

/**
 * The value is a pointer (again).
 * TODO: Figure out the difference.
 */
const uint16_t POINTER2 = 0x40;
const uint16_t POINTER3 = 0x20;


const uint8_t VOID = 1;
const uint8_t UCHAR = 2;
const uint8_t SCHAR = 3;
const uint8_t UHALF = 4;
const uint8_t SHALF = 5;
const uint8_t UWORD = 6;
const uint8_t SWORD = 7;
const uint8_t FLOAT = 8;
const uint8_t ADDR = 12;

}}

#endif
