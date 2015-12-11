//
//  AdsHelp.mm
//  RunRound
//
//  Created by LinShulong on 15/12/2.
//
//
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "AdsHelp.h"
#include "AppController.h"

bool AdsHelp::_showBanner = false;
void AdsHelp::showInterstitial()
{
//    static int count = 0;
//    count++;
//    if (count <= 3) {
//        return ;
//    }else{
//        count = 0;
//    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //iOS代码
    [AppController showInterstitial];

#else
    //Android代码
#endif
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
    

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //iOS代码
    [AppController showBanner];
    
#else
    //Android代码
#endif
}

#endif