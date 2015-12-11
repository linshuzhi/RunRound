//
//  AdsHelp.h
//  RunRound
//
//  Created by LinShulong on 15/12/2.
//
//

#ifndef AdsHelp_h
#define AdsHelp_h

class AdsHelp{
public:
    static void showInterstitial();
    static void showBanner();
    static void init();
private:
    static bool _showBanner;
};

#endif /* AdsHelp_h */
