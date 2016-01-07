//
//  FailScene.h
//  NSWNGAME
//
//  Created by nancai on 14/12/23.
//
//

#ifndef __NSWNGAME__FailScene__
#define __NSWNGAME__FailScene__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class FailScene:public Scene
{
public:
    virtual bool init() override;
    CREATE_FUNC(FailScene);
    
    void backMainMenu(Ref* pSender);
    
    void retry(Ref* pSender);
    
    static FailScene* createClassicFailedScene();
    static FailScene* createChallengeFailedScene();
    
    CC_SYNTHESIZE(std::string, gameMode, GameMode);
    
    Label* upLabel;
    Label* midLabel;
    Label* downLabel;
    Label* commentLabel;
private:
  
   // Label* wbLabel;
};
#endif /* defined(__NSWNGAME__FailScene__) */
