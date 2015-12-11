//
//  OriginLayer.cpp
//  RunRound
//
//  Created by LinShulong on 15/11/24.
//
//

#include "OriginLayer.h"
#include "PhysicsBodyMask.h"

USING_NS_CC;
namespace  {
    const char * kPile = "pile.png";
}
OriginLayer::OriginLayer()
: _origin(nullptr)
, _pileLayer(nullptr)
{
    
}
OriginLayer::~OriginLayer()
{
    
}


bool OriginLayer::init(){
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    
    return true;
}

void OriginLayer::addOrigin(cocos2d::Point point){
    if (_origin) {
        _origin->removeFromParent();
        _origin = nullptr;
    }
    _origin = Sprite::create(kPile);//
    _origin->setPosition(point.x + 1,point.y + 15);
    addChild(_origin);
}

void OriginLayer::addPile(cocos2d::Point point){
    if (_pileLayer) {
        _pileLayer->removeFromParent();
        _pileLayer = nullptr;
    }
    
    _pileLayer = Node::create();
    _pileLayer->setTag(TAG_PILE);
    this->addChild(_pileLayer);
    auto body = PhysicsBody::createBox(Size(4,4));//(point, Point(point.x+1,point.y));
    body->setCategoryBitmask(MASK_LINE);
    body->setCollisionBitmask(MASK_LINE);
    body->setContactTestBitmask(MASK_LINE);
    auto bodyNode = Node::create();
    bodyNode->setPosition(point);
    bodyNode->setPhysicsBody(body);
    _pileLayer->addChild(bodyNode);
    
    
    
    auto origin = Sprite::create(kPile);
    origin->setPosition(point.x + 1,point.y + 15);
    _pileLayer->addChild(origin);



    
}

void OriginLayer::setNext(){
    _origin = nullptr;
    _pileLayer = nullptr;
}


