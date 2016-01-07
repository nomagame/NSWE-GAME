//
//  InstallScene.h
//  NSWNGAME
//
//  Created by nancai on 14/12/27.
//
//

#ifndef __NSWNGAME__InstallScene__
#define __NSWNGAME__InstallScene__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class InstallScene :public Scene
{
public:
    virtual bool init() override;
    CREATE_FUNC(InstallScene);
    
    void changeVoiceState(Ref* pSender);
    
    void interAboutScene(Ref* pSender);
    
    void interHelpScene(Ref* pSender);
    
    void backToMainMenuScene(Ref* pSender);

    void backToInstallScene(Ref* pSender);
private:
    Sprite* voiceStateSprite;
};
#endif /* defined(__NSWNGAME__InstallScene__) */
