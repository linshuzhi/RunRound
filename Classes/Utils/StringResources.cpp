//
//  StringResources.cpp
//  LeftRight
//
//  Created by LinShulong on 15/10/27.
//
//

#include "StringResources.h"
#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"


using namespace tinyxml2;
USING_NS_CC;


StringResources* StringResources::_instance  = nullptr;

StringResources* StringResources::getInstance(){
    if (!_instance) {
        _instance = new StringResources();
        _instance->init();
    }
    return _instance;
}

void StringResources::init(){
    auto data = FileUtils::getInstance()->getStringFromFile("string.xml");

    
    XMLDocument* myDocment = new tinyxml2::XMLDocument();
    myDocment->Parse(data.c_str());
    tinyxml2::XMLElement* rootElement = myDocment->RootElement();
    XMLElement* layerElement = rootElement->FirstChildElement();
    
    while (layerElement) {
        auto  name = layerElement->Name();
        if(name == nullptr)
            break;
        _stringMap.insert(std::make_pair(name,layerElement->GetText()));
        layerElement = layerElement->NextSiblingElement();
        
    }
}

const char * StringResources::getText(const char* ID){
    auto item = _stringMap.find(ID);
    if (item != _stringMap.end()) {
        return item->second.c_str();
    }
    return "";
    
}