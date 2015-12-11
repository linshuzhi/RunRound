//
//  LoseLayer.cpp
//  RunRound
//
//  Created by LinShulong on 15/11/25.
//
//

#include "LoseLayer.h"

#include "../Manager/GameManager.h"
#include "../Utils/StringResources.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
namespace  {
    const char* kBg = "game_end_bg.png";
    const char* kButton_n = "game_end_button_n.png";
    const char* kButton_d = "game_end_button_d.png";
    const char* kLose = "lose.png";
    
}
LoseLayer::LoseLayer()
{
}

LoseLayer::~LoseLayer(){
    
}

bool LoseLayer::init(){
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(0,0,0,200));
    addChild(layer);
    
    auto bg = ui::Scale9Sprite::create(kBg);
    bg->setPosition(origin.x + visibleSize.width/ 2,origin.y + visibleSize.height / 2 + 50);
    auto bgSize = bg->getContentSize();
    //设置伸缩后的外框大小
    bg->setPreferredSize(Size(Vec2(visibleSize.width - 100, 300)));
    //bg伸缩后的内框大小
    bg->setCapInsets(Rect(50, 50, bgSize.width - 100, bgSize.height -100));
    layer->addChild(bg);
    
    
    /***************************/
    //back
    auto backItem = MenuItemImage::create(
                                          kButton_n,
                                          kButton_d,
                                          CC_CALLBACK_1(LoseLayer::menuBackCallback, this));
    
    backItem->setPosition(Vec2((bg->getContentSize().width - (backItem->getContentSize().width*2))/3 + backItem->getContentSize().width /2  ,
                               backItem->getContentSize().height ));
    auto backLabel = Label::create();//Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    backLabel->setSystemFontSize(18);
    backLabel->setString(StringResources::getInstance()->getText("GAME_BACK") );
    backLabel->setPosition(backItem->getContentSize().width /2 ,backItem->getContentSize().height /2+3);
    backItem->addChild(backLabel);
    /***************************/
    /***************************/
    //replay
    auto replayItem = MenuItemImage::create(
                                            kButton_n,
                                            kButton_d,
                                            CC_CALLBACK_1(LoseLayer::menuReplayCallback, this));
    
    replayItem->setPosition(Vec2((bg->getContentSize().width - (replayItem->getContentSize().width*2))*2/3 + replayItem->getContentSize().width *3/2  ,
                                 replayItem->getContentSize().height ));
    auto replayLabel = Label::create();//Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    replayLabel->setSystemFontSize(18);
    replayLabel->setString(StringResources::getInstance()->getText("GAME_REPLAY") );
    replayLabel->setPosition(replayItem->getContentSize().width /2 ,replayItem->getContentSize().height /2+3);
    replayItem->addChild(replayLabel);
    /***************************/
    // create menu, it's an autorelease object
    auto menu = Menu::create(backItem,replayItem,NULL);
    menu->setPosition(Vec2::ZERO);
    bg->addChild(menu);
    
    auto winLabel = Sprite::create(kLose);
    winLabel->setPosition(bg->getContentSize().width / 2,bg->getContentSize().height / 2);
    bg->addChild(winLabel);
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event) { return true; };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
    
}

void LoseLayer::menuNextCallback(cocos2d::Ref* pSender){
    GameManager::getInstance()->toNext();
}

void LoseLayer::menuReplayCallback(cocos2d::Ref* pSender){
    GameManager::getInstance()->toReplay();
}

void LoseLayer::menuBackCallback(cocos2d::Ref* pSender){
    GameManager::getInstance()->toBack();
}
