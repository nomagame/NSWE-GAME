//
//  SuccessfulScene.h
//  NSWNGAME
//
//  Created by nancai on 14/12/25.
//
//

#ifndef __NSWNGAME__SuccessfulScene__
#define __NSWNGAME__SuccessfulScene__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
//主要是用来制造各个模式的最佳场景
class SuccessfulScene:public Scene
{
public:
    bool init() override;
    CREATE_FUNC(SuccessfulScene);
    
    static SuccessfulScene* createClassicsSuccessfulScene();
    static SuccessfulScene* createChallengeSuccessfulScene();
    static SuccessfulScene* createQuickSuccessfulScene();
    static SuccessfulScene* createEndlessSuccessfulScene();
    static SuccessfulScene* createAbnormalSuccessfulScene();
    void initSceneLabel();
    
    void backMainMenu(Ref* pSender);
    void retry(Ref* pSender);
    
    CC_SYNTHESIZE(std::string,gameMode, GameMode);
private:
    Label* gameModeLabel; //游戏模式标签
    Label* currGradeLabel;//当前分数标签
    Label* historyGradeLabel;//历史最佳标签
    Label* commentLabel;//评论标签
    
};
#endif /* defined(__NSWNGAME__SuccessfulScene__) */
