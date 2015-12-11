//
//  UserLevelManager.cpp
//  RunRound
//
//  Created by LinShulong on 15/11/18.
//
//

#include "UserLevelManager.h"
#include "cocos2d.h"
USING_NS_CC;

namespace  {
    const char* kLevelKey = "LEVEL_KEY";
    const char* kMapFileFormat = "map/map_%d.tmx";
}

UserLevelManager* UserLevelManager::_instance = nullptr;

UserLevelManager::UserLevelManager(){
    
}

UserLevelManager::~UserLevelManager(){
    
}


UserLevelManager* UserLevelManager::getInstance(){
    if (_instance == nullptr) {
        _instance = new UserLevelManager();
        _instance->init();
    }
    return _instance;
}


void UserLevelManager::init(){
//    for (int i = 1 ;i <= 38 ;i++) {
//        LevelData info;
//        info.levelId = i;
//        info.isSuccess = true;
//        if (i > 19) {
//            info.isSuccess = false;
//        }
//        _levelDatas.push_back(info);
//        
//    }
    _levelDatas.clear();
    int max = getLastLevelSuccess();
    for (int i = 1;; i++) {
        std::string file = StringUtils::format(kMapFileFormat,i);
        auto fullpath = FileUtils::getInstance()->fullPathForFilename(file);
        if(!FileUtils::getInstance()->isFileExist(fullpath)){
            break;
        }
        
        LevelData info;
        info.levelId = i;
        info.isSuccess = true;
//#if  COCOS2D_DEBUG == 0
        if (i > max) {
            info.isSuccess = false;
        }
//#endif
        _levelDatas.push_back(info);
    }
    
    
    
}

void UserLevelManager::setLevelSuccess(int level){
    int max = getLastLevelSuccess();
    if (level <= max) {
        return ;
    }
    UserDefault::getInstance()->setIntegerForKey(kLevelKey, level);
    UserDefault::getInstance()->flush();
    init();         //刷新
}

int UserLevelManager::getLastLevelSuccess(){
    return UserDefault::getInstance()->getIntegerForKey(kLevelKey, 1);
}

std::vector<LevelData>& UserLevelManager::getLevelDatas(){
    return _levelDatas;
}

