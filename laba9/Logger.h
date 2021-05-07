#include <cstring>
#include <ctime>
#include <set>

enum priority
{
    trace,
    debug,
    information,
    warning,
    error,
    fatal
};

std::string Priority(priority prior)
{
    std::string string;
    if(prior == trace)
        string = "trace";
    else if (prior == debug)
        string = "debug";
    else if (prior == information)
        string = "information";
    else if (prior == warning)
        string = "warning";
    else if (prior == error)
        string = "error";
    else if (prior == fatal)
        string = "fatal";
    return string;
}

struct LoggerInf
{
    std::ostream* stream;
    priority severity;
};

class Logger
{
    std::forward_list<std::pair<LoggerInf, std::string>>LogList;
    static std::map<std::string, std::pair<size_t, std::ostream*>>existedStream;
public:
    explicit Logger(std::forward_list<std::pair<LoggerInf, std::string>> logger_list) : LogList(std::move(logger_list))
    {
        for (auto& iter: existedStream)
            iter.second.first++;
    }
    Logger() = default;

    void log(const std::string& message, priority prior)
    {
        for (auto& iter: LogList)
        {
            time_t seconds = time(nullptr);
            tm* timeinfo = localtime(&seconds);
            char* tmp = asctime(timeinfo);
            tmp[std::strlen(tmp) - 1] = '\0';
            if(iter.first.severity <= prior)
                *iter.first.stream << "[" << tmp << "]" <<"[" << Priority(prior) << "]: " << message <<std::endl;
        }
    }

    ~Logger()
    {
        std::set<std::string> uniq_stream;
        for(auto item: LogList)
        {
            uniq_stream.insert(item.second);
        }
        for (auto& iter : uniq_stream)
        {
            auto str = existedStream.find(iter);
            if (str != existedStream.end())
                    str->second.first--;
                if (str->second.first == 0)
                {
                    if (str->first != "stdout")
                        delete str->second.second;
                    existedStream.erase(str->first);
                }
            else
                break;
        }
    }
    friend class Build_Logger;
};

std::map<std::string, std::pair<size_t, std::ostream*>>Logger::existedStream;