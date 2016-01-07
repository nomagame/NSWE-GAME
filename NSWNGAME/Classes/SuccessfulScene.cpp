//
//  SuccessfulScene.cpp
//  NSWNGAME
//
//  Created by nancai on 14/12/25.
//
//

#include "SuccessfulScene.h"
#include "MainMenuScene.h"
#include "MainGameScene.h"
#include "AppMacros.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
bool SuccessfulScene::init()
{
    if(!Scene::init())
        return false;
    Sprite* bgSprite = Sprite::create("blueBg.png");
    bgSprite->setAnchorPoint(Point(0,0));
    addChild(bgSprite);
    
    gameModeLabel =Label::create(" ","Arial",TITLE_FONT_SIZE+20);
    gameModeLabel->setPosition(Point(135.0f,345.0f));
    addChild(gameModeLabel);
    
    currGradeLabel = Label::create(" ","Arial",TITLE_FONT_SIZE+40);
    currGradeLabel->setPosition(Point(135.0f,255.0f));
    addChild(currGradeLabel);

    historyGradeLabel= Label::create(" ","Arial",TITLE_FONT_SIZE-5);
    historyGradeLabel->setPosition(Point(135.0f,205.0f));
    addChild(historyGradeLabel);
    
    commentLabel= Label::create(" ","Arial",TITLE_FONT_SIZE-5);
    commentLabel->setPosition(Point(135.0f,170.0f));
    addChild(commentLabel);
    
    auto backItem= MenuItemImage::create("noBorderBack.png",
                                         "noBorderBack.png",
                                         CC_CALLBACK_1(SuccessfulScene::backMainMenu,this));
    backItem->setAnchorPoint(Point(0,0));
    backItem->setPosition(Point(20,0));
    
    auto retryItem = MenuItemImage::create("noBorderRetry.png",
                                           "noBorderRetry.png",
                                           CC_CALLBACK_1(SuccessfulScene::retry,this));
    retryItem->setAnchorPoint(Point(0,0));
    retryItem->setPosition(Point(180,0));
    
    auto menu=Menu::create(backItem,retryItem,NULL);
    menu->setPosition(Point(0,30));
    addChild(menu);

    return true;
}
//经典模式成功场景
SuccessfulScene* SuccessfulScene::createClassicsSuccessfulScene()
{
    SuccessfulScene* successfulScene = new SuccessfulScene();
    if(successfulScene&&successfulScene->init())
    {
        successfulScene->setGameMode("classics");
        successfulScene->initSceneLabel();
        return successfulScene;
    }else
    {
        delete successfulScene;
        return NULL;
    }
}
//挑战模式成功的场景
SuccessfulScene* SuccessfulScene::createChallengeSuccessfulScene()
{
    SuccessfulScene* successfulScene = new SuccessfulScene();
    if(successfulScene&&successfulScene->init())
    {
        successfulScene->setGameMode("challenge");
        successfulScene->initSceneLabel();
        return successfulScene;
        
    }else{
        delete successfulScene;
        return NULL;
    }
}
//快速模式结束的场景
SuccessfulScene* SuccessfulScene::createQuickSuccessfulScene()
{
    SuccessfulScene* successfulScene = new SuccessfulScene();
    if(successfulScene&&successfulScene->init())
    {
        successfulScene->setGameMode("quick");
        successfulScene->initSceneLabel();
        return successfulScene;
        
    }else{
        delete successfulScene;
        return NULL;
    }
    
}
//无尽模式结束的场景
SuccessfulScene* SuccessfulScene::createEndlessSuccessfulScene()
{
    SuccessfulScene* successfulScene = new SuccessfulScene();
    if(successfulScene&&successfulScene->init())
    {
        successfulScene->setGameMode("endless");
        successfulScene->initSceneLabel();
        return successfulScene;
        
    }else{
        delete successfulScene;
        return NULL;
    }

}
//变态模式结束的场景
SuccessfulScene* SuccessfulScene::createAbnormalSuccessfulScene()
{
    SuccessfulScene* successfulScene = new SuccessfulScene();
    if(successfulScene&&successfulScene->init())
    {
        successfulScene->setGameMode("abnormal");
        successfulScene->initSceneLabel();
        return successfulScene;
        
    }else{
        delete successfulScene;
        return NULL;
    }
    

}
void SuccessfulScene::initSceneLabel()
{
    std::string gameModeStr =  getGameMode();
    if(gameModeStr=="classics")//经典模式
    {
        char buf[10],buf2[20];
        float bestGrate=UserDefault::getInstance()->getFloatForKey("classicsBest",INT16_MAX);
        float curTime=GameManager::getInstance()->getCurTime();
       // gameModeLabel->setString("经典模式");
        gameModeLabel->setString("Classic Mode");
        sprintf(buf, "%.3f''",curTime);
        currGradeLabel->setString(buf);
        if(curTime>bestGrate){
           // sprintf(buf2, "历史最佳%.3f''",bestGrate);
            sprintf(buf2, "The best score of history is %.3f''",bestGrate);
            historyGradeLabel->setString(buf2);
        }else{
            UserDefault::getInstance()->setFloatForKey("classicsBest",curTime);
            //histortGradeLabel->setString("新纪录");
            historyGradeLabel->setString("New Record");
        }
        
    }else if(gameModeStr=="challenge")
    {
        int bestGrade =UserDefault::getInstance()->getIntegerForKey("challengeBest",0);
        int curPressTimes = GameManager::getInstance()->getPressTimes();
        //gameModeLabel->setString("挑战模式");
        gameModeLabel->setString("Arcade Mode");
        currGradeLabel->setString(std::to_string(curPressTimes));
        if(bestGrade>=curPressTimes){
            //historyGradeLabel->setString("历史最佳"+std::to_string(bestGrade));
            historyGradeLabel->setString("The best socre of history is "+std::to_string(bestGrade));
            if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
                SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("over.wav").c_str(), false);
        }else{
            UserDefault::getInstance()->setIntegerForKey("challengeBest",curPressTimes);
            historyGradeLabel->setString("New Record");
            //historyGradeLabel->setString("新纪录");
            if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
                SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("cheer.wav").c_str(), false);
        }
            
    }else if(gameModeStr=="quick")
    {
        int bestGrade =UserDefault::getInstance()->getIntegerForKey("quickBest",0);
        int curPressTimes = GameManager::getInstance()->getPressTimes();
        //gameModeLabel->setString("快速模式");
        gameModeLabel->setString("Quick Mode");
        currGradeLabel->setString(std::to_string(curPressTimes));
        if(bestGrade<curPressTimes){
            UserDefault::getInstance()->setIntegerForKey("quickBest",curPressTimes);
           // historyGradeLabel->setString("新纪录");
            historyGradeLabel->setString(("New Record"));
            if(UserDefault::getInstance()->getBoolForKey("voice_state",true)){
                SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("cheer.wav").c_str(), false);
            }

        }else{
            historyGradeLabel->setString("The best socre of history is "+std::to_string(bestGrade));
            //historyGradeLabel->setString("历史最佳"+std::to_string(bestGrade));
            if(UserDefault::getInstance()->getBoolForKey("voice_state",true)){
                SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("over.wav").c_str(), false);
            }
        }

    }else if(gameModeStr=="endless"){
        int bestGrade =UserDefault::getInstance()->getIntegerForKey("endlessBest",0);
        int curPressTimes = GameManager::getInstance()->getPressTimes();
        gameModeLabel->setString("无尽模式");
        currGradeLabel->setString(std::to_string(curPressTimes));
        if(bestGrade>=curPressTimes){
            historyGradeLabel->setString("历史最佳"+std::to_string(bestGrade));
            if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
                SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("over.wav").c_str(), false);
        }else{
            UserDefault::getInstance()->setIntegerForKey("endlessBest",curPressTimes);
            historyGradeLabel->setString("新纪录");
            if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
                SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("cheer.wav").c_str(), false);
            
        }
    }else if(gameModeStr=="abnormal"){
        int bestGrade =UserDefault::getInstance()->getIntegerForKey("abnormalBest",0);
        int curPressTimes = GameManager::getInstance()->getPressTimes();
        gameModeLabel->setString("Crazy Mode");
        currGradeLabel->setString(std::to_string(curPressTimes));
        if(bestGrade<curPressTimes){
            UserDefault::getInstance()->setIntegerForKey("abnormalBest",curPressTimes);
           // historyGradeLabel->setString("新纪录");
            historyGradeLabel->setString("New Record");
            if(UserDefault::getInstance()->getBoolForKey("voice_state",true)){
                SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("cheer.wav").c_str(), false);
            }
        }else{
            //historyGradeLabel->setString("历史最佳"+std::to_string(bestGrade));
            historyGradeLabel->setString("The best socre of history is "+std::to_string(bestGrade));
            if(UserDefault::getInstance()->getBoolForKey("voice_state",true)){
                SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("over.wav").c_str(), false);
            }
        }

    }
   // commentLabel->setString(commentsStr[(int)(CCRANDOM_0_1()*16)%16]);

}

void SuccessfulScene::backMainMenu(Ref* pSender)
{
    if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
        SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("click.wav").c_str(), false);
    Director::getInstance()->replaceScene(TransitionFade::create(0.1f, MainMenuScene::create()));
}
void SuccessfulScene::retry(Ref* pSender)
{
    if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
        SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("click.wav").c_str(), false);
    std::string gameMode = getGameMode();
    if(gameMode=="classics"){
        Director::getInstance()->replaceScene(TransitionFade::create(0.1f, MainGameScene::createClassicsScene()));
    }else if(gameMode=="challenge"){
        Director::getInstance()->replaceScene(TransitionFade::create(0.1f, MainGameScene::createChallengeScene()));
    }else if(gameMode=="quick"){
        Director::getInstance()->replaceScene(TransitionFade::create(0.1f, MainGameScene::createQuickScene()));
    }else if(gameMode=="endless"){
        Director::getInstance()->replaceScene(TransitionFade::create(0.1f, MainGameScene::createEndlessScene()));
    }else if(gameMode=="abnormal"){
        Director::getInstance()->replaceScene(TransitionFade::create(0.1f, MainGameScene::createAbnormalScene()));
    }
  
}