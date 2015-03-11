//
//  startScene.h
//  ttzj
//
//  Created by 林跃南 on 15/3/11.
//
//

#ifndef __ttzj__startScene__
#define __ttzj__startScene__


#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"


USING_NS_CC;
USING_NS_CC_EXT;


class startScene : public Layer {
    
public:
    
    static Scene* createScene();
    virtual bool init();
    void menucallback();//render will add
    CREATE_FUNC(startScene);
    
public:
    
    void addUI();
    void addEffect();
    void addres();
    
private:
    
    Size winSize;
    
};


class chooseScene : public Layer {
    
public:
    
    static Scene* createScene();
    virtual bool init();
    void menucallback();
    CREATE_FUNC(chooseScene);
    
public:
    
    void addUI();
    void addselectLayer();
    void addlistener();
    
private:
    
    Size winSize;
    Layer * selectLayer;
    Vec2 startPoint;
    Vec2 firstPoint;
    
};

#endif /* defined(__ttzj__startScene__) */
