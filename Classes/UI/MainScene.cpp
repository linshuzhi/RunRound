//
//  MainScene.cpp
//  RunRound
//
//  Created by LinShulong on 15/11/17.
//
//

#include "MainScene.h"
#include "MainLayer.h"
USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
