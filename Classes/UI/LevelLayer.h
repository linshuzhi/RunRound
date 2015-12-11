//
//  LevelLayer.h
//  RunRound
//
//  Created by LinShulong on 15/11/18.
//
//

#ifndef __RunRound__LevelLayer__
#define __RunRound__LevelLayer__

#include "cocos2d.h"

class LevelLayer : public cocos2d::Layer
{
public:
    
    virtual bool init();

    void menuCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(LevelLayer);
    
};

#endif /* defined(__RunRound__LevelLayer__) */
