#ifndef __CSCRIPT_HH_
# define __CSCRIPT_HH_

# include "endian.hh"
# include "exception.hh"
# include "thread-context.hh"

# include <boost/array.hpp>
# include <cstdint>
# include <cstdlib>

namespace cscript {

class bad_script_exception : public exception
{
public:
    bad_script_exception(const std::string& message) : exception(message)
    {
    }
};

class cscript
{
public:
    cscript(const char* buffer, size_t size) :
        code_sect_(0), code_sect_size_(0), data_sect_(0), data_sect_size_(0),
        current_thread_(0), done_(false)
    {
        this->parse_bytecode(buffer, size);
    }

    /**
     * Destructor of the cscript object.
     */
    ~cscript()
    {
        delete[] code_sect_;
        delete[] data_sect_;
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
     * Returns the current thread.
     */
    thread_context& curr_thread()
    {
        return thread(current_thread_);
    }

    const thread_context& curr_thread() const
    {
        return thread(current_thread_);
    }

    /**
     * Runs the bytecode.
     */
    void run()
    {
        while (!done())
            run_one_instr();
    }

    /**
     * Executes one instruction.
     */
    void run_one_instr();

    /**
     * Is the interpretation done or not?
     */
    bool done() const
    {
        return done_;
    }

private:
    /**
     * Initializes a cscript object from a buffer containing bytecode.
     * Does not take ownership of the buffer.
     *
     * @param buffer The buffer containing the script bytecode.
     * @param size The size of the buffer.
     */
    void parse_bytecode(const char* buffer, size_t size);

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
     * Is the interpretation done?
     */
    bool done_;

    /**
     * Execution context of the script threads.
     */
    boost::array<thread_context, MAX_THREADS> threads_;
};

}

#endif
