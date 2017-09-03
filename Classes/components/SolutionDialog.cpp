#include "SimpleAudioEngine.h"
#include "SolutionDialog.h"
#include "../base/Colors.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;
using namespace ui;

SolutionDialog::SolutionDialog() {

}

SolutionDialog* SolutionDialog::create(float width, float height) {
    auto solutionDialog = new SolutionDialog();
    solutionDialog->setContentSize(Size(width, height));
    solutionDialog->ignoreAnchorPointForPosition(false);

    // add background
    auto bgDialog = Scale9Sprite::create("res/BgDialog.png", Rect(0, 0, 108, 99), Rect(10, 10, 88, 79));
    bgDialog->setContentSize(Size(width, height));
    bgDialog->setAnchorPoint(Point(0, 0));
    solutionDialog->addChild(bgDialog, 0);

    // add back button
    solutionDialog->backButton = Button::create("res/BgDialog.png", "res/BgDialog_Pressed.png");
    solutionDialog->backButton->setScale9Enabled(true);
    solutionDialog->backButton->setCapInsets(Rect(10, 10, 88, 79));
    solutionDialog->backButton->setContentSize(Size(height * 1.5 / 10, height / 10));

    // add icon
    auto backIcon = Sprite::create("res/IconBack.png");
    backIcon->setScale(solutionDialog->backButton->getContentSize().height * 0.6 / backIcon->getContentSize().height);
    backIcon->setAnchorPoint(Point(0.5, 0.5));
    backIcon->setPosition(Point(solutionDialog->backButton->getContentSize().width / 2, solutionDialog->backButton->getContentSize().height / 2));
    solutionDialog->backButton->addChild(backIcon, 0);

    solutionDialog->backButton->setAnchorPoint(Point(0, 1));
    solutionDialog->backButton->setPosition(Point(0, height));
    solutionDialog->addChild(solutionDialog->backButton, 0);

    return solutionDialog;
}

void SolutionDialog::SetOnCloseListener(std::function<void(Ref*)> listener) {
    this->backButton->addClickEventListener(listener);
}