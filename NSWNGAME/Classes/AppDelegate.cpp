#include "AppDelegate.h"
#include "AppMacros.h"
#include "MainMenuScene.h"
#include "MainGameScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        glview->setFrameSize(320, 480);
        director->setOpenGLView(glview);
    }

    //屏幕自适应
    auto screenSize = glview->getFrameSize();
    std::vector<std::string> searchPaths;
    
    // 这里是实现的重点，比较屏幕的高和设定的三种适配尺寸的高，选择合适的图片
    // 然后将对应图片的路径添加到搜索路径中，那么cocos2d-x就会到该目录去寻找图片
  /*  if (screenSize.width> largeResource.size.width)
    {
        glview->setDesignResolutionSize(largeResource.size.width, largeResource.size.height, ResolutionPolicy::FIXED_WIDTH);
        director->setContentScaleFactor(RESOURCE_WIDTH/largeResource.size.width);
        searchPaths.push_back(largeResource.directory);
    }else if (screenSize.width > middleResource.size.width)
    {
        glview->setDesignResolutionSize(middleResource.size.width, middleResource.size.height, ResolutionPolicy::FIXED_WIDTH);
        director->setContentScaleFactor(RESOURCE_WIDTH/middleResource.size.width);
        searchPaths.push_back(middleResource.directory);
    }else
    {
        glview->setDesignResolutionSize(smallResource.size.width, smallResource.size.height, ResolutionPolicy::FIXED_WIDTH);
        director->setContentScaleFactor(RESOURCE_WIDTH/smallResource.size.width);
        searchPaths.push_back(smallResource.directory);
    }*/
    glview->setDesignResolutionSize(smallResource.size.width, smallResource.size.height, ResolutionPolicy::FIXED_WIDTH);
    director->setContentScaleFactor(RESOURCE_WIDTH/smallResource.size.width);
    searchPaths.push_back(smallResource.directory);
    //log("scale is %f",director->getContentScaleFactor());
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);


   
    // create a scene. it's an autorelease object
    //auto scene = MainGameScene::createClassicsScene();
    //auto scene = MainGameScene::createChallengeScene();
    //auto scene = MainGameScene::createQuickScene();
   // auto scene=MainGameScene::createEndlessScene();
    auto scene = MainMenuScene::create();
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
