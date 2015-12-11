//
//  AdsHelp.cpp
//  RunRound
//
//  Created by LinShulong on 15/12/2.
//
//


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)



#include "AdsHelp.h"

#include "platform/android/jni/JniHelper.h"
#include "cocos2d.h"
USING_NS_CC;
bool AdsHelp::_showBanner = false;
void AdsHelp::showInterstitial()
{
    JniMethodInfo minfo;//定义Jni函数信息结构体
    //getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/cpp/AppActivity","showInterstitial","()V");
    
    if(!isHave) {
    }else{
        
        //调用此函数
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }

}

void AdsHelp::init(){
    _showBanner = false;
}

void AdsHelp::showBanner(){
    if(_showBanner){
        return;
    }else{
        _showBanner = true;
    }
    
    JniMethodInfo minfo;//定义Jni函数信息结构体
    //getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/cpp/AppActivity","showBanner","()V");
    
    if(!isHave) {
    }else{
        
        //调用此函数
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
    

}




#endif