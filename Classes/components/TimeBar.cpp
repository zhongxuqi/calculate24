#include "SimpleAudioEngine.h"
#include "TimeBar.h"

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
    timeBar->loadingBar = LoadingBar::create();
    timeBar->loadingBar->loadTexture("res/LoadingBar_Green.png");
    timeBar->loadingBar->setDirection(LoadingBar::Direction::LEFT);
    timeBar->loadingBar->setPercent(100);
    timeBar->loadingBar->setScale9Enabled(true);
    timeBar->loadingBar->setCapInsets(Rect(20, 8, 63, 4));
    timeBar->loadingBar->setAnchorPoint(Point(0, 0.5));
    timeBar->loadingBar->setContentSize(Size(width - height - 20, height / 2));
    timeBar->loadingBar->setPosition(Point(height + 20, height / 2));
    timeBar->addChild(timeBar->loadingBar, 0);

    return timeBar;
}

void TimeBar::SetPercent(float percent) {
    if (percent < 20) {
        this->loadingBar->loadTexture("res/LoadingBar_Red.png");
    } else if (percent < 50) {
        this->loadingBar->loadTexture("res/LoadingBar_Yellow.png");
    } else {
        this->loadingBar->loadTexture("res/LoadingBar_Green.png");
    }
    this->loadingBar->setPercent(percent);
}