//
//  SoundManager.h
//  RunRound
//
//  Created by LinShulong on 15/11/16.
//
//

#ifndef __RunRound__SoundManager__
#define __RunRound__SoundManager__

#include <vector>
class SoundManagerDelegate;
class SoundManager{
public:
    static void setEffect(bool bAble);
    static void setMusic(bool bAble);
    
    static bool getMusic();
    static bool getEffect();
    
    static void updateData();
    
    
    static void addDelegate(SoundManagerDelegate* delegate);
    static void deleteDelegate(SoundManagerDelegate* delegate);
    
    
    static void playEffect(const char* filePath);
    static void stopBackgroundMusic();
    static void playBackgroundMusic(const char* filePath);
private:
    static std::vector<SoundManagerDelegate*> _delegates;
};

#endif /* defined(__RunRound__SoundManager__) */
