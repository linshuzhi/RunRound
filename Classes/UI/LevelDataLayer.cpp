//
//  LevelDataLayer.cpp
//  RunRound
//
//  Created by LinShulong on 15/11/18.
//
//

#include "LevelDataLayer.h"
#include "extensions/cocos-ext.h"
#include "cocos-ext.h"

#include "cocostudio/CocoStudio.h"
#include "../Manager/UserLevelManager.h"
#include "../Manager/GameManager.h"
#include "../Manager/SoundManager.h"
USING_NS_CC;
using namespace ui;
USING_NS_CC_EXT;


namespace  {
    const char* kBg = "level_dialog.png";
    const char * kButtonOgg = "sound/button.m4a";
}


LevelDataLayer::LevelDataLayer()
: _listView(nullptr)
{
    
}

LevelDataLayer::~LevelDataLayer(){
    
}
bool LevelDataLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto bg = Scale9Sprite::create(kBg);
    bg->setPosition(origin.x + visibleSize.width/ 2,origin.y + visibleSize.height / 2 + 50);
    auto bgSize = bg->getContentSize();
    //设置伸缩后的外框大小
    bg->setPreferredSize(Size(Vec2(visibleSize.width - 100, visibleSize.height - 300)));
    //bg伸缩后的内框大小
    bg->setCapInsets(Rect(100, 100, bgSize.width - 200, bgSize.height -200));
    addChild(bg);
    
    
    
    _listView = ListView::create();
    
    _listView->setDirection(ui::ScrollView::Direction::VERTICAL);
    
    _listView->setBounceEnabled(true);
    _listView->setColor(Color3B(255,255,255));
    _listView->setContentSize(Size(bg->getContentSize().width - 40, bg->getContentSize().height - 47));

    _listView->setPosition(Vec2(40,10));
    bg->addChild(_listView);
    


    updateData();
    return true;
}

void LevelDataLayer::updateData(){
    auto levelDatas = UserLevelManager::getInstance()->getLevelDatas();
    int row = 0;
    float scale = 0.2f;
    auto size = Sprite::create("level_min_bg.png")->getContentSize();
    float intervals = (_listView->getContentSize().width - 40 - size.width * 3 ) / 2;
    
    
    Layout* temp = nullptr;
    int colseIndex = 0;
    for(LevelData& info : levelDatas){
        int index = row % 3;
        if (index == 0) {
            temp = Layout::create();
            temp->setContentSize(Size(size.width * 3.0f + intervals * 2,size.height + 30));
            _listView->pushBackCustomItem(temp);
        }

        
        auto button = Button::create("level_min_bg.png");
        button->setPosition(Vec2(size.width / 2 + index * (intervals + size.width),0));
        temp->addChild(button);
        button->addTouchEventListener(CC_CALLBACK_2(LevelDataLayer::onTouchEvent, this));
        button->setTag(info.levelId);
        
        
        
        if(info.isSuccess){
            auto numLabel = Label::createWithCharMap("number_red.png", 90, 90, '0');
            numLabel->setScale(scale);
            numLabel->setString(StringUtils::format("%d",info.levelId));
            numLabel->setPosition(Vec2(size.width / 2,size.height / 2));
            button->addChild(numLabel);
        }
        
        
        if(!info.isSuccess){
            auto close = Sprite::create("level_min_close.png");
            close->setPosition(Vec2(size.width / 2,size.height / 2));
            button->addChild(close);
            button->setEnabled(false);
            if (colseIndex == 0) {
                colseIndex = row;
            }
        }
        

        row++;
    }
    
    temp = Layout::create();
    temp->setContentSize(Size(size.width * 3.0f + intervals * 2,size.height + 30));
    _listView->pushBackCustomItem(temp);
    
    
    float t = 0.0f;
    float line = (int)(levelDatas.size()+1) / 3 + 1;
    float index = (colseIndex)/ 3 - 1;
    float percent = index * 100 /(line - 5);
    if (percent < 0) {
        percent = 0;
    }
    if (percent > 100) {
        percent = 100;
    }
    auto act = Sequence::create(DelayTime::create(t),
                                CallFuncN::create([this,percent](Node* node){
        _listView->scrollToPercentVertical(percent, 0.0f, false);
    }),
                                nullptr
                                );
    
    this->runAction(act);
    
    
}


void LevelDataLayer::onTouchEvent(cocos2d::Ref *ref, Widget::TouchEventType touchType)
{

    
    if(touchType == Widget::TouchEventType::ENDED){
        auto button = dynamic_cast<Button*>(ref);
        int level = button->getTag();
        SoundManager::playEffect(kButtonOgg);
        GameManager::getInstance()->startLevel(level);
        CCLOG("on ended %d",level);
        
    }
    
}




