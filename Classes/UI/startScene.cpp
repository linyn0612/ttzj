//
//  startScene.cpp
//  ttzj
//
//  Created by 林跃南 on 15/3/11.
//
//

#include "startScene.h"


/*
 ********************************************************
 ********************************************************
 ****                   startScene                   ****
 ********************************************************
 ********************************************************
*/
 
Scene * startScene::createScene(){

    auto scene = Scene::create();
    auto layer = startScene::create();
    scene->addChild(layer);
    return scene;
    
}

bool startScene::init(){
    
    if (!Layer::init()) {
        return false;
    }
    
    winSize = Director::getInstance()->getWinSize();
    addres();
    addUI();
    
    return true;
}

void startScene::addres(){

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("outFram.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("outTwo.plist");

}


void startScene::addUI(){
    
    //BG
    auto bg = Sprite::create("menu_bg.jpg");
    bg->setPosition(winSize/2);
    this->addChild(bg);
    
    //startmenu
    auto startnormal = Sprite::createWithSpriteFrameName("m_play.png");
    auto startselected = Sprite::createWithSpriteFrameName("m_play_1.png");
    auto startitem = MenuItemSprite::create(startnormal, startselected, CC_CALLBACK_0(startScene::menucallback, this) );
    startitem->setPosition(winSize.width/4*3,winSize.height/4);
    
    auto menu = Menu::create(startitem, NULL);
    menu->setPosition(CCPointZero);
    addChild(menu);
    
}

void startScene::menucallback(){

    Director::getInstance()->replaceScene(chooseScene::createScene());
    this->removeFromParent();
}




/*
 ********************************************************
 ********************************************************
 ****                  chooseScene                   ****
 ********************************************************
 ********************************************************
 */
Scene * chooseScene::createScene(){
    
    auto scene = Scene::create();
    auto layer = chooseScene::create();
    scene->addChild(layer);
    return scene;
    
}


bool chooseScene::init(){
    
    if (!Layer::init()) {
        return false;
    }
    
    winSize = Director::getInstance()->getWinSize();
    addUI();
    addselectLayer();
    addlistener();
    
    return true;
}

void chooseScene::addUI(){
    
    //bg
    auto bg = Sprite::create("map_bg.jpg");
    bg->setPosition(winSize/2);
    addChild(bg);
    
    //menu
    auto back = Sprite::createWithSpriteFrameName("shop_back.png");
    auto backitem = MenuItemSprite::create(back, back, CC_CALLBACK_0(chooseScene::menucallback, this));
    backitem->setPosition(Vec2(back->getContentSize().width/2*1.2,winSize.height-back->getContentSize().height/2*1.2));
    auto menu = Menu::create(backitem, NULL);
    menu->setPosition(CCPointZero);
    addChild(menu);
    
    auto te = Sprite::createWithSpriteFrameName("lev_z_xz.png");
    te->setPosition(400,400);
    addChild(te,100);
}

void chooseScene::addselectLayer(){

    selectLayer = Layer::create();
    selectLayer->setContentSize(Size(2400,360));
    Sprite * sp;
    for (int i = 0; i<18; i++) {
        sp = Sprite::createWithSpriteFrameName("level_full.png");
        sp->setAnchorPoint(Vec2(0,0));
        if (i<9) {
            sp->setPosition(sp->getContentSize().width*i,0);
        }else{
            sp->cocos2d::Node::setPosition(sp->getContentSize().width*(i-9),sp->getContentSize().height);
        }
        selectLayer->addChild(sp);
    }
    addChild(selectLayer);
    log("%f",selectLayer->getPositionX());
}

void chooseScene::addlistener(){

    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = [this](Touch * t,Event * e){
        
        startPoint = t->getLocation();
        firstPoint = t->getLocation();
        
        return true;
    };
    listener->onTouchMoved = [this](Touch * t,Event * e){
        
        selectLayer->setPosition(selectLayer->getPositionX()+t->getLocation().x-startPoint.x,selectLayer->getPositionY());
        startPoint = t->getLocation();
    };
    listener->onTouchEnded = [this](Touch * t,Event * e){
        
        int direction = t->getLocation().x-firstPoint.x<0?1:-1;
        float x = -selectLayer->getPositionX();
        if (x < 0 || x>1600) {
            direction = -1;
        }
        float dis = direction>0?800 - ((int)x % 800):(int)x % 800;
        //float dis = direction>0?(int)x % 800:800 - ((int)x % 800);
        
        auto move = MoveBy::create(0.5, Vec2(-dis * direction,selectLayer->getPositionY()));
        selectLayer->runAction(move);
        
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void chooseScene::menucallback(){

    Director::getInstance()->replaceScene(startScene::createScene());
    this->removeFromParent();
    
}





