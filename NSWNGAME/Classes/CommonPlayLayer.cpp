//
//  CommonPlayLayer.cpp
//  NSWNGAME
//
//  Created by nancai on 14/12/21.
//
//

#include "CommonPlayLayer.h"
#include "MainGameScene.h"
#include "GameManager.h"
#include "SuccessfulScene.h"
#include "FailScene.h"
#include "AppMacros.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
//static Map <String ,Sprite* >directionMap;
//static std::string directionFont[12]={"东","南","西","北","东南","南东","西南","南西","西北","北西","东北","北东"};
static std::string directionFont[12]={"East","South","West","North","Southeast","Eastsouth","Westsouth","Southwest","Westnorth","Northwest","Eastnorth","Northeast"};

bool CommonPlayLayer::init()
{
    if(!Layer::init())
        return false;
    
    //初始化八个精灵
    WSSprite= Sprite::create("WS.png");
    WSSprite->setAnchorPoint(Point(0,0));
    WSSprite->setPosition(Point(0,0));
    WSSprite->setName("WS");
    addChild(WSSprite,-1);
    
    SSprite=Sprite::create("S.png");
    SSprite->setAnchorPoint(Point(0,0));
    SSprite->setPosition(Point(90.0f,0.0f));
    SSprite->setName("S");
    addChild(SSprite,-1);
    
    ESSprite=Sprite::create("ES.png");
    ESSprite->setAnchorPoint(Point(0,0));
    ESSprite->setPosition(Point(90.0f*2,0));
    ESSprite->setName("ES");
    addChild(ESSprite);
    
    WSprite =Sprite::create("W.png");
    WSprite->setAnchorPoint(Point(0,0));
    WSprite->setPosition(Point(0,90.0f));
    WSprite->setName("W");
    addChild(WSprite);
    
    ESprite= Sprite::create("E.png");
    ESprite->setAnchorPoint(Point(0,0));
    ESprite->setPosition(Point(90.0*2,90.0));
    ESprite->setName("E");
    addChild(ESprite);
    
    WNSprite=Sprite::create("WN.png");//西北
    WNSprite->setAnchorPoint(Point(0,0));
    WNSprite->setPosition(Point(0,90.0*2));
    WNSprite->setName("WN");
    addChild(WNSprite);
    
    NSprite=Sprite::create("N.png");//北
    NSprite->setAnchorPoint(Point(0,0));
    NSprite->setPosition(Point(90.0,90.0*2));
    NSprite->setName("N");
    addChild(NSprite);
    
    ENSprite=Sprite::create("EN.png");;//东北
    ENSprite->setAnchorPoint(Point(0,0));
    ENSprite->setPosition(Point(90.0*2,90.0*2));
    ENSprite->setName("EN");
    addChild(ENSprite);
    
    midSprite=Sprite::create("whiteCube.png");
    midSprite->setAnchorPoint(Point(0,0));
    midSprite->setPosition(Point(90.0,90.0 ));
    addChild(midSprite);
    
    directionLabel = Label::create(" ","Arial",TITLE_FONT_SIZE-5);
    directionLabel->setColor(ccc3(68,152,200));
    int rondom=(int)(CCRANDOM_0_1()*12)%12;
    directionLabel->setString(directionFont[rondom]);
    directionLabel->setPosition(Point(midSprite->getBoundingBox().size.width/2,midSprite->getBoundingBox().size.height/2));
    midSprite->addChild(directionLabel);
    
    //初始化directionMap
    initDirectionMap();
    
    //触碰事件响应
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan=CC_CALLBACK_2(CommonPlayLayer::onTouchBegan,this);
    touchListener->onTouchEnded=CC_CALLBACK_2(CommonPlayLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, WSSprite);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), SSprite);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), ESSprite);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), WSprite);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), ESprite);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), WNSprite);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), NSprite);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), ENSprite);

    return true;
}
void CommonPlayLayer::initAbnormalSceneDirection(){
    auto mScene=(MainGameScene*)this->getParent();
    std::string gameMode = mScene->getGameMode();
    if(gameMode=="abnormal"){//变态模式需要随机改变位置
        for(int i=0;i<8;i++){
            Sprite* nextDirctionSprite =directionMap.at(directionLabel->getString());
            Sprite* changeDirctionSprite = directionMap.at(directionFont[(int)(CCRANDOM_0_1()*12)%12]);
            spriteChangePosition(nextDirctionSprite,changeDirctionSprite);
        }
    }
}

void CommonPlayLayer::initDirectionMap()
{
     /*directionMap.insert("东北",WSSprite);
     directionMap.insert("北东",WSSprite);
     directionMap.insert("北", SSprite);
     directionMap.insert("西北", ESSprite);
     directionMap.insert("北西", ESSprite);
     directionMap.insert("东", WSprite);
     directionMap.insert("西", ESprite);
     directionMap.insert("东南", WNSprite);
     directionMap.insert("南东", WNSprite);
     directionMap.insert("南", NSprite);
     directionMap.insert("西南", ENSprite);
     directionMap.insert("南西", ENSprite);*/
    
     directionMap.insert("Eastnorth",WSSprite);
     directionMap.insert("Northeast",WSSprite);
     directionMap.insert("North", SSprite);
     directionMap.insert("Westnorth", ESSprite);
     directionMap.insert("Northwest", ESSprite);
     directionMap.insert("East", WSprite);
     directionMap.insert("West", ESprite);
     directionMap.insert("Eastsouth", WNSprite);
     directionMap.insert("Southeast", WNSprite);
     directionMap.insert("South", NSprite);
     directionMap.insert("Westsouth", ENSprite);
     directionMap.insert("Southwest", ENSprite);
    
}
bool CommonPlayLayer::onTouchBegan(Touch* touch, Event*event)
{
    auto target=static_cast<Sprite*>(event->getCurrentTarget());
    Point locationInNode = target->convertTouchToNodeSpace(touch);
    Size size = target->getContentSize();
    Rect rect = Rect(0, 0, size.width, size.height);
    
    if (rect.containsPoint(locationInNode))
    {
        //target->setOpacity(180);
        //log("targetName is %s",target->getName().c_str());
        std::string pressPic =target->getName()+"Action.png";
        target->setTexture(pressPic);
        return true;
    }
    return false;
}
void CommonPlayLayer::spriteChangePosition(Sprite* oneSprite,Sprite* anotherSprite)
{
    Point onePoint = oneSprite->getPosition();
    Point anotherPoint  = anotherSprite->getPosition();
    oneSprite->setPosition(anotherPoint);
    anotherSprite->setPosition(onePoint);
}
void CommonPlayLayer::onTouchEnded(Touch* touch, Event* event)
{
    auto target=static_cast<Sprite*>(event->getCurrentTarget());
    Sprite* currDirctionSprite =directionMap.at(directionLabel->getString());
    auto mScene=(MainGameScene*)this->getParent();
    mScene->press_time=0.0;
    std::string gameMode = mScene->getGameMode();
    if(currDirctionSprite==target)
    {//right
        if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
            SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("touch.wav").c_str(), false);
        int rondom=(int)(CCRANDOM_0_1()*12)%12;
        directionLabel->setString(directionFont[rondom]);
        
        
        mScene->setCurPressTime(mScene->getCurPressTime()+1);
    }else{
       // fail
        if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
            SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("error.wav").c_str(), false);
        mScene->unschedule(schedule_selector(MainGameScene::update));
        
        if(gameMode=="classics"){
            Director::getInstance()->replaceScene(TransitionFade::create(0.1f, FailScene::createClassicFailedScene()));
            
            if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
                SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("over.wav").c_str(), false);

        }else if(gameMode=="challenge"){
            GameManager::getInstance()->setPressTimes(mScene->getCurPressTime());
            Director::getInstance()->replaceScene(TransitionFade::create(0.1f, FailScene::createChallengeFailedScene()));
            
            if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
                SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("over.wav").c_str(), false);
        }else if(gameMode=="quick"){
            GameManager::getInstance()->setPressTimes(mScene->getCurPressTime());
            Director::getInstance()->replaceScene(TransitionFade::create(0.1f,SuccessfulScene::createQuickSuccessfulScene()));
            
            if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
                SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("over.wav").c_str(), false);
        }else if(gameMode=="endless"){
            GameManager::getInstance()->setPressTimes(mScene->getCurPressTime());
            Director::getInstance()->replaceScene(TransitionFade::create(0.1f,SuccessfulScene::createEndlessSuccessfulScene()));
            
            if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
                SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("over.wav").c_str(), false);
        }else if(gameMode=="abnormal"){
            GameManager::getInstance()->setPressTimes(mScene->getCurPressTime());
            Director::getInstance()->replaceScene(TransitionFade::create(0.1f,SuccessfulScene::createAbnormalSuccessfulScene()));
            
            if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
                SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("over.wav").c_str(), false);
        }
        
       
    }
    target->setTexture(target->getName()+".png");
}