#include "SimpleAudioEngine.h"
#include "TimeBar.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

bool TimeBar::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

TimeBar* TimeBar::create(float width, float height) {
    auto timeBar = TimeBar::create();
    timeBar->setContentSize(Size(width, height));
    timeBar->setIgnoreAnchorPointForPosition(false);
    
    // add clock icon
    auto clockIcon = Sprite::create("res/Clock.png");
    clockIcon->setScale(height / clockIcon->getContentSize().height);
    clockIcon->setAnchorPoint(Point(0.5, 0.5));
    clockIcon->setPosition(height * 0.5, height * 0.5);
    timeBar->addChild(clockIcon, 0);

    // add loading bar
    auto loadingBar = LoadingBar::create();
    loadingBar->loadTexture("res/LoadingBar_Green.png");
    loadingBar->setDirection(LoadingBar::Direction::RIGHT);
    loadingBar->setPercent(100);
    loadingBar->setScale9Enabled(true);
    loadingBar->setCapInsets(Rect(20, 8, 63, 4));
    loadingBar->setAnchorPoint(Point(0, 0.5));
    loadingBar->setContentSize(Size(width - height - 20, height / 2));
    loadingBar->setPosition(Point(height + 20, height / 2));
    timeBar->addChild(loadingBar, 0);

    return timeBar;
}