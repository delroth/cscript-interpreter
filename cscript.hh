#ifndef __CSCRIPT_HH_
# define __CSCRIPT_HH_

# include "endian.hh"
# include "thread-context.hh"

# include <boost/array.hpp>
# include <cstdint>
# include <cstdlib>

namespace cscript {

class cscript
{
public:
    cscript() : code_sect_(0), code_sect_size_(0),
                data_sect_(0), data_sect_size_(0)
    {
    }

    /**
     * Destructor of the cscript object.
     */
    ~cscript()
    {
        delete code_sect_;
        delete data_sect_;
    }

    /**
     * Read an uint32_t from the code section.
     *
     * @param idx The index of the code in the section.
     * @return The data at index idx in the code section.
     */
    uint32_t read_code_at(unsigned int idx) const
    {
        return endian::from_big(code_sect_[idx]);
    }

    /**
     * Return a pointer to a memory zone in the data section from a specified
     * offset.
     *
     * @param off The offset in the data section.
     * @return A pointer to the specified location in the data section.
     */
    char* data_at(unsigned int off)
    {
        return data_sect_ + off;
    }

    const char* data_at(unsigned int off) const
    {
        return data_sect_ + off;
    }

    /**
     * Returns the thread context from a thread id.
     */
    thread_context& thread(uint16_t n)
    {
        return threads_[n];
    }

    const thread_context& thread(uint16_t n) const
    {
        return threads_[n];
    }

    /**
     * Initializes a cscript object from a buffer containing bytecode.
     * Does not take ownership of the buffer.
     *
     * @param buffer The buffer containing the script bytecode.
     * @param size The size of the buffer.
     * @return The boolean value false in case of error, else true.
     */
    bool parse_bytecode(const char* buffer, size_t size);

private:
    /**
     * Code section of the compiled bytecode. An uint32_t array as it will
     * only be accessed 4 byte by 4 byte.
     */
    uint32_t* code_sect_;

    /**
     * Size of the code section in uint32s.
     */
    size_t code_sect_size_;

    /**
     * Data section of the compiled bytecode. Byte array.
     */
    char* data_sect_;

    /**
     * Size of the data section in bytes.
     */
    size_t data_sect_size_;

    /**
     * Current thread index.
     */
    size_t current_thread_;

    /**
     * Execution context of the script threads.
     */
    boost::array<thread_context, MAX_THREADS> threads_;
};

}

#endif
