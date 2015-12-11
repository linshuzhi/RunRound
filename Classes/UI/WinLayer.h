//
//  WinLayer.h
//  RunRound
//
//  Created by LinShulong on 15/11/25.
//
//

#ifndef __RunRound__WinLayer__
#define __RunRound__WinLayer__

#include "cocos2d.h"

class WinLayer : public cocos2d::Layer
{
public:
    WinLayer();
    ~WinLayer();
    virtual bool init();
    void menuNextCallback(cocos2d::Ref* pSender);
    void menuReplayCallback(cocos2d::Ref* pSender);
    void menuBackCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(WinLayer);

};
#endif /* defined(__RunRound__WinLayer__) */
