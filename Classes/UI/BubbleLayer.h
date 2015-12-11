//
//  BubbleLayer.h
//  RunRound
//
//  Created by LinShulong on 15/11/24.
//
//

#ifndef __RunRound__BubbleLayer__
#define __RunRound__BubbleLayer__
#include "cocos2d.h"
struct BubblePoint;
class BubbleLayer : public cocos2d::Layer
{
public:
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(BubbleLayer);
    void addBubble(const std::vector<BubblePoint>& bubblePoints);
};

#endif /* defined(__RunRound__BubbleLayer__) */
