//
//  MainLayer.cpp
//  RunRound
//
//  Created by LinShulong on 15/11/17.
//
//

#include "MainLayer.h"
#include "AboutLayer.h"
#include "../Utils/StringResources.h"
#include "../Manager/SoundManager.h"
#include "../Manager/DirectorManager.h"
#include "../Utils/BranchTools.h"
#include "../AdsHelp.h"
USING_NS_CC;

namespace  {
    const char * kMainbg = "main.jpg";
    const char * kButton = "button.png";
    const char * kSoundAble = "sound_able.png";
    const char * kSoundDisable = "sound_disable.png";
    
    const char * kButtonOgg = "sound/button.m4a";
}

MainLayer::MainLayer()
: _soundOffItem(nullptr)
, _soundOnItem(nullptr)
{
    
}

MainLayer::~MainLayer()
{
    SoundManager::deleteDelegate(this);
}
// on "init" you need to initialize your instance
bool MainLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto bg = Sprite::create(kMainbg);
    bg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    addChild(bg);
    
    const int txtHight = 2;
    /**********************/
    //play
    auto playItem = MenuItemImage::create(
                                          kButton,
                                          kButton,
                                          CC_CALLBACK_1(MainLayer::menuPlayCallback, this));
    playItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                               origin.y + visibleSize.height / 2 + playItem->getContentSize().height ));
    auto playLabel = Label::create();//Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    playLabel->setString(StringResources::getInstance()->getText("MAIN_PLAY") );
    playLabel->setSystemFontSize(24);
    
    playLabel->setPosition(playItem->getContentSize().width /2 ,playItem->getContentSize().height /2+txtHight);
    // position the label on the center of the screen
    playItem->addChild(playLabel);
    
    

    
    /***************************/
    //about
    auto aboutItem = MenuItemImage::create(
                                           kButton,
                                           kButton,
                                           CC_CALLBACK_1(MainLayer::menuAboutCallback, this));
    
    aboutItem->setPosition(Vec2(origin.x + visibleSize.width /2 ,
                                origin.y + visibleSize.height / 2 - aboutItem->getContentSize().height));
    auto aboutLabel = Label::create();//Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    aboutLabel->setString(StringResources::getInstance()->getText("MAIN_ABOUT") );
    aboutLabel->setSystemFontSize(24);
    
    aboutLabel->setPosition(aboutItem->getContentSize().width /2 ,aboutItem->getContentSize().height /2+txtHight);
    // position the label on the center of the screen
    aboutItem->addChild(aboutLabel);
    
    /***************************/
    /************************/
    //sound
    _soundOffItem = MenuItemImage::create(
                                           kSoundAble,
                                           kSoundAble,
                                           CC_CALLBACK_1(MainLayer::menuSoundOffCallback, this));
    
    _soundOffItem->setPosition(Vec2(origin.x + visibleSize.width /2 ,
                                origin.y + visibleSize.height / 4));
    
    
    _soundOnItem = MenuItemImage::create(
                                           kSoundDisable,
                                           kSoundDisable,
                                           CC_CALLBACK_1(MainLayer::menuSoundOnCallback, this));
    
    _soundOnItem->setPosition(Vec2(origin.x + visibleSize.width /2 ,
                                origin.y + visibleSize.height / 4));

    /*********************/
    // create menu, it's an autorelease object
    auto menu = Menu::create( playItem,aboutItem,_soundOffItem,_soundOnItem,NULL);
    menu->setPosition(Vec2::ZERO);
    bg->addChild(menu, 1);    /////////////////////////////

    updateSound();
    
    SoundManager::addDelegate(this);
    return true;
}

void MainLayer::menuSoundOffCallback(cocos2d::Ref* pSender){
    SoundManager::setEffect(false);
    SoundManager::setMusic(false);
    SoundManager::playEffect(kButtonOgg);
}

void MainLayer::menuSoundOnCallback(cocos2d::Ref* pSender){
    SoundManager::setEffect(true);
    SoundManager::setMusic(true);
    SoundManager::playEffect(kButtonOgg);
}

void MainLayer::menuAboutCallback(cocos2d::Ref* pSender){
    auto layer = AboutLayer::create();
    addChild(layer);
    SoundManager::playEffect(kButtonOgg);
}

void MainLayer::menuPlayCallback(cocos2d::Ref* pSender){
    AdsHelp::showBanner();
    DirectorManager::getInstance()->replaceScene(DirectorManager::SCENE_LEVEL);
    SoundManager::playEffect(kButtonOgg);
}

void MainLayer::updateSound(){
    auto bSound = SoundManager::getEffect();
    _soundOffItem->setVisible(bSound);
    _soundOffItem->setEnabled(bSound);
    _soundOnItem->setVisible(!bSound);
    _soundOnItem->setEnabled(!bSound);

    
}

void MainLayer::soundUpdate(){
    updateSound();
}



