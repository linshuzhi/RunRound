//
//  DirectorManager.cpp
//  RunRound
//
//  Created by LinShulong on 15/11/22.
//
//

#include "DirectorManager.h"
#include "../UI/LevelScene.h"
#include "../UI/GameScene.h"
#include "../UI/MainScene.h"
#include "cocos2d.h"

USING_NS_CC;

DirectorManager* DirectorManager::_instance = nullptr;
DirectorManager::DirectorManager()
{
    
}


DirectorManager::~DirectorManager(){
    
}


DirectorManager* DirectorManager::getInstance(){
    if (!_instance) {
        _instance = new DirectorManager();
        _instance->init();
    }
    return _instance;
}


void DirectorManager::init(){
    
}

void DirectorManager::replaceScene(TYPE_SCENE typeScene){
    Scene* scene = nullptr;
    switch (typeScene) {
        case SCENE_MAIN:
            scene = MainScene::createScene();
            break;
        case SCENE_LEVEL:
            scene = LevelScene::createScene();
            break;
        case SCENE_GAME:
            scene = GameScene::createScene();
            break;
        default:
            break;
    }
    CC_ASSERT(scene);
    Director::getInstance()->replaceScene(scene);
}




