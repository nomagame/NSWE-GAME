//
//  GameManager.h
//  NSWNGAME
//
//  Created by nancai on 14/12/25.
//
//

#ifndef __NSWNGAME__GameManager__
#define __NSWNGAME__GameManager__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class GameManager
{
public:
    CC_SYNTHESIZE(float, curTime,CurTime);//游戏时间
    CC_SYNTHESIZE(int, pressTimes, PressTimes);//按下的次数
    void init();
    void clear();
    static GameManager* getInstance();
private:
    static GameManager* instance;
};
#endif /* defined(__NSWNGAME__GameManager__) */
