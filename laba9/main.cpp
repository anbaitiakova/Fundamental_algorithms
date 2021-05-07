#include <iostream>
#include <string>
#include "Builder.h"
#include "dependencies/include/nlohmann/json.hpp"

priority from_file(std::string prior)
{
    priority result = information;
    if(prior == "trace")
        result = trace;
    else if (prior == "debug")
        result = debug;
    else if (prior == "information")
        result = information;
    else if (prior == "warning")
        result = warning;
    else if (prior == "error")
        result = error;
    else if (prior == "fatal")
        result = fatal;
    return result;
}

int main(int argc, char** argv)
{
    Build_Logger builder;
    nlohmann::json objJson;
    std::fstream fileInput;
    fileInput.open(argv[1]);
    fileInput >> objJson;
    priority severity;
    std::string streamJson, tmp_prior;
    for(int i = 0; i < objJson["streams"].size(); i++)
    {
        streamJson = objJson["streams"][i]["name"];
        tmp_prior = objJson["streams"][i]["severity"];
        severity = from_file(tmp_prior);
        builder.addLoggerTarget(streamJson, severity);
    }
    fileInput.close();

    Logger* log1 = builder.createLogger();
    builder.addLoggerTarget("test.txt", warning);

    builder.addLoggerTarget("test.txt", fatal);
    //builder.addLoggerTarget("stdout", warning);

    //builder.addLoggerTarget("stdout", error);
    builder.addLoggerTarget("test.txt", information);
    builder.addLoggerTarget("test.txt", debug);
    builder.addLoggerTarget("stdout", information);
    Logger* log2 = builder.createLogger();
    log2->log("bibaboba", warning);
    log1->log("puk", fatal);
    delete log1;
    delete log2;
    return 0;
}