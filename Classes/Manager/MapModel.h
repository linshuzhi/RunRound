//
//  MapModel.h
//  RunRound
//
//  Created by LinShulong on 15/11/23.
//
//

#ifndef __RunRound__MapModel__
#define __RunRound__MapModel__

#include "cocos2d.h"
#include <vector>

struct BubblePoint {
    float moveLength;
    float moveTime;
    float scale;
    cocos2d::Point point;
    
    BubblePoint(){
        moveLength = 0;
        moveTime = 0;
        scale = 1;
    }
};
struct MapModel {
    int level;
    int pileCount;
    cocos2d::Point startPoint;
    std::vector<BubblePoint> bubblePoints;
    MapModel(){
        level = 0;
        pileCount = 0;
    }
    
};

#endif /* defined(__RunRound__MapModel__) */
