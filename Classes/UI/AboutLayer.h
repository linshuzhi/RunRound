//
//  AboutLayer.h
//  LeftRight
//
//  Created by LinShulong on 15/10/27.
//
//

#ifndef __LeftRight__AboutLayer__
#define __LeftRight__AboutLayer__
#include "cocos2d.h"

class AboutLayer : public cocos2d::Layer
{
public:
    
    virtual bool init();
    void menuCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(AboutLayer);
    
};

#endif /* defined(__LeftRight__AboutLayer__) */
