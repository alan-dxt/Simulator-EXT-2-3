#ifndef ROUTESREADER_H_INCLUDED
#define ROUTESREADER_H_INCLUDED

#include "../Headers/httplib.h"

class RoutesReader{
    public:
        static void Reader(httplib::Server& api);
};

#endif