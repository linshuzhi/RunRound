//
//  TouchLayer.cpp
//  RunRound
//
//  Created by LinShulong on 15/11/22.
//
//

#include "TouchLayer.h"
#include "../Utils/StringResources.h"
#include "TouchLayerDelegate.h"
USING_NS_CC;


namespace  {
    const char * kButton = "game_button.png";
    
}

TouchLayer::TouchLayer()
:_delegate(nullptr)
, _buttonlabel(nullptr)
, _btnItem(nullptr)
{
    
}
TouchLayer::~TouchLayer(){
    
}

void TouchLayer::setDelegate(TouchLayerDelegate* delegate){
    _delegate = delegate;
}

bool TouchLayer::init()
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
    //about
    _btnItem = MenuItemImage::create(
                                           kButton,
                                           kButton,
                                           CC_CALLBACK_1(TouchLayer::menuCallback, this));
    _btnItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                origin.y + visibleSize.height / 10 + _btnItem->getContentSize().height / 2));
    _buttonlabel = Label::create();//Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    _buttonlabel->setString(StringResources::getInstance()->getText("GAME_NEXT") );
    _buttonlabel->setSystemFontSize(24);
    
    _buttonlabel->setPosition(_btnItem->getContentSize().width /2 ,_btnItem->getContentSize().height /2+ 3);
    // position the label on the center of the screen
    _btnItem->addChild(_buttonlabel);
    /***************************/
    // create menu, it's an autorelease object
    auto menu = Menu::create(_btnItem,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}
void TouchLayer::showRunBtn(){
    _buttonlabel->setString(StringResources::getInstance()->getText("GAME_RUN") );
}

bool TouchLayer::onTouchBegan(Touch* touch, Event* event)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Point point = touch->getLocation();
    //CCLOG("x = %f, y = %f",point.x,point.y);
    if (point.y >= origin.y + (visibleSize.height - visibleSize.width)/2 &&
        point.y <= origin.y + (visibleSize.height - visibleSize.width)/2 + visibleSize.width) {
        if(_delegate)
            _delegate->onTouchLayerTouch(point);
        return true;
    }
    
    return false;
}


void TouchLayer::menuCallback(cocos2d::Ref* pSender){
    if(_delegate)
        _delegate->onTouchLayerButton();
    
}

void TouchLayer::setBtnEnabled(bool bEnabled){
    _btnItem->setEnabled(bEnabled);
}
