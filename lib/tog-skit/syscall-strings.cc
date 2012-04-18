#include "../address.hh"
#include "../type.hh"
#include "syscall-strings.hh"

namespace cscript { namespace tog_skit { namespace syscalls {

struct str_descriptor
{
    str_descriptor(const std::string& s)
    {
        parse(s.c_str());
    }

    void parse(const char* s)
    {
        type = *s++;
        if (type == 0x1F)
        {
            while (*s == '(' || *s == ' ') s++;
            scs.file_index = (uint32_t)parse_number(s);
            while (*s == ' ' || *s == ',') s++;
            scs.string_index = (uint32_t)parse_number(s);
            while (*s == ' ' || *s == ')') s++;
            if (*s)
                throw exception("trailing characters in 0x1F descriptor");
        }
        else
            throw exception("unknown string descriptor type");
    }

    int32_t parse_number(const char*& s)
    {
        int sign = 1;
        int32_t n = 0;

        if (*s == '-')
        {
            sign = -1;
            s++;
        }
        else if (*s == '+')
            s++;

        if (*s == '0')
        {
            s++;
            if (*s == 'x' || *s == 'X')
                n = parse_hex(++s);
            else if (*s == 'b' || *s == 'B')
            {
                s++;
                while (*s == '0' || *s == '1')
                {
                    n <<= 1;
                    n += (*s++ - '0');
                }
            }
            else
            {
                while (*s >= '0' && *s <= '7')
                {
                    n <<= 3;
                    n += (*s++ - '0');
                }
            }
        }
        else if (*s == '$')
            n = parse_base64(++s);
        else
        {
            while (*s >= '0' && *s <= '9')
            {
                n *= 10;
                n += (*s++ - '0');
            }
        }

        return sign * n;
    }

    int32_t parse_hex(const char* s)
    {
        int32_t n = 0;

        static uint8_t val[256] = { 0xFF };
        for (int i = 0; i < 10; ++i) val['0' + i] = i;
        for (int i = 0; i < 6; ++i) val['a' + i] = val['A' + i] = 10 + i;

        while (val[(uint8_t)*s] != 0xFF)
        {
            n <<= 4;
            n += val[(uint8_t)*s++];
        }

        return n;
    }

    int32_t parse_base64(const char* s)
    {
        int32_t n = 0;

        static uint8_t val[256] = { 0xFF };
        for (int i = 0; i < 10; ++i) val['0' + i] = i;
        for (int i = 0; i < 26; ++i) val['a' + i] = 10 + i;
        for (int i = 0; i < 26; ++i) val['A' + i] = 36 + i;
        val['~'] = 62;
        val['_'] = 63;

        while (val[(uint8_t)*s] != 0xFF)
        {
            n <<= 6;
            n += val[(uint8_t)*s++];
        }

        return n;
    }

    uint8_t type;
    struct
    {
        uint32_t file_index;
        uint32_t string_index;
    } scs;
};

void skit_get_string(tog_skit_cscript& script,
                     const std::vector<uint32_t>& args)
{
    std::string str = address::get_ptr(script, args[0]);
    str_descriptor descriptor(str);

    uint32_t ret;
    if (descriptor.type == 0x1F)
    {
        char* ptr = script.backend().get_stringtable_base();
        uint32_t offset = script.backend().get_string_offset(
            descriptor.scs.string_index
        );

        uint16_t id = script.register_external_pointer(ptr);
        ret = address::make_external_addr(id, offset);
    }
    else
        throw exception("unknown string descriptor type");

    variable& v = script.curr_thread().scratch.top(0);
    v.value.u32 = ret;
    v.address = 0;
    v.type = type::IMMEDIATE | type::SWORD;
    script.curr_thread().scratch.push();
}

}}}
