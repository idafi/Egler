#pragma once

#include <cstdarg>
#include <exception>
#include "Common.hpp"

namespace Egler
{
    class EglerException : public std::exception
    {
        #define MAX_MSG_LENGTH 512

        public:
            EglerException() { }
            EglerException(const char *msg, ...)
            {
                va_list args;
                va_start(args, msg);
                MakeMsg(msg, args);
                va_end(args);
            }

            const char *what() const throw()
            {
                return msg;
            }

        protected:
            void MakeMsg(const char *msg, va_list va_args)
            {
                vsnprintf(this->msg, MAX_MSG_LENGTH, msg, va_args);
            }
        
        private:
            char msg[MAX_MSG_LENGTH];
    };

    // HACK: this sucks
    #define _DefineException(name) \
        class name : public EglerException \
        { \
            public: \
                name(const char *msg, ...) \
                { \
                    va_list args; \
                    va_start(args, msg); \
                    MakeMsg(msg, args); \
                    va_end(args); \
                } \
        };

    _DefineException(NullPtrException)
    _DefineException(BadArgumentException)
    _DefineException(OutOfRangeException)
    _DefineException(InvalidOperationException)
    _DefineException(NotInitializedException)
    _DefineException(FailureException)
}