//
//  DirectorManager.h
//  RunRound
//
//  Created by LinShulong on 15/11/22.
//
//

#ifndef __RunRound__DirectorManager__
#define __RunRound__DirectorManager__

class DirectorManager{
public:
    enum TYPE_SCENE{
        SCENE_MAIN = 0,
        SCENE_LEVEL,
        SCENE_GAME
    };
public:
    DirectorManager();
    ~DirectorManager();
    static DirectorManager* getInstance();
    void replaceScene(TYPE_SCENE typeScene);
private:
    void init();
    
private:
    static DirectorManager* _instance;

};

#endif /* defined(__RunRound__DirectorManager__) */
