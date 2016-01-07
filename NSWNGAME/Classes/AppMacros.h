//
//  AppMacros.h
//  NSWNGAME
//
//  Created by nancai on 14/12/21.
//
//

#ifndef NSWNGAME_AppMacros_h
#define NSWNGAME_AppMacros_h

#define DESIGN_RESOLUTION_480X320    0
#define DESIGN_RESOLUTION_1024X768   1
#define DESIGN_RESOLUTION_2048X1536  2


#define RESOURCE_WIDTH  1080
#define RESOURCE_HEIGHT 1920
// 要切换设计方案，改变这一行即可
#define TARGET_DESIGN_RESOLUTION_SIZE  DESIGN_RESOLUTION_480X320

typedef struct tagResource
{
    cocos2d::Size size;        // 尺寸
    char directory[100];   // 资源路径
}Resource;

//由于这里时竖屏的，所以screen.width<screen.height
static Resource smallResource  =  { cocos2d::Size(270, 480),   "iphone" };//16:9
static Resource middleResource =  { cocos2d::Size(768, 1024),  "ipad"   };
static Resource largeResource  =  { cocos2d::Size(1536,2048), "ipadhd" };


static std::string commentsStr[] ={"一看就知道经常在家撸！","恭喜你被评为“年度最佳快枪手”",//16
                                "一人之下万人之上！","你就是pig的上限！","恭喜你成功拉低了整条街的智商",
                                "图样图森破！","亲，今天也要按时吃药哦！","再加把油当上高富帅！","脑袋中了一箭！",
                                "你是二师兄失散多年的兄弟吗！","要学会笨鸟先飞哦！","祝孤生！",
                                "你别以为我不知道你开了外挂","爱因斯坦是你的远房亲戚吗！","你的反应可以打破牛顿第－定律",
                                "想看评论？木有，哈哈"
};
#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_480X320)
static cocos2d::Size designResolutionSize = cocos2d::Size(480, 270);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1024X768)
static cocos2d::Size designResolutionSize = cocos2d::Size(1024, 768);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_2048X1536)
static cocos2d::Size designResolutionSize = cocos2d::Size(2048, 1536);
#else
#error unknown target design resolution!
#endif

// 480*320的字体大小是24号，根据当前的分辨率来修改字体大小
#define TITLE_FONT_SIZE  (cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 24)


#endif
