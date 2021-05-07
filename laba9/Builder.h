#include <iostream>
#include <fstream>
#include <map>
#include <forward_list>
#include <climits>
#include "Logger.h"
#include <filesystem>

std::ostream* KindOfFlow(const std::string& string)
{
    std::ostream* flow_stdout = &std::cout;
    std::ofstream* flow_file;
    if (string != "stdout")
    {
        flow_file = new std::ofstream(string);
        if(!flow_file->is_open())
            throw "Something wrong with file:((";
        return flow_file;
    }
    return flow_stdout;
}

class Builder
{
public:
    virtual void addLoggerTarget(const std::string& string, priority prior = information) = 0;
    virtual ~Builder(){}
};

std::string parse_path(std::string path)
{
    std::string result;
    char* res;
    size_t pos;
    char dir[PATH_MAX + 1];
    if(path == "stdout")
        return path;
    pos = path.find('/', 0);
    if (pos == -1)
    {
        res = realpath(path.c_str(), dir);
        result = std::string(dir);
        return result;
    }
    return path;
}

class Build_Logger: public Builder
{
    std::forward_list<std::pair<LoggerInf, std::string>> logger_list;
public:
    Build_Logger() = default;
    
    void addLoggerTarget(const std::string& string, priority prior = information) override
    {
        LoggerInf tmp;
        std::string path = parse_path(string);
        auto iter = Logger::existedStream.find(path);
        if(iter != Logger::existedStream.end())
        {
            tmp.stream = iter->second.second;
            tmp.severity = prior;
            logger_list.push_front(std::make_pair(tmp, path));
        }
        else
        {
            std::ostream* stream_tmp = KindOfFlow(path);
            tmp.stream = stream_tmp;
            tmp.severity = prior;
            Logger::existedStream.insert(std::make_pair(path, std::make_pair(0, stream_tmp)));
            logger_list.push_front(std::make_pair(tmp, path));
        }
    }

    Logger* createLogger()
    {
        Logger* log = new Logger(logger_list);
        return log;
    }

    ~Build_Logger()
    {
        for(auto iter: Logger::existedStream)
        {
            if(iter.first != "stdout")
            {
                iter.second.second->flush();
                delete iter.second.second;
            }
        }
    }
};