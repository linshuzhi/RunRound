//
//  UserLevelManager.h
//  RunRound
//
//  Created by LinShulong on 15/11/18.
//
//

#ifndef __RunRound__UserLevelManager__
#define __RunRound__UserLevelManager__

#include "MapModel.h"
#include <vector>


struct LevelData {
    int levelId;        //第几关
    bool isSuccess;     //是否已经通关
};

class UserLevelManager {
public:
    UserLevelManager();
    ~UserLevelManager();
    static UserLevelManager* getInstance();
    void init();
    std::vector<LevelData>& getLevelDatas();
    void setLevelSuccess(int level);
    int getLastLevelSuccess();
private:
    static UserLevelManager* _instance;
    std::vector<LevelData> _levelDatas;
};

#endif /* defined(__RunRound__UserLevelManager__) */
