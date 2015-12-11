//
//  LevelLayer.cpp
//  RunRound
//
//  Created by LinShulong on 15/11/18.
//
//

#include "LevelLayer.h"
#include "LevelDataLayer.h"
#include "../Manager/DirectorManager.h"
#include "../Manager/SoundManager.h"
USING_NS_CC;


namespace  {
    const char * kBg = "game.jpg";
    const char * kBack = "back.png";
    const char * kButtonOgg = "sound/button.m4a";
}


bool LevelLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
   
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /***************************/
    //close
    auto closeItem = MenuItemImage::create(
                                           kBack,
                                           kBack,
                                           CC_CALLBACK_1(LevelLayer::menuCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + closeItem->getContentSize().width / 3 ,
                                origin.y + visibleSize.height - closeItem->getContentSize().height / 3));
    closeItem->setScale(0.5f);
    /***************************/
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    auto bg = Sprite::create(kBg);
    bg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    addChild(bg);
    
    
    auto dataLayer = LevelDataLayer::create();
    //dataLayer->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    bg->addChild(dataLayer);
    return true;
}

void LevelLayer::menuCallback(cocos2d::Ref* pSender){
    SoundManager::playEffect(kButtonOgg);
    DirectorManager::getInstance()->replaceScene(DirectorManager::SCENE_MAIN);
}

