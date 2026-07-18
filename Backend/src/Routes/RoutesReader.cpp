#include <iostream>
#include <sstream>
#include <vector>
#include "../Headers/json.hpp"
#include "../Headers/httplib.h"
#include "../Objects/Command.h"
#include "../Objects/CommandResult.h"
#include "../Controllers/Utilities.h"
#include "./RoutesReader.h"


using namespace std;
using json = nlohmann::json;

vector<Command> splitCommands(const string& str){
    stringstream rawData(str);
    string line;
    vector<Command> commands;
    //separate the data into lines
    while(getline(rawData, line)){
        line = Utilities::Trim(line);
        if(line.empty() || line[0] == '#') continue;    //Comments
        //The line is separated into command and attributes
        stringstream rawline(line);
        string token;
        Command cmd;
        rawline >> cmd.command;     //rawline[0] = command name
        while(getline(rawline, token, '-')){
            token = Utilities::Trim(token);
            if (token.empty()) continue;
            //Flags
            if(token == "r"){
                cmd.params["r"] = "r";
                continue;
            }
            //Every attribute and its value is obtained
            size_t pos = token.find('=');
            if(pos == string::npos) continue;       //The simbol '=' is not found, the token is rejected
            string key = Utilities::Trim(token.substr(0, pos));
            string value = Utilities::Trim(token.substr(pos + 1));
            if(key.empty() || value.empty()) continue;      //not valid attribute
            cmd.params[key] = value;
            cout<<"key: ["<<key<<"] value: ["<<value<<"]\n";
        }
        commands.push_back(cmd);
    }
    return commands;
}

CommandResult executeCommand(const Command& command){
    if(command.command == "") return {true, "message"};
    
    return {false, " -> The command [" + command.command + "] was not recognized"};
}

vector<CommandResult> executeCommands(const vector<Command>& commands){
    vector<CommandResult> results;
    for(const Command& currentCommand: commands){
        results.push_back(executeCommand(currentCommand));
    }
    return results;
}

void RoutesReader::Reader(httplib::Server& api){
    api.Post("/execute", [](const httplib::Request& req, httplib::Response& res){
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        try{
            json body = json::parse(req.body);
            string data = body["data"];         //raw text
            vector<Command> commands = splitCommands(data);
            vector<CommandResult> results = executeCommands(commands);

            json response;

            for(const CommandResult& currentCR: results){
                response["results"].push_back({
                    {"succes", currentCR.success},
                    {"message", currentCR.message}
                });
            }

            res.status = 200;
            res.set_content(response.dump(4), "application/json");
        } catch(const exception& e){
            json error;
            error["error"] = e.what();
            res.status = 400;
            res.set_content(error.dump(), "application/json");
        }
    });
}
