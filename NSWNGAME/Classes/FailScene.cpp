//
//  FailScene.cpp
//  NSWNGAME
//
//  Created by nancai on 14/12/23.
//
//

#include "FailScene.h"
#include "MainGameScene.h"
#include "GameManager.h"
#include "MainMenuScene.h"
#include "AppMacros.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;


bool FailScene::init()
{
    if(!Scene::init())
        return false;
    Size winSize = Director::getInstance()->getWinSize();
    
    Sprite* bgSprite = Sprite::create("blueBg.png");
    bgSprite->setAnchorPoint(Point(0,0));
    bgSprite->setPosition(Point(0,0));
    addChild(bgSprite);
    upLabel=Label::create(" ","Arial",TITLE_FONT_SIZE+20);
    upLabel->setPosition(Point(winSize.width/2,winSize.height*3/4+30));
    addChild(upLabel);
    
   // midLabel =Label::create(" ","Arial",TITLE_FONT_SIZE+40);
    midLabel =Label::create(" ","Arial",TITLE_FONT_SIZE+20);
    midLabel->setPosition(Point(winSize.width/2,winSize.height/2+40));
    addChild(midLabel);
    
    downLabel = Label::create(" ","Arial",TITLE_FONT_SIZE);
    downLabel->setPosition(Point(winSize.width/2,winSize.height/2-5));
    addChild(downLabel);
    commentLabel = Label::create(" ","Arial",TITLE_FONT_SIZE-5);
    commentLabel->setPosition(Point(winSize.width/2,winSize.height/2-40));
    addChild(commentLabel);
    auto backItem= MenuItemImage::create("noBorderBack.png",
                                        "noBorderBack.png",
                                         CC_CALLBACK_1(FailScene::backMainMenu,this));
    backItem->setAnchorPoint(Point(0,0));
    backItem->setPosition(Point(20,0));
    
    auto retryItem = MenuItemImage::create("noBorderRetry.png",
                                           "noBorderRetry.png",
                                           CC_CALLBACK_1(FailScene::retry,this));
    retryItem->setAnchorPoint(Point(0,0));
    retryItem->setPosition(Point(180,0));
    
    auto menu=Menu::create(backItem,retryItem,NULL);
    menu->setPosition(Point(0,30));
    addChild(menu);
    
    return true;
}
//经典模式失败场景
FailScene* FailScene::createClassicFailedScene()
{
    FailScene* failScene = new FailScene();
    if(failScene&&failScene->init())
    {
        failScene->setGameMode("classics");
        //failScene->midLabel->setString("游戏失败");
        failScene->midLabel->setString("Game Over!");
        failScene->commentLabel->setString(commentsStr[(int)(CCRANDOM_0_1()*16)%16]);
        return failScene;
        
    }else{
        delete failScene;
        return NULL;
    }
}

//挑战模式失败场景
FailScene* FailScene::createChallengeFailedScene()
{
    FailScene* failScene = new FailScene();
    if(failScene&&failScene->init())
    {
        failScene->setGameMode("challenge");
        //failScene->upLabel->setString("挑战模式");
        failScene->upLabel->setString("Arcade Mode");
        int curPressTimes=GameManager::getInstance()->getPressTimes();
        failScene->midLabel->setString(std::to_string(curPressTimes));
        int bestGrade =UserDefault::getInstance()->getIntegerForKey("challengeBest",0);
        if(bestGrade>=curPressTimes){
            failScene->downLabel->setString("The best score of history is "+std::to_string(bestGrade));
        }else{
            UserDefault::getInstance()->setIntegerForKey("challengeBest",curPressTimes);
            failScene->downLabel->setString("New Record");
        }
      //  failScene->commentLabel->setString(commentsStr[(int)(CCRANDOM_0_1()*16)%16]);
        return failScene;
    }else{
        delete failScene;
        return NULL;
    }
}
void FailScene::backMainMenu(Ref* pSender)
{
    if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
        SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("click.wav").c_str(), false);

    Director::getInstance()->replaceScene(TransitionFade::create(0.1f, MainMenuScene::create()));
}

void FailScene::retry(Ref* pSender)
{
    if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
        SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("click.wav").c_str(), false);
    std::string gameMode = getGameMode();
    if(gameMode=="classics")
    {
        Director::getInstance()->replaceScene(TransitionFade::create(0.1f, MainGameScene::createClassicsScene()));
    }else if(gameMode=="challenge"){
        Director::getInstance()->replaceScene(TransitionFade::create(0.1f, MainGameScene::createChallengeScene()));
    }
    
}