//
//  MainGameScene.h
//  NSWNGAME
//
//  Created by nancai on 14/12/21.
//
//

#ifndef __NSWNGAME__MainGameScene__
#define __NSWNGAME__MainGameScene__

#include <stdio.h>
#include "cocos2d.h"
#include "AppMacros.h"
#include "CommonPlayLayer.h"

USING_NS_CC;

class MainGameScene:public Scene
{
public:
    MainGameScene();
    ~MainGameScene();
    virtual bool init() override;
    void update(float dt);
    void backMainMenu(Ref* pSender);
    void retry(Ref* pSender);
    static MainGameScene* createClassicsScene();//创建经典模式
    static MainGameScene* createChallengeScene();// 创建挑战模式
    static MainGameScene* createQuickScene();//创建快速模式
    static MainGameScene* createEndlessScene();//创建无尽模式
    
    static MainGameScene* createAbnormalScene();//创建变态模式
    
    
    CREATE_FUNC(MainGameScene);
 //   CC_SYNTHESIZE(Label* , numLabel, NumLabel);//用来显示各个数字的
    CC_SYNTHESIZE(std::string,gameMode,GameMode);//主要是用来判断当前游戏模式
    CC_SYNTHESIZE(int,curPressTime, CurPressTime);//主要用来记录当前次数
    Label* fontLabel;
    Label* numLabel;
    float press_time;//按下的时间间隔
private:
    CommonPlayLayer* commonPlayLayer;
    float timeCount; //纪录当前游戏的时间
    float timeBackCount;//纪录游戏的倒计时


};
#endif /* defined(__NSWNGAME__MainGameScene__) */
