//
//  OriginLayer.h
//  RunRound
//
//  Created by LinShulong on 15/11/24.
//
//

#ifndef __RunRound__OriginLayer__
#define __RunRound__OriginLayer__
#include "cocos2d.h"

class OriginLayer : public cocos2d::Layer
{
public:
    OriginLayer();
    ~OriginLayer();
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(OriginLayer);
    
    void addOrigin(cocos2d::Point point);
    void addPile(cocos2d::Point point);
    void setNext();
private:
    cocos2d::Sprite* _origin;
    cocos2d::Node* _pileLayer;
};

#endif /* defined(__RunRound__OriginLayer__) */
