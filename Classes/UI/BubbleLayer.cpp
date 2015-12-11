//
//  BubbleLayer.cpp
//  RunRound
//
//  Created by LinShulong on 15/11/24.
//
//

#include "BubbleLayer.h"
#include "PhysicsBodyMask.h"
#include "../Manager/MapModel.h"
USING_NS_CC;

namespace  {
    const char * kBubble = "bubble.png";
}
bool BubbleLayer::init(){
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    
    return true;
}

void BubbleLayer::addBubble(const std::vector<BubblePoint>& bubblePoints){
    for (const BubblePoint& info : bubblePoints) {
        auto bubble = Sprite::create(kBubble);
        bubble->setPosition(info.point);
        bubble->setTag(TAG_BUBBLE);
        bubble->setScale(info.scale);

        addChild(bubble);
        auto body = PhysicsBody::createCircle(bubble->getContentSize().width / 2);
        body->setCategoryBitmask(MASK_BALL);
        body->setCollisionBitmask(MASK_BALL);
        body->setContactTestBitmask(MASK_BALL);
        bubble->setPhysicsBody(body);
        
        if (info.moveLength > 0) {
            
            Size visibleSize = Director::getInstance()->getVisibleSize();
            Vec2 origin = Director::getInstance()->getVisibleOrigin();
            Vec2 f;
            f.x = origin.x +visibleSize.width / 2 - info.point.x;
            f.y = origin.y +visibleSize.height / 2 - info.point.y;
            f.normalize();
            f = f*info.moveLength;
            auto move = MoveBy::create(info.moveTime, f);
            auto back = MoveBy::create(info.moveTime, -f);
            auto s = Sequence::create(move,back,nullptr);
            auto r = RepeatForever::create(s);
            bubble->runAction(r);
        }
    }
}