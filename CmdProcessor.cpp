#include <vector>
#include <cstdlib>
#include "CmdProcessor.h"

filter_map CmdProcessor::filters;
std::map<unsigned int, unsigned int> CmdProcessor::userMap;
std::map<unsigned int, unsigned int> CmdProcessor::disableBuildAccountIdSet;
std::map<unsigned int, unsigned int> CmdProcessor::disableBuildConnIdSet;

void CmdProcessor::init() {
    //filters[onDisableBuild] = new std::regex("\\b(GET /disableBuild?id=)([^\r]+)");
    //filters.insert(std::pair<handler_method, std::string>(onDisableBuild, "GET /disableBuild?id="));
    filters["GET /disableBuild?id="] = onDisableBuild;
}

void CmdProcessor::process(char* buf, int len) {
    std::vector<std::string> vargs;
    unsigned int eqsign, amp, i;
    std::string* args;
    //std::smatch match;
    std::string buffer(buf);
    for(filter_iterator iter = filters.begin(); iter != filters.end(); ++iter) {
        // function = iterator->first = key
        // regex = iterator->second = value
        //std::regex re = iter->second;
        /*
        if (std::regex_search(buf, match, iter->second)) {
            // The first sub_match is the whole string; the next
            // sub_match is the first parenthesized expression.
            if (match.size() == 0) continue;
            string args[] = new string[match.size()];
            for(int i = 0; i < match.size(); ++i) {
                args[i] = match[i].str();
            }
            iterator->first(match.size(), args);
            break;
        }
        */
        std::string pattern = iter->first;
        if(std::string::npos != buffer.find(pattern)) {
            buffer[buffer.find("\r")] = 0;
            do {
                eqsign = buffer.find("=");
                amp = buffer.find("&", eqsign + 1);
                vargs.push_back(buffer.substr(eqsign + 1, amp));
            } while(amp != std::string::npos);
            args = new std::string[vargs.size()];
            for(i = 0; i < vargs.size(); ++i)
                args[i] = vargs.at(i);
            iter->second(vargs.size(), args);
        }
    }
}