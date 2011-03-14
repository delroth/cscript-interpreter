#ifndef __EXCEPTION_HH_
# define __EXCEPTION_HH_

# include <string>

namespace cscript {

class exception
{
public:
    exception(const std::string& message) : message_(message)
    {
    }

    const std::string& message() const
    {
        return message_;
    }

private:
    std::string message_;
};

}

#endif
