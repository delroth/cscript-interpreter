#include "cscript.hh"
#include "endian.hh"

#include <cstring>

namespace {

uint32_t read_beword_at(const char* buffer, size_t where)
{
    uint32_t* ptr = (uint32_t*)(buffer + where);
    return cscript::endian::from_big(*ptr);
}

}

namespace cscript {

void cscript::parse_bytecode(const char* buffer, size_t size)
{
    if (size < 0x20)
        throw bad_script_exception("file is too small");

    if (memcmp(buffer, "TSS\0", 4))
        throw bad_script_exception("bad FOURCC (should be TSS\\0)");

    uint32_t code_base = read_beword_at(buffer, 0x04);
    uint32_t initial_pc = read_beword_at(buffer, 0x08);
    uint32_t data_base = read_beword_at(buffer, 0x0C);
    uint32_t data_size = read_beword_at(buffer, 0x18);

    if (code_base > size)
        throw bad_script_exception("code section outside of the file");

    if (data_base > size || data_base < code_base)
        throw bad_script_exception("data section outside of the file");

    if (data_base + data_size > size)
        throw bad_script_exception("data section is too large");

    if (initial_pc % 4 != 0)
        throw bad_script_exception("badly aligned initial PC");

    uint32_t code_size = (data_base - code_base);
    code_sect_ = new uint32_t[code_size / 4];
    memcpy(code_sect_, buffer + code_base, code_size);
    code_sect_size_ = code_size / 4;

    data_sect_ = new char[data_size];
    memcpy(data_sect_, buffer + data_base, data_size);
    data_sect_size_ = data_size;

    curr_thread().pc = initial_pc;
}

void cscript::run_one_instr()
{
}

}
