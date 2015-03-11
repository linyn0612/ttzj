#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto move = MoveTo::create(10, Vec2(500,400));
    auto s = Sprite::create("bg_1.jpg");
    s->setScale(0.3);
    s->setPosition(100,400);
    addChild(s);
    s->runAction(move);
    
    s2 = Sprite::create("bg_2.jpg");
    log("x:%f,y:%f",s2->getContentSize().width,s->getContentSize().height);
    s2->setPosition(400,400);
    s2->setScale(0.3);
    addChild(s2);
    
    log("x:%f,y:%f",s2->getContentSize().width,s->getContentSize().height);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch * t,Event * e){
        
        auto fangda = ScaleTo::create(2, 3);
        this->runAction(fangda);
        
        if(s2->getBoundingBox().containsPoint(t->getLocation()))
        {
            log("!!!!!");
        }
        
        return false;
    };
    _eventDispatcher->addEventListenerWithFixedPriority(listener, 1);
    
    return true;
}
