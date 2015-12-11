//
//  BallLayer.cpp
//  RunRound
//
//  Created by LinShulong on 15/11/24.
//
//

#include "BallLayer.h"
#include "PhysicsBodyMask.h"
#include "BallLayerDelegate.h"
USING_NS_CC;


namespace  {
    const char * kBall = "ball.png";
}

BallLayer::BallLayer()
: _ballPoint(0,0)
, _originPoint(0,0)
, _drawNode(nullptr)
, _ball(nullptr)
, _runLayer(nullptr)
, _delegate(nullptr)
{
    
}

BallLayer::~BallLayer(){
    
}

bool BallLayer::init(){
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    _runLayer = Layer::create();
    addChild(_runLayer);
    //_runLayer->addChild(LayerColor::create(Color4B(255,0,0,100)));
    
    return true;
}

void BallLayer::addBall(cocos2d::Point point){
    _ballPoint = point;
    _ball = Sprite::create(kBall);
    _ball->setTag(TAG_BALL);
    
    auto body = PhysicsBody::createCircle(_ball->getContentSize().width / 3);
    
    body->setCategoryBitmask(MASK_BALL);
    body->setCollisionBitmask(MASK_BALL);
    body->setContactTestBitmask(MASK_BALL);
    _ball->setPhysicsBody(body);
    
    _runLayer->addChild(_ball,1);
    _ball->setPosition(point);
    

        //runAction(RotateBy::create(10.0f, -720));
}

void BallLayer::runRound(){
    
    auto act = Sequence::create(RotateBy::create(5.0f, -360),
                                CallFuncN::create([this](Node* node){
        if (_delegate) {
            _delegate->gameLose();
        }
    }),
                                nullptr
                                );
    _runLayer->runAction(act);
}


void BallLayer::setOrigin(cocos2d::Point point){
    _originPoint = point;
    if (_drawNode) {
        _drawNode->removeFromParent();
        _drawNode = nullptr;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _drawNode = DrawNode::create();
    _drawNode->setTag(TAG_LINE);
    _runLayer->addChild(_drawNode);
    auto body = PhysicsBody::createEdgeSegment(point, _ballPoint);
    body->setCategoryBitmask(MASK_LINE);
    body->setCollisionBitmask(MASK_LINE);
    body->setContactTestBitmask(MASK_LINE);
    _drawNode->setPhysicsBody(body);
    
    _drawNode->drawSegment(point, _ballPoint, 1, Color4F(0, 0, 0, 1));
   

    _runLayer->setAnchorPoint(Vec2(
                              point.x / (visibleSize.width + origin.x + origin.x),
                              point.y / (visibleSize.height+ origin.y + origin.y)
                              ));
    
}

void BallLayer::rerunRound(cocos2d::Point point){
    
    auto drawNode = DrawNode::create();
    addChild(drawNode);
    drawNode->drawSegment(point, _originPoint, 1, Color4F(0, 0, 0, 1));
    
    
    _runLayer->stopAllActions();
    _ballPoint = _runLayer->convertToWorldSpace(_ballPoint);
    _runLayer->removeFromParent();
    _drawNode = nullptr;
    _runLayer = nullptr;
    _runLayer = Layer::create();
    //_runLayer->addChild(LayerColor::create(Color4B(255,0,0,100)));
    addChild(_runLayer);
    CCLOG("_ballPoint x = %f, y = %f",_ballPoint.x,_ballPoint.y);
    addBall(_ballPoint);
    setOrigin(point);
    
    float t = 0.0f;
    
    auto act = Sequence::create(DelayTime::create(t),
                                CallFuncN::create([this](Node* node){
        CCLOG("_ball x = %f, y = %f",_ball->getPositionX(),_ball->getPositionY());
        _ball->setPosition(_ballPoint);
        runRound();
    }),
                                nullptr
                                );
    
    _ball->runAction(act);
    //;
//    CCLOG("befor x = %f, y = %f",point.x,point.y);
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//    point = _runLayer->convertToNodeSpace(point);
//    CCLOG("after x = %f, y = %f",point.x,point.y);
//    _runLayer->setAnchorPoint(Vec2(
//                              0 / (visibleSize.width + origin.x + origin.x),
//                              0 / (visibleSize.height+ origin.y + origin.y)
//                              ));
//    runAction(RotateBy::create(5.0f, -360));
//    auto drawNode = DrawNode::create();
//    drawNode->drawSegment(point, _originPoint, 1, Color4F(0, 0, 0, 1));
//    this->addChild(drawNode);
//    _ballPoint = _ball->getPosition();
//    setOrigin(point);
//    runRound();
}
void BallLayer::setDelegate(BallLayerDelegate* delegate){
    _delegate = delegate;
}

void BallLayer::stopRun(){
    _runLayer->stopAllActions();
}



