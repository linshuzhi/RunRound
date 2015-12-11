//
//  StringResources.h
//  LeftRight
//
//  Created by LinShulong on 15/10/27.
//
//

#ifndef __LeftRight__StringResources__
#define __LeftRight__StringResources__
#include <map>
#include <string>
class StringResources{
public:
    static StringResources* getInstance();
    const char * getText(const char* ID);
private:
    void init();
private:
    std::map<std::string,std::string> _stringMap;
    static StringResources* _instance;
};

#endif /* defined(__LeftRight__StringResources__) */
