//
//  GameLayer.h
//  RunRound
//
//  Created by LinShulong on 15/11/22.
//
//

#ifndef __RunRound__GameLayer__
#define __RunRound__GameLayer__

#include "cocos2d.h"
#include "TouchLayerDelegate.h"
#include "BallLayerDelegate.h"
class BallLayer;
class OriginLayer;
class TouchLayer;
class GameLayer : public cocos2d::Layer , TouchLayerDelegate ,BallLayerDelegate
{
public:
    GameLayer();
    ~GameLayer();
    virtual bool init();
    void menuCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    virtual void onTouchLayerButton();
    virtual void onTouchLayerTouch(cocos2d::Point point);
    virtual void gameLose();
private:
    void addBallLayer();
    void addBubbleayer();
    void addOriginLayer();
    void showWinLayer();
    void showLoseLayer();
    void disBubble(cocos2d::Node* node);
private:
    BallLayer* _balllayer ;
    OriginLayer* _originLayer;
    TouchLayer* _touchLayer;
    int _disBubble; //消灭的bubble数
    int _pileCount; //剩余
    bool _bTouch;
};
#endif /* defined(__RunRound__GameLayer__) */
