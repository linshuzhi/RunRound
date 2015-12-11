//
//  GameManager.h
//  RunRound
//
//  Created by LinShulong on 15/11/22.
//
//

#ifndef __RunRound__GameManager__
#define __RunRound__GameManager__
#include "MapModel.h"


class GameManager{
public:
    GameManager();
    ~GameManager();
    static GameManager* getInstance();
    
    void startLevel(int level);
    MapModel getMapData(int level);
    void toRealMapData(MapModel& info);
    int getCurLevel(){
        return _level;
    }
    void setLevelSuccess();
    void toBack();
    void toNext();
    void toReplay();
    MapModel readTmx(int level);
private:
    void init();

private:
    static GameManager* _instance;
    MapModel _mapInfo;
    int _level;
};

#endif /* defined(__RunRound__GameManager__) */
