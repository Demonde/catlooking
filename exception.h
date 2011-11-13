#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

class Exception : public std::exception
{
public:
    Exception(const char * message)
        : _message (message)
    {}
    const char * what() const throw()
    {  return _message ? _message : "";  }

      private:
    const char * _message;
};

#endif // EXCEPTION_H
