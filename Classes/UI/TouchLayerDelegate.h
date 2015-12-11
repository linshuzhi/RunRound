//
//  TouchLayerDelegate.h
//  RunRound
//
//  Created by LinShulong on 15/11/24.
//
//

#ifndef __RunRound__TouchLayerDelegate__
#define __RunRound__TouchLayerDelegate__

#include "cocos2d.h"

class TouchLayerDelegate{
public:
    virtual void onTouchLayerButton() = 0;
    virtual void onTouchLayerTouch(cocos2d::Point point) = 0;
};

#endif /* defined(__RunRound__TouchLayerDelegate__) */
