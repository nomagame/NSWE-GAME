//
//  MainGameScene.cpp
//  NSWNGAME
//
//  Created by nancai on 14/12/21.
//
//

#include "MainGameScene.h"
#include "SuccessfulScene.h"
#include "MainMenuScene.h"
#include "MainGameScene.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#define PASS_TIMES 20
#define GAME_TIME_LIMITED 10.0
#define QUICK_PRESS_TIME_LIMITED 1.0
#define ENDLESS_PRESS_TIME_LIMITED 2.0
#define ABNORMAL_PRESS_TIME_LIMITED 1.0
MainGameScene::MainGameScene()
{
    
}
MainGameScene::~MainGameScene()
{
    
}
bool MainGameScene::init()
{
    if(!Scene::init())
    {
        return false;
    }
    setCurPressTime(0);
    timeCount=0.0f;
    press_time=0.0;
    timeBackCount=GAME_TIME_LIMITED;
    
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("cheer.wav" ).c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("over.wav" ).c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("click.wav" ).c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("error.wav" ).c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("start.wav" ).c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("touch.wav" ).c_str());
    //添加顶上的一个层
    Layer * topLayer = Layer::create();
    topLayer->setPosition(Point(0,390));
    Sprite* topSprite = Sprite::create("top.png");
    topSprite->setAnchorPoint(Point(0,0));
    topLayer->addChild(topSprite);
    addChild(topLayer);
    
    //添加顶部标签
    
    fontLabel = Label::create(" ","Arial",TITLE_FONT_SIZE);
    fontLabel->setPosition(Point(135.0f,67.5f));
    topLayer->addChild(fontLabel);
    
    numLabel=Label::create(" ","Arial",TITLE_FONT_SIZE);
    numLabel->setPosition(Point(135.0f,22.5f));
    topLayer->addChild(numLabel);

    
    commonPlayLayer = CommonPlayLayer::create();
    commonPlayLayer->setPosition(Point(0.0f,120.0f));
    addChild(commonPlayLayer);
  
    
    // auto test = MenuItemImage::create("noBorderBack.png");
    auto* backItem= MenuItemImage::create("back.png",
                                           "backAction.png",
                                           CC_CALLBACK_1(MainGameScene::backMainMenu,this));
    backItem->setAnchorPoint(Point(0,0));
    backItem->setPosition(Point(0,0));
    
    auto* nullItem= MenuItemImage::create("blueCube.png","blueCube.png");
    nullItem->setAnchorPoint(Point(0,0));
    nullItem->setPosition(Point(90,0));
    

    auto retryItem = MenuItemImage::create("retry.png","retryAction.png",CC_CALLBACK_1(MainGameScene::retry,this));
    retryItem->setAnchorPoint(Point(0,0));
    retryItem->setPosition(Point(180,0));
     
    auto menu=Menu::create(backItem,nullItem,retryItem,NULL);
    menu->setPosition(Point(0,30));
    addChild(menu);
    
    Sprite* blogSprite = Sprite::create("blog.png");
    blogSprite->setAnchorPoint(Point(0,0));
    addChild(blogSprite);
    return true;
}
//经典模式场景设置
MainGameScene* MainGameScene::createClassicsScene()
{
    MainGameScene* classicsScene = new MainGameScene();
    if(classicsScene&&classicsScene->init())
    {
        classicsScene->setGameMode("classics");
        
        //加载经典模式所需要的层
        classicsScene->fontLabel->setString(std::to_string(PASS_TIMES));
        classicsScene->numLabel->setString("0.000''");
        classicsScene->schedule(schedule_selector(MainGameScene::update),0.1f);
    
        
        return classicsScene;
        
    }else{
        delete classicsScene;
        return NULL;
    }
    
}

//挑战模式场景设置
MainGameScene* MainGameScene::createChallengeScene()
{
    MainGameScene* challengeScene = new MainGameScene();
    if(challengeScene&&challengeScene->init())
    {
        challengeScene->setGameMode("challenge");
        
        //challengeScene->fontLabel->setString("倒计时");
        challengeScene->fontLabel->setString("Timer");
        char buf[10];
        sprintf(buf, "%.3f''", GAME_TIME_LIMITED);
        challengeScene->numLabel->setString(buf);
        challengeScene->schedule(schedule_selector(MainGameScene::update),0.1f);
        return challengeScene;
        
    }else{
        delete challengeScene;
        return NULL;
    }
}

//快速模式场景设置
MainGameScene* MainGameScene::createQuickScene()
{
    MainGameScene* quickScene = new MainGameScene();
    if(quickScene&&quickScene->init())
    {
        quickScene->setGameMode("quick");
        //quickScene->fontLabel->setString("得分");
        quickScene->fontLabel->setString("Score");
        quickScene->numLabel->setString("0");
        quickScene->schedule(schedule_selector(MainGameScene::update),0.1f);
        return quickScene;
        
    }else{
        delete quickScene;
        return NULL;
    }
    
}

//创建无尽模式
MainGameScene* MainGameScene::createEndlessScene()
{
    MainGameScene* endlessScene= new MainGameScene();
    if(endlessScene&&endlessScene->init())
    {
        endlessScene->setGameMode("endless");
        //endlessScene->fontLabel->setString("得分");
        endlessScene->fontLabel->setString("Score");
        endlessScene->numLabel->setString("0");
        endlessScene->schedule(schedule_selector(MainGameScene::update),0.1f);
        
        return endlessScene;
    }else{
        delete endlessScene;
        return NULL;
    }
}

//创建变态模式

MainGameScene * MainGameScene::createAbnormalScene()
{
    MainGameScene* abnormalScene = new MainGameScene();
    if(abnormalScene&&abnormalScene->init())
    {
        abnormalScene->setGameMode("abnormal");
        abnormalScene->commonPlayLayer->initAbnormalSceneDirection();
        //abnormalScene->fontLabel->setString("得分");
        abnormalScene->fontLabel->setString("Score");
        abnormalScene->numLabel->setString("0");
        abnormalScene->schedule(schedule_selector(MainGameScene::update),0.1f);
        return abnormalScene;
        
    }else{
        delete abnormalScene;
        return NULL;
    }

}
void MainGameScene::update(float dt)
{
    //log("%f",dt);
    press_time+=dt;
    std::string mode = getGameMode();
    bool voice_state=UserDefault::getInstance()->getBoolForKey("voice_state",true);
    if(mode=="classics"&&getCurPressTime()>0)
    {
      
        timeCount+=dt;
        char buf[10];
        sprintf(buf, "%.3f''", timeCount);
        numLabel->setString(buf);
        fontLabel->setString(std::to_string(PASS_TIMES-getCurPressTime()));
        if(getCurPressTime()==PASS_TIMES){
            //log("Success! You passed using time is %s",buf);
            GameManager::getInstance()->setCurTime(timeCount);
            this->unschedule(schedule_selector(MainGameScene::update));
            Director::getInstance()->replaceScene(TransitionFade::create(0.1f, SuccessfulScene::createClassicsSuccessfulScene()));
            
            if(voice_state)
                SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("cheer.wav").c_str(), false);
        }
       
    }else if(mode=="challenge"&&getCurPressTime()>0){
        timeBackCount-=dt;
        if(timeBackCount<0)
            timeBackCount=0;
        char buf[10];
        sprintf(buf, "%.3f''", timeBackCount);
        numLabel->setString(buf);
        if(timeBackCount<=0)
        {
            GameManager::getInstance()->setPressTimes(getCurPressTime());
            this->unschedule(schedule_selector(MainGameScene::update));
            Director::getInstance()->replaceScene(TransitionFade::create(0.1f,SuccessfulScene::createChallengeSuccessfulScene()));

        }
    }else if(mode =="quick"){
        numLabel->setString(std::to_string(getCurPressTime()));
        if(press_time>QUICK_PRESS_TIME_LIMITED&&getCurPressTime()>0){//超出反应的时间
            GameManager::getInstance()->setPressTimes(getCurPressTime());
            Director::getInstance()->replaceScene(TransitionFade::create(0.1f,SuccessfulScene::createQuickSuccessfulScene()));
        }
    }else if(mode =="endless"){
        numLabel->setString(std::to_string(getCurPressTime()));
        if(press_time>ENDLESS_PRESS_TIME_LIMITED&&getCurPressTime()>0){//超出反应的时间
            GameManager::getInstance()->setPressTimes(getCurPressTime());
            Director::getInstance()->replaceScene(TransitionFade::create(0.1f,SuccessfulScene::createEndlessSuccessfulScene()));
        }
    }else if(mode=="abnormal"){
        numLabel->setString(std::to_string(getCurPressTime()));
        if(press_time>ABNORMAL_PRESS_TIME_LIMITED&&getCurPressTime()>0){//超出反应的时间
            GameManager::getInstance()->setPressTimes(getCurPressTime());
            Director::getInstance()->replaceScene(TransitionFade::create(0.1f,SuccessfulScene::createAbnormalSuccessfulScene()));
        }

    }
   // log("time is %f",timeCount);
    
}

void MainGameScene::backMainMenu(Ref* pSender)
{
    if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
        SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("click.wav").c_str(), false);

    Director::getInstance()->replaceScene(TransitionFade::create(0.1f, MainMenuScene::create()));

}
void MainGameScene::retry(Ref* pSender)
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
    }else if(gameMode =="abnormal"){
         Director::getInstance()->replaceScene(TransitionFade::create(0.1f, MainGameScene::createAbnormalScene()));

    }
   
}