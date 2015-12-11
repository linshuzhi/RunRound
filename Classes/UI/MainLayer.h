//
//  MainLayer.h
//  RunRound
//
//  Created by LinShulong on 15/11/17.
//
//

#ifndef __RunRound__MainLayer__
#define __RunRound__MainLayer__
#include "cocos2d.h"
#include "../Manager/SoundManagerDelegate.h"
class MainLayer : public cocos2d::Layer , SoundManagerDelegate
{
public:
    MainLayer();
    ~MainLayer();
    virtual bool init();
    
    void menuAboutCallback(cocos2d::Ref* pSender);
    void menuPlayCallback(cocos2d::Ref* pSender);
    void menuSoundOffCallback(cocos2d::Ref* pSender);
    void menuSoundOnCallback(cocos2d::Ref* pSender);

    
    // implement the "static create()" method manually
    CREATE_FUNC(MainLayer);
    virtual void soundUpdate();
private:
    void updateSound();
    
private:
    cocos2d::MenuItemImage* _soundOffItem;
    cocos2d::MenuItemImage* _soundOnItem;
};
#endif /* defined(__RunRound__MainLayer__) */
