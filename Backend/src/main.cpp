#include <iostream>
#include "./Headers/httplib.h"
#include "./Routes/RoutesReader.h"

using namespace std;

int main() {
    httplib::Server api;
    cout<<"Working on http://localhost:8080\n";

    //Endpoints for the console
    RoutesReader::Reader(api);

    api.Get("/", [](const httplib::Request& req, httplib::Response& res){
        res.set_content("Api res c++ ok", "text/plain");
    });


    api.listen("0.0.0.0", 8080);
    return 0;
}