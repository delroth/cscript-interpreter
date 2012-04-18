#include "address.hh"
#include "cscript.hh"
#include "endian.hh"
#include "instruction-dispatcher.hh"
#include "instruction-handler.hh"
#include "type.hh"

#include <boost/format.hpp>
#include <cstring>
#include <sstream>

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

    curr_thread().pc = initial_pc / 4;
    curr_thread().st = thread_state::RUNNABLE;
}

bool cscript::done() const
{
    if (done_)
        return true;

    for (const auto& thread : threads_)
        if (thread.st & thread_state::RUNNABLE)
            return false;

    return true;
}

void cscript::schedule_next()
{
    uint16_t old_thread = current_thread_;
    uint16_t chosen;

    for (chosen = 1; chosen <= MAX_THREADS; ++chosen)
    {
        thread_context& th = threads_[(old_thread + chosen) % MAX_THREADS];
        if (th.st & thread_state::RUNNABLE)
            break;
    }

    current_thread_ = (old_thread + chosen) % MAX_THREADS;
}

void cscript::run_one_instr()
{
    //std::cerr << curr_thread();
    //std::cout << std::hex << std::setw(8) << std::setfill('0');
    //std::cout << (curr_thread().pc * 4) << std::endl;
    uint32_t opcode = read_code_at(curr_thread().pc++);
    boost::optional<instruction::handler> handler;

    handler = instruction::dispatcher::get().get_handler(opcode);
    if (!handler)
    {
        std::ostringstream oss;
        oss << "no handler found for opcode ";
        oss << std::hex << opcode;
        throw bad_script_exception(oss.str());
    }
    else
        (*handler)(*this, opcode);
}

bool cscript::handle_common_syscall(uint16_t syscall,
                                    const std::vector<uint32_t>& args)
{
    if (syscall == 0xFFFD)
    {
        curr_thread().frames_to_wait = args[0];
        curr_thread().st |= thread_state::WAIT_FRAMES;
    }
    else if (syscall == 0xFFFF)
    {
        std::string fmt_string = address::get_ptr(*this, args[0]);
        boost::format fmt(fmt_string);
        for (unsigned int i = 1; i < args.size(); ++i)
            fmt = fmt % args[i];
        std::cerr << "[log] " << fmt;
    }
    else
        return false;

    variable& v = curr_thread().scratch.top(0);
    v.value.u32 = 0;
    v.address = 0;
    v.type = type::IMMEDIATE | type::SWORD;
    v.pointed_size = 4;
    curr_thread().scratch.push();

    return true;
}

uint16_t cscript::register_external_pointer(char* addr)
{
    auto it = registered_addrs_.find(addr);
    if (it != registered_addrs_.end())
        return it->second;

    uint16_t id = next_free_external_++;
    if (id >= 0x400)
        throw invalid_external_pointer_exception("too much external pointers");

    external_pointers_[id] = addr;
    registered_addrs_[addr] = id;

    return id;
}

char* cscript::get_external_pointer(uint16_t id)
{
    if (!external_pointers_[id])
        throw invalid_external_pointer_exception("unregistered id");
    return external_pointers_[id];
}

const char* cscript::get_external_pointer(uint16_t id) const
{
    if (!external_pointers_[id])
        throw invalid_external_pointer_exception("unregistered id");
    return external_pointers_[id];
}

}
