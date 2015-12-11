//
//  AboutLayer.cpp
//  LeftRight
//
//  Created by LinShulong on 15/10/27.
//
//

#include "AboutLayer.h"
#include "../Manager/SoundManager.h"
USING_NS_CC;


namespace  {
    const char * kBack = "back.png";
    const char * kAbout = "about.png";
    const char * kTitle = "title.png";
    const char * kButtonOgg = "sound/button.m4a";
}
bool AboutLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto layer = LayerColor::create(Color4B(122, 122, 122, 255));
    addChild(layer);
    /***************************/
    //about
    auto closeItem = MenuItemImage::create(
                                           kBack,
                                           kBack,
                                           CC_CALLBACK_1(AboutLayer::menuCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + closeItem->getContentSize().width / 3 ,
                                origin.y + visibleSize.height - closeItem->getContentSize().height / 3));
    closeItem->setScale(0.5f);
    /***************************/
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    
    auto title = Sprite::create(kTitle);
    title->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    layer->addChild(title);
    
    auto aboutLabel = Label::create();
    aboutLabel->setSystemFontSize(24);
    aboutLabel->setTextColor(Color4B(0, 0, 0, 255));
    aboutLabel->setString("v1.0");
    aboutLabel->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - title->getContentSize().height));
    layer->addChild(aboutLabel);
    
    auto about = Sprite::create(kAbout);
    about->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y + about->getContentSize().height));
    layer->addChild(about);
    
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event) { return true; };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void AboutLayer::menuCallback(cocos2d::Ref* pSender){
    SoundManager::playEffect(kButtonOgg);
    removeFromParent();
}


