//
//  LevelScene.cpp
//  RunRound
//
//  Created by LinShulong on 15/11/18.
//
//

#include "LevelScene.h"
#include "LevelLayer.h"
USING_NS_CC;

Scene* LevelScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LevelLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}