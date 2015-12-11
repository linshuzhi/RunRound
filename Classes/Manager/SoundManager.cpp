//
//  SoundManager.cpp
//  RunRound
//
//  Created by LinShulong on 15/11/16.
//
//

#include "SoundManager.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "SoundManagerDelegate.h"
USING_NS_CC;
using namespace CocosDenshion;

namespace  {
    const char* kEffectsKey = "EFFECTS_KEY";
    const char* kMusicKey = "MUSIC_KEY";
}


std::vector<SoundManagerDelegate*> SoundManager::_delegates;

void SoundManager::setEffect(bool bAble){
    bool able = getMusic();
    if (bAble == able) {
        return;
    }else{
        UserDefault::getInstance()->setBoolForKey(kEffectsKey, bAble);
        UserDefault::getInstance()->flush();
        updateData();
    }
}


void SoundManager::setMusic(bool bAble){
    bool able = getMusic();
    if (bAble == able) {
        return;
    }else{
        UserDefault::getInstance()->setBoolForKey(kMusicKey, bAble);
        UserDefault::getInstance()->flush();
        updateData();
    }
}

bool SoundManager::getMusic(){
    return UserDefault::getInstance()->getBoolForKey(kMusicKey,true);
}
bool SoundManager::getEffect(){
    return UserDefault::getInstance()->getBoolForKey(kEffectsKey,true);
}

void SoundManager::updateData(){
    if(!getMusic()){
        stopBackgroundMusic();
    }
    
    for(SoundManagerDelegate* delegate : _delegates){
        delegate->soundUpdate();
    }
}


void SoundManager::addDelegate(SoundManagerDelegate* delegate){
    _delegates.push_back(delegate);
}


void SoundManager::deleteDelegate(SoundManagerDelegate* delegate){
    for (std::vector<SoundManagerDelegate*>::iterator iter = _delegates.begin(); iter != _delegates.end(); iter++) {
        if (delegate == *iter) {
            _delegates.erase(iter);
            return;
        }
    }
}


void SoundManager::playEffect(const char* filePath){
    bool bAble = getEffect();
    if (!bAble) {
        return ;
    }
    auto fullpath = FileUtils::getInstance()->fullPathForFilename(filePath);
    SimpleAudioEngine::getInstance()->playEffect(fullpath.c_str());
}
void SoundManager::stopBackgroundMusic(){
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
void SoundManager::playBackgroundMusic(const char* filePath){
    bool bAble = getMusic();
    if (!bAble) {
        return ;
    }
    auto fullpath = FileUtils::getInstance()->fullPathForFilename(filePath);
    SimpleAudioEngine::getInstance()->playBackgroundMusic(fullpath.c_str(),true);
}

