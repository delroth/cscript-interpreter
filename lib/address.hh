#ifndef __ADDRESS_HH_
# define __ADDRESS_HH_

# include "cscript.hh"

# include <cstdint>

namespace cscript { namespace address {

/**
 * Addresses are encoded as an uint32 as all the other values. There is a bit
 * of memory mapping done so that stack and data addresses can share the same
 * address space.
 *
 * The current encoding method is the following :
 * - Data addresses are encoded as 0x80000000 | offset
 * - Stack addresses are encoded as 0x40000000 | (thread_id << 16) | offset
 */

const uint32_t DATA_FLAG = 0x80000000;
const uint32_t STACK_FLAG = 0x40000000;
const uint32_t EXTERNAL_FLAG = 0xC0000000;

const uint32_t DATA_OFF_MASK = 0x1FFFFFFF;
const uint32_t DATA_OFF_SHIFT = 0;

const uint32_t STACK_THREAD_MASK = 0x00FF0000;
const uint32_t STACK_THREAD_SHIFT = 16;
const uint32_t STACK_OFF_MASK = 0x0000FFFF;
const uint32_t STACK_OFF_SHIFT = 0;

const uint32_t EXTERNAL_ID_MASK = 0x3FF00000;
const uint32_t EXTERNAL_ID_SHIFT = 20;
const uint32_t EXTERNAL_OFF_MASK = 0x000FFFFF;
const uint32_t EXTERNAL_OFF_SHIFT = 0;

inline uint32_t make_data_addr(uint32_t offset)
{
    return DATA_FLAG | ((offset << DATA_OFF_SHIFT) & DATA_OFF_MASK);
}

inline uint32_t make_stack_addr(uint16_t thread_id, uint32_t offset)
{
    uint32_t addr = STACK_FLAG;
    addr |= ((thread_id << STACK_THREAD_SHIFT) & STACK_THREAD_MASK);
    addr |= ((offset << STACK_OFF_SHIFT) & STACK_OFF_MASK);
    return addr;
}

inline uint32_t make_external_addr(uint16_t id, uint16_t offset)
{
    uint32_t addr = EXTERNAL_FLAG;
    addr |= ((id << EXTERNAL_ID_SHIFT) & EXTERNAL_ID_MASK);
    addr |= ((offset << EXTERNAL_OFF_SHIFT) & EXTERNAL_OFF_MASK);
    return addr;
}

/**
 * Get a pointer to the memory zone referenced by the address.
 */
char* get_ptr(cscript& script, uint32_t address);
const char* get_ptr(const cscript& script, uint32_t address);

/**
 * Reads an uint32_t at the specified address. Correctly handles endianness
 * when reading in the data section.
 */
uint32_t uword_at(cscript& script, uint32_t address);

/**
 * Offset an address by a certain amount in bytes.
 * Correctly handles the fact that stack addresses are in words, not bytes.
 */
uint32_t offset(uint32_t address, int32_t off);

}}

#endif
