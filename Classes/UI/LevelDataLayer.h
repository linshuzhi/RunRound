//
//  LevelDataLayer.h
//  RunRound
//
//  Created by LinShulong on 15/11/18.
//
//

#ifndef __RunRound__LevelDataLayer__
#define __RunRound__LevelDataLayer__
#include "cocos2d.h"
#include "ui/CocosGUI.h"


class LevelDataLayer : public cocos2d::Layer
{
public:
    LevelDataLayer();
    ~LevelDataLayer();
    virtual bool init();
    
    void onTouchEvent(cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType touchType);
    CREATE_FUNC(LevelDataLayer);
private:
    void updateData();
private:
    cocos2d::ui::ListView* _listView;
};

#endif /* defined(__RunRound__LevelDataLayer__) */
