//
//  BallLayer.h
//  RunRound
//
//  Created by LinShulong on 15/11/24.
//
//

#ifndef __RunRound__BallLayer__
#define __RunRound__BallLayer__

#include "cocos2d.h"

class BallLayerDelegate;
class BallLayer : public cocos2d::Layer
{
public:
    BallLayer();
    ~BallLayer();
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(BallLayer);
    void addBall(cocos2d::Point point);
    void runRound();
    void setOrigin(cocos2d::Point point);
    
    void rerunRound(cocos2d::Point point);
    void setDelegate(BallLayerDelegate* delegate);
    void stopRun();
private:
    cocos2d::Point _ballPoint;
    cocos2d::DrawNode* _drawNode;
    cocos2d::Point _originPoint;
    cocos2d::Sprite* _ball;
    cocos2d::Layer* _runLayer;
    BallLayerDelegate* _delegate;
};

#endif /* defined(__RunRound__BallLayer__) */
