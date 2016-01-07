//
//  MainMenuScene.h
//  NSWNGAME
//
//  Created by nancai on 14/12/26.
//
//

#ifndef __NSWNGAME__MainMenuScene__
#define __NSWNGAME__MainMenuScene__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class MainMenuScene:public Scene
{
public:
    virtual bool init() override;
    CREATE_FUNC(MainMenuScene);
    
    void classicsStart(Ref* pSender);
    void quickStart(Ref* pSender);
    void challengeStart(Ref* pSender);
    void endlessStart(Ref* pSender);
    void abnormalStart(Ref* pSender);
    
    void intoInstallScene(Ref* pSender);
    void endGame(Ref* pSender);
};

#endif /* defined(__NSWNGAME__MainMenuScene__) */
