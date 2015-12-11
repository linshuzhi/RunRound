//
//  GameManager.cpp
//  RunRound
//
//  Created by LinShulong on 15/11/22.
//
//

#include "GameManager.h"
#include "../Utils/StringResources.h"
#include "UserLevelManager.h"
#include "DirectorManager.h"
#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"
#include "../Utils/BranchTools.h"

using namespace tinyxml2;
USING_NS_CC;


namespace  {
    const int kMapSize = 400;
    const char* kMapFileFormat = "map/map_%d.tmx";
}
GameManager* GameManager::_instance = nullptr;

GameManager::GameManager()
: _level(0)
{
    
}


GameManager::~GameManager(){
    
}


GameManager* GameManager::getInstance(){
    if (!_instance) {
        _instance = new GameManager();
        _instance->init();
    }
    return _instance;
}

void GameManager::init(){
    
}

void GameManager::startLevel(int level){

    _level = level;
    _mapInfo = readTmx(_level);
    DirectorManager::getInstance()->replaceScene(DirectorManager::SCENE_GAME);
    
    
    
}
MapModel GameManager::readTmx(int level){
    MapModel info;
    info.level = level;
    std::string filename = StringUtils::format(kMapFileFormat,level);

    auto data = FileUtils::getInstance()->getStringFromFile(filename);
    
    XMLDocument* myDocment = new tinyxml2::XMLDocument();
    //加载文件
    myDocment->Parse(data.c_str());
    
    tinyxml2::XMLElement* rootElement = myDocment->RootElement();
    
    
    XMLElement* layerElement = rootElement->FirstChildElement();
    
    while (layerElement) {
        
        auto  name = layerElement->Attribute("name");
        if(name == nullptr)
            break;
        std::string att = name;
        if(att == "ball"){
            
            auto objects = layerElement->FirstChildElement();
            int w = objects->IntAttribute("width");
            int h = objects->IntAttribute("height");
            info.startPoint.x = BranchTools::getRand(0, w) + objects->IntAttribute("x");
            info.startPoint.y = kMapSize - BranchTools::getRand(0, h) - objects->IntAttribute("y");
            auto properties = objects->FirstChildElement();
            auto propertys = properties->FirstChildElement();
            std::string na = propertys->Attribute("name");
            if(na == "PileCount"){
                info.pileCount = propertys->IntAttribute("value");
            }
        }
        if(att == "bubble"){
            auto objects = layerElement->FirstChildElement();
            while (objects) {
                BubblePoint binfo;
                int w = objects->IntAttribute("width");
                int h = objects->IntAttribute("height");
                binfo.point.x = BranchTools::getRand(0, w) + objects->IntAttribute("x");
                binfo.point.y = kMapSize - BranchTools::getRand(0, h) - objects->IntAttribute("y");
                auto properties = objects->FirstChildElement();
                auto propertys = properties->FirstChildElement();
                while (propertys) {
                    std::string na = propertys->Attribute("name");
                    if(na == "MoveLength"){
                        binfo.moveLength = propertys->FloatAttribute("value");
                    }else if(na == "MoveTime"){
                        binfo.moveTime = propertys->FloatAttribute("value");
                    }else if(na == "Scale"){
                        binfo.scale = propertys->FloatAttribute("value");
                    }
                    propertys = propertys->NextSiblingElement();
                }
                info.bubblePoints.push_back(binfo);
                objects = objects->NextSiblingElement();
                
            }
        }
        layerElement = layerElement->NextSiblingElement();
        
    }
    toRealMapData(info);
    return info;
}

MapModel GameManager::getMapData(int level){
    return _mapInfo;
}

void GameManager::toRealMapData(MapModel& info){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float ratio = visibleSize.width / kMapSize;
    
    float hight = (visibleSize.height - visibleSize.width) * 0.5f;
    

    info.startPoint.x *= ratio;
    info.startPoint.x += origin.x;
    info.startPoint.y *= ratio;
    info.startPoint.y += hight + origin.y;
    for (BubblePoint& binfo : info.bubblePoints) {
        binfo.point.x *= ratio;
        binfo.point.x += origin.x;
        
        binfo.point.y *= ratio;
        binfo.point.y += hight + origin.y;
        binfo.moveLength *= ratio;
    
    }

    
}

void GameManager::toBack(){
    DirectorManager::getInstance()->replaceScene(DirectorManager::SCENE_LEVEL);
}
void GameManager::toNext(){
    std::string filename = StringUtils::format(kMapFileFormat,_level+1);
    if(!FileUtils::getInstance()->isFileExist(filename)){
        startLevel(_level);
        return;
    }
    startLevel(_level + 1);
}
void GameManager::toReplay(){
    startLevel(_level);
}

void GameManager::setLevelSuccess(){
    UserLevelManager::getInstance()->setLevelSuccess(_level + 1);
}



