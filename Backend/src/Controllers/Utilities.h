#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include <string>

class Utilities{
    public:
        static std::string Trim(const std::string& str);
        static bool diskExist(const std::string& path);
};

#endif