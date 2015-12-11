//
//  GameLayer.cpp
//  RunRound
//
//  Created by LinShulong on 15/11/22.
//
//

#include "GameLayer.h"
#include "../Manager/DirectorManager.h"
#include "TouchLayer.h"
#include "BallLayer.h"
#include "BubbleLayer.h"
#include "OriginLayer.h"
#include "PhysicsBodyMask.h"
#include "WinLayer.h"
#include "LoseLayer.h"
#include "../Manager/GameManager.h"
#include "../Manager/SoundManager.h"
#include "../AdsHelp.h"
USING_NS_CC;

namespace  {
    const char * kBg = "game.jpg";
    const char * kBack = "back.png";
    const int kTouch = 10;
    const char * kButtonOgg = "sound/button.m4a";
    const char * kNextOgg = "sound/next.m4a";
    const char * kRunOgg = "sound/run.m4a";
    
    const char * kPileOgg = "sound/pile.m4a";
    const char * kVictoryOgg = "sound/victory.m4a";
    const char * kFailureOgg = "sound/failure.m4a";
    const char * kRunBgOgg = "sound/run_bg.m4a";
    const char * kBoomOgg = "sound/boom.m4a";
    
    
}

GameLayer::GameLayer()
: _balllayer(nullptr)
, _originLayer(nullptr)
, _disBubble(0)
, _pileCount(0)
, _touchLayer(nullptr)
, _bTouch(true)
{
    
}
GameLayer::~GameLayer(){
    SoundManager::stopBackgroundMusic();
}
bool GameLayer::init(){
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
                                           CC_CALLBACK_1(GameLayer::menuCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + closeItem->getContentSize().width / 3 ,
                                origin.y + visibleSize.height - closeItem->getContentSize().height / 3));
    closeItem->setScale(0.5f);

    /***************************/
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, kTouch);
    
    

    ;
    auto bg = Sprite::create(kBg);
    bg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    addChild(bg);
    if(GameManager::getInstance()->getCurLevel() == 1){
        auto txt = Label::create();//Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
        txt->setString("set a center of a circle and\nclick run button to hit all white ball");
        txt->setColor(Color3B(0,0,0));
        txt->setSystemFontSize(24);
    
        txt->setPosition(origin.x + visibleSize.width / 2 ,origin.y + visibleSize.height - 80);
        // position the label on the center of the screen
        bg->addChild(txt);
    }
    
    _touchLayer = TouchLayer::create();
    _touchLayer->setDelegate(this);
    _touchLayer->setBtnEnabled(false);
    addChild(_touchLayer , kTouch);
    
    addBallLayer();
    addBubbleayer();
    addOriginLayer();
    
    auto info = GameManager::getInstance()->getMapData(GameManager::getInstance()->getCurLevel());
    _pileCount = info.pileCount;
    if (_pileCount == 1) {
        _touchLayer->showRunBtn();
    }
    /* 碰撞监听 */
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    return true;
}

bool GameLayer::onContactBegin(PhysicsContact& contact)
{
    auto nodeA = (Sprite*)contact.getShapeA()->getBody()->getNode();
    auto nodeB = (Sprite*)contact.getShapeB()->getBody()->getNode();
    
    if (nodeA == NULL || nodeB == NULL)
    {
        return true;
    }
    
    if (nodeA->getTag() == TAG_BUBBLE) {
        disBubble(nodeA);
        return true;
        
    }
    if (nodeB->getTag() == TAG_BUBBLE) {
        disBubble(nodeB);
        return true;
    }
    if (nodeA->getTag() == TAG_LINE ){
        //_balllayer->stopAllActions();
        auto point = nodeB->getPosition();
        CCLOG("rerunRound x = %f, y = %f",point.x,point.y);
        nodeB->removeFromParent();
        nodeA->removeFromParent();
        _balllayer->rerunRound(point);
        return true;
    }
    if (nodeB->getTag() == TAG_LINE ){
        //_balllayer->stopAllActions();
        
        auto point = nodeA->getPosition();
        nodeB->removeFromParent();
        nodeA->removeFromParent();
        CCLOG("rerunRound x = %f, y = %f",point.x,point.y);
        _balllayer->rerunRound(point);
        return true;
    }
    return true;
}

void GameLayer::disBubble(cocos2d::Node* node){
    node->removeFromParent();
    _disBubble++;
     SoundManager::playEffect(kBoomOgg);
    auto info = GameManager::getInstance()->getMapData(GameManager::getInstance()->getCurLevel());
    if(_disBubble == info.bubblePoints.size()){
        showWinLayer();
    }
}

void GameLayer::showWinLayer(){
    AdsHelp::showInterstitial();
    SoundManager::stopBackgroundMusic();
    SoundManager::playEffect(kVictoryOgg);
    GameManager::getInstance()->setLevelSuccess();
    _balllayer->stopRun();
    auto layer = WinLayer::create();
    getParent()->addChild(layer,kTouch);
}

void GameLayer::showLoseLayer(){
    AdsHelp::showInterstitial();
    SoundManager::stopBackgroundMusic();
    SoundManager::playEffect(kFailureOgg);
    auto layer = LoseLayer::create();
    getParent()->addChild(layer,kTouch);
}


void GameLayer::addBallLayer(){
    _balllayer = BallLayer::create();
    addChild(_balllayer);
    auto info = GameManager::getInstance()->getMapData(GameManager::getInstance()->getCurLevel());

    _balllayer->addBall(info.startPoint);
    _balllayer->setDelegate(this);
    
}

void GameLayer::addBubbleayer(){
    auto layer = BubbleLayer::create();
    addChild(layer);
    auto info = GameManager::getInstance()->getMapData(GameManager::getInstance()->getCurLevel());
    
    layer->addBubble(info.bubblePoints);
    
    
}

void GameLayer::addOriginLayer(){
    _originLayer = OriginLayer::create();
    addChild(_originLayer,kTouch);
    
    
    
}





void GameLayer::menuCallback(cocos2d::Ref* pSender){
    SoundManager::playEffect(kButtonOgg);
    DirectorManager::getInstance()->replaceScene(DirectorManager::SCENE_LEVEL);
}

void GameLayer::onTouchLayerButton(){
    _touchLayer->setBtnEnabled(false);
    if (_pileCount > 1) {
        _pileCount--;
        if (_pileCount == 1) {
            _touchLayer->showRunBtn();
        }
        _originLayer->setNext();
        SoundManager::playEffect(kNextOgg);

    }else if(_pileCount == 1){
        SoundManager::playEffect(kRunOgg);
        _balllayer->runRound();
        _bTouch = false;
        SoundManager::playBackgroundMusic(kRunBgOgg);
        _touchLayer->setBtnEnabled(false);
    }
    
}

void GameLayer::onTouchLayerTouch(cocos2d::Point point){
    if (!_bTouch) {
        return ;
    }
    _touchLayer->setBtnEnabled(true);
    SoundManager::playEffect(kPileOgg);
    auto info = GameManager::getInstance()->getMapData(GameManager::getInstance()->getCurLevel());
    if(_pileCount == info.pileCount){
        _balllayer->setOrigin(point);
        _originLayer->addOrigin(point);
    }else{
        _originLayer->addPile(point);
    }
    
}

void GameLayer::gameLose(){
    showLoseLayer();
}

