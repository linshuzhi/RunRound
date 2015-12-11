//
//  TouchLayer.h
//  RunRound
//
//  Created by LinShulong on 15/11/22.
//
//

#ifndef __RunRound__TouchLayer__
#define __RunRound__TouchLayer__

#include "cocos2d.h"

class TouchLayerDelegate;
class TouchLayer : public cocos2d::Layer
{
public:
    TouchLayer();
    ~TouchLayer();
    virtual bool init();
    void menuCallback(cocos2d::Ref* pSender);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    // implement the "static create()" method manually
    CREATE_FUNC(TouchLayer);
    void setDelegate(TouchLayerDelegate* delegate);
    void showRunBtn();
    void setBtnEnabled(bool bEnabled);
private:
    TouchLayerDelegate* _delegate;
    cocos2d::Label* _buttonlabel;
    cocos2d::MenuItemImage* _btnItem;
};

#endif /* defined(__RunRound__TouchLayer__) */
