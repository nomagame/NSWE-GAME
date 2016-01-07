//
//  MainMenuScene.cpp
//  NSWNGAME
//
//  Created by nancai on 14/12/26.
//
//

#include "MainMenuScene.h"
#include "MainGameScene.h"
#include "InstallScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool MainMenuScene::init(){
    if(!Scene::init())
        return false;
    Sprite * bgSprite = Sprite::create("mainMenuBg.png");
    bgSprite->setAnchorPoint(Point(0,0));
    addChild(bgSprite);
    
    auto classicsMenuItem = MenuItemImage::create("classicsItem.png",
                                                  "classicsItemAction.png",
                                                  CC_CALLBACK_1(MainMenuScene::classicsStart,this));
    classicsMenuItem->setAnchorPoint(Point(0,0));
    classicsMenuItem->setPosition(Point(0.0f,110.5*2));
    auto quickMenuItem = MenuItemImage::create("quickItem.png",
                                               "quickItemAction.png",
                                               CC_CALLBACK_1(MainMenuScene::quickStart, this));
    quickMenuItem->setAnchorPoint(Point(0,0));
    quickMenuItem->setPosition(Point(67.5f,110.5*2));
    auto  challengeMenuItem =MenuItemImage::create("challengeItem.png",
                                               "challengeItemAction.png",
                                               CC_CALLBACK_1(MainMenuScene::challengeStart, this));
    challengeMenuItem->setAnchorPoint(Point(0,0));
    challengeMenuItem->setPosition(Point(0.0f,110.5));
    auto  abnormalMenuItem =MenuItemImage::create("abnormalItem.png",
                                                   "abnormalItemAction.png",
                                                   CC_CALLBACK_1(MainMenuScene::abnormalStart, this));
    abnormalMenuItem->setAnchorPoint(Point(0,0));
    abnormalMenuItem->setPosition(Point(67.5f,110.5));
    
    /*auto endlessItem = MenuItemImage::create("endlessItem.png",
                                             "endlessItemAction.png",
                                             CC_CALLBACK_1(MainMenuScene::endlessStart,this));
    endlessItem->setAnchorPoint(Point(0,0));
    endlessItem->setPosition(Point(67.5f,110.5));*/
    auto installItem = MenuItemImage::create("installItem.png",
                                             "installItemAction.png",
                                             CC_CALLBACK_1(MainMenuScene::intoInstallScene,this));
    installItem->setAnchorPoint(Point(0,0));
    installItem->setPosition(Point(0.0f,0.0f));
    auto endGameItem = MenuItemImage::create("endGameItem.png",
                                            "endGameItemAction.png",
                                             CC_CALLBACK_1(MainMenuScene::endGame, this));
    endGameItem->setAnchorPoint(Point(0,0));
    endGameItem->setPosition(Point(67.5f,0.0f));
    auto menu = Menu::create(classicsMenuItem,quickMenuItem,challengeMenuItem,abnormalMenuItem,installItem,endGameItem,NULL);
    
    menu->setAnchorPoint(Point(0,0));

    menu->setPosition(Point(67.5f,37.2f));
    addChild(menu);
    
    return true;
}
void MainMenuScene::classicsStart(Ref* pSender)
{
    
    Director::getInstance()->replaceScene(TransitionFade::create(0.1f,MainGameScene::createClassicsScene()));
    if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
        SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("start.wav").c_str(), false);
}
void MainMenuScene::quickStart(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionFade::create(0.1f,MainGameScene::createQuickScene()));
    
    if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
        SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("start.wav").c_str(), false);

}
void MainMenuScene::challengeStart(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionFade::create(0.1f,MainGameScene::createChallengeScene()));
    
    if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
        SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("start.wav").c_str(), false);

}
void MainMenuScene::endlessStart(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionFade::create(0.1f,MainGameScene::createEndlessScene()));
    
    if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
        SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("start.wav").c_str(), false);

}
void MainMenuScene::abnormalStart(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionFade::create(0.1f,MainGameScene::createAbnormalScene()));
    
    if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
        SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("start.wav").c_str(), false);

}
void MainMenuScene::intoInstallScene(Ref* pSender)
{
    if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
        SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("click.wav").c_str(), false);
    Director::getInstance()->replaceScene(TransitionFade::create(0.1f,InstallScene::create()));
}
void MainMenuScene::endGame(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}