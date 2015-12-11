//
//  LoseLayer.h
//  RunRound
//
//  Created by LinShulong on 15/11/25.
//
//

#ifndef __RunRound__LoseLayer__
#define __RunRound__LoseLayer__
#include "cocos2d.h"

class LoseLayer : public cocos2d::Layer
{
public:
    LoseLayer();
    ~LoseLayer();
    virtual bool init();
    void menuNextCallback(cocos2d::Ref* pSender);
    void menuReplayCallback(cocos2d::Ref* pSender);
    void menuBackCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(LoseLayer);
    
};

#endif /* defined(__RunRound__LoseLayer__) */
