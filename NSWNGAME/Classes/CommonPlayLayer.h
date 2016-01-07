//
//  CommonPlayLayer.h
//  NSWNGAME
//
//  Created by nancai on 14/12/21.
//
//

#ifndef __NSWNGAME__CommonPlayLayer__
#define __NSWNGAME__CommonPlayLayer__

#include <stdio.h>
#include"cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
class CommonPlayLayer:public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(CommonPlayLayer);
    void initDirectionMap();
    void spriteChangePosition(Sprite* oneSprite,Sprite* anotherSprite);
    void initAbnormalSceneDirection();
    virtual bool onTouchBegan(Touch* touch,Event* event);
    virtual void onTouchEnded(Touch* touch,Event* event);
private:
    Map<std::string ,Sprite*>directionMap;
    Sprite* WSSprite;//西南
    Sprite* SSprite;//南
    Sprite* ESSprite;//东南
    
    Sprite* WSprite;//西
    Sprite* ESprite;//东
    
    Sprite* WNSprite;//西北
    Sprite* NSprite;//北
    Sprite* ENSprite;//东北
    
    Sprite* midSprite;//中间的变化的精灵
    Label* directionLabel;//随机显示方向文字；
};
#endif /* defined(__NSWNGAME__CommonPlayLayer__) */
