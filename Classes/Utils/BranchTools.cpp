//
//  BranchTools.cpp
//  RunRound
//
//  Created by LinShulong on 15/11/26.
//
//

#include "BranchTools.h"


namespace BranchTools {
    int getRand(int begin,int end){
        static bool bInit = false;
        if (!bInit) {
            bInit = true;
            srand((unsigned int)time(0));
        }
        if (end - begin <= 1) {
            return begin;
        }
        return rand() % (end - begin) + begin;
    }
}