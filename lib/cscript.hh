#ifndef __CSCRIPT_HH_
# define __CSCRIPT_HH_

# include "endian.hh"
# include "exception.hh"
# include "thread-context.hh"

# include <array>
# include <cstdint>
# include <cstdlib>
# include <map>

namespace cscript {

class bad_script_exception : public exception
{
public:
    bad_script_exception(const std::string& message) : exception(message)
    {
    }
};

class invalid_external_pointer_exception : public exception
{
public:
    invalid_external_pointer_exception(const std::string& m) : exception(m)
    {
    }
};

class cscript
{
public:
    /**
     * Default constructor, does not initialize the sections. The script must
     * be parsed using the parse_bytecode method.
     *
     * When possible, use the cscript(const char*, size_t) constructor instead.
     */
    cscript() :
        code_sect_(0), code_sect_size_(0), data_sect_(0), data_sect_size_(0),
        current_thread_(0), done_(false), next_free_external_(0)
    {
        external_pointers_.fill(0);
    }

    cscript(const char* buffer, size_t size) :
        code_sect_(0), code_sect_size_(0), data_sect_(0), data_sect_size_(0),
        current_thread_(0), done_(false), next_free_external_(0)
    {
        external_pointers_.fill(0);
        this->parse_bytecode(buffer, size);
    }

    /**
     * Destructor of the cscript object.
     */
    virtual ~cscript()
    {
        delete[] code_sect_;
        delete[] data_sect_;
    }

    /**
     * Handles a syscall. To be implemented in subclasses.
     */
    virtual void handle_syscall(uint16_t syscall,
                                const std::vector<uint32_t>& args) = 0;

    /**
     * Handles all common syscalls (which have negative ids).
     */
    bool handle_common_syscall(uint16_t syscall,
                               const std::vector<uint32_t>& args);

    /**
     * Registers a pointer to an external data page and returns the id for this
     * external pointer.
     *
     * @param addr The address to the external page.
     * @return An ID used to reference this external page.
     */
    uint16_t register_external_pointer(char* addr);

    /**
     * Gets a pointer to the data associated with an external pointer.
     *
     * @param id The external pointer id.
     * @return The address for the memory block referenced by that id.
     */
    char* get_external_pointer(uint16_t id);
    const char* get_external_pointer(uint16_t id) const;

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
     * Returns the current thread id.
     */
    uint16_t curr_thread_id() const
    {
        return current_thread_;
    }

    /**
     * Schedule the next runnable thread.
     */
    void schedule_next();

    /**
     * Runs the bytecode.
     */
    void run()
    {
        while (!done())
        {
            if (curr_thread().yielding())
                schedule_next();
            else
                run_one_instr();
        }
    }

    /**
     * Executes one instruction in the current thread.
     */
    void run_one_instr();

    /**
     * Is the interpretation done or not?
     */
    bool done() const;

    /**
     * Exits the script interpretation.
     */
    void exit()
    {
        if (current_thread_ == 0)
            done_ = true;
        else
        {
            curr_thread().st = thread_state::NOT_RUNNING;
            schedule_next();
        }
    }

    /**
     * Gets the data section size.
     */
    size_t data_size() const
    {
        return data_sect_size_;
    }

    /**
     * Initializes a cscript object from a buffer containing bytecode.
     * Does not take ownership of the buffer.
     *
     * @param buffer The buffer containing the script bytecode.
     * @param size The size of the buffer.
     */
    void parse_bytecode(const char* buffer, size_t size);

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
    uint16_t current_thread_;

    /**
     * Is the interpretation done?
     */
    bool done_;

    /**
     * Execution context of the script threads.
     */
    std::array<thread_context, MAX_THREADS> threads_;

    /**
     * Metadata for external pointers handling.
     */
    std::array<char*, 0x400> external_pointers_;
    std::map<char*, uint16_t> registered_addrs_;
    uint16_t next_free_external_;
};

}

#endif
