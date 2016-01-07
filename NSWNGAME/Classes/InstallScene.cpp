//
//  InstallScene.cpp
//  NSWNGAME
//
//  Created by nancai on 14/12/27.
//
//

#include "InstallScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
bool InstallScene::init(){
    if(!Scene::init())
        return false;
    
    Sprite * bgSprite = Sprite::create("mainMenuBg.png");
    bgSprite->setAnchorPoint(Point(0,0));
    addChild(bgSprite);
    
    Sprite* voiceSprite =Sprite::create("voice.png");
    voiceSprite->setAnchorPoint(Point(0,0));
    voiceSprite->setPosition(Point(67.5f,110.5*2+37.5));
    addChild(voiceSprite);
    
    voiceStateSprite = Sprite::create("state_close.png");
    
    if(UserDefault::getInstance()->getBoolForKey("voice_state", true)){
        voiceStateSprite->setTexture("state_open.png");
    }
    
    auto voiceStateItem= MenuItemSprite::create(voiceStateSprite,
                                                voiceStateSprite,
                                                CC_CALLBACK_1(InstallScene::changeVoiceState,this));
    voiceStateItem->setAnchorPoint(Point(0,0));
    voiceStateItem->setPosition(Point(67.5f,110.5*2));
    
    auto  aboutMenuItem =MenuItemImage::create("aboutItem.png",
                                                  "aboutItem.png",
                                                  CC_CALLBACK_1(InstallScene::interAboutScene, this));
    aboutMenuItem->setAnchorPoint(Point(0,0));
    aboutMenuItem->setPosition(Point(0.0f,110.5));
    
    auto helpItem = MenuItemImage::create("helpItem.png",
                                             "helpItem.png",
                                          CC_CALLBACK_1(InstallScene::interHelpScene,this));
    helpItem->setAnchorPoint(Point(0,0));
    helpItem->setPosition(Point(67.5f,110.5));
    
    auto backItem = MenuItemImage::create("backItem.png",
                                             "backItem.png",
                                          CC_CALLBACK_1(InstallScene::backToMainMenuScene,this));
    backItem->setAnchorPoint(Point(0,0));
    backItem->setPosition(Point(0.0f,0.0f));
 
    auto menu = Menu::create(voiceStateItem,aboutMenuItem,helpItem,backItem,NULL);
    
    menu->setAnchorPoint(Point(0,0));
    
    menu->setPosition(Point(67.5f,37.2f));
    addChild(menu);
    return true;
    
}

void InstallScene::changeVoiceState(Ref* pSender)
{
    
    if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
        SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("click.wav").c_str(), false);

    bool voice_state =UserDefault::getInstance()->getBoolForKey("voice_state",true);
    if(voice_state)
    {
        UserDefault::getInstance()->setBoolForKey("voice_state",false);
        voiceStateSprite->setTexture("state_close.png");
    }else{
        UserDefault::getInstance()->setBoolForKey("voice_state",true);
        voiceStateSprite->setTexture("state_open.png");
    }
}
void InstallScene::interAboutScene(Ref* pSender)
{
    if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
        SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("click.wav").c_str(), false);

    Scene* aboutScene = Scene::create();
    Sprite* bgSprite = Sprite::create("aboutScene.png");
    bgSprite->setAnchorPoint(Point(0,0));
    bgSprite->setPosition(Point(0,0));
    aboutScene->addChild(bgSprite);
    
    auto backItem = MenuItemImage::create("noBorderBack.png",
                                          "noBorderBack.png",
                                          CC_CALLBACK_1(InstallScene::backToInstallScene,this));
    backItem->setAnchorPoint(Point(0,0));
    backItem->setPosition(Point(0.0f,0.0f));
    
    auto menu = Menu::create(backItem,NULL);
    
    menu->setAnchorPoint(Point(0,0));
    
    menu->setPosition(Point(108.0f,38.2f));
    aboutScene->addChild(menu);
    
    Director::getInstance()->replaceScene(TransitionFade::create(0.1f,aboutScene));
}
void InstallScene::interHelpScene(Ref* pSender)
{
    if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
        SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("click.wav").c_str(), false);
    Scene* helpScene = Scene::create();
    Sprite* bgSprite = Sprite::create("helpScene.png");
    bgSprite->setAnchorPoint(Point(0,0));
    bgSprite->setPosition(Point(0,0));
    helpScene->addChild(bgSprite);
    
    auto backItem = MenuItemImage::create("back_new.png",
                                          "back_new.png",
                                          CC_CALLBACK_1(InstallScene::backToInstallScene,this));
    backItem->setAnchorPoint(Point(0,0));
    backItem->setPosition(Point(0.0f,0.0f));
    
    auto menu = Menu::create(backItem,NULL);
    
    menu->setAnchorPoint(Point(0,0));
    
    menu->setPosition(Point(100.0f,38.2f));
    helpScene->addChild(menu);
    
    Director::getInstance()->replaceScene(TransitionFade::create(0.1f,helpScene));
}
void InstallScene::backToMainMenuScene(Ref* pSender)
{
     if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
        SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("click.wav").c_str(), false);
     Director::getInstance()->replaceScene(TransitionFade::create(0.1f,MainMenuScene::create()));
}
void InstallScene::backToInstallScene(Ref* pSender)
{
     if(UserDefault::getInstance()->getBoolForKey("voice_state",true))
         SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("click.wav").c_str(), false);
     Director::getInstance()->replaceScene(TransitionFade::create(0.1f,InstallScene::create()));
}