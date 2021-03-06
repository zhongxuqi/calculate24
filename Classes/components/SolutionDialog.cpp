#include "SimpleAudioEngine.h"
#include "SolutionDialog.h"
#include "../base/Colors.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;
using namespace ui;

bool SolutionDialog::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

SolutionDialog* SolutionDialog::create(float width, float height) {
    auto solutionDialog = SolutionDialog::create();
    solutionDialog->setContentSize(Size(width, height));
    solutionDialog->setIgnoreAnchorPointForPosition(false);

    // add background
    auto bgDialog = Scale9Sprite::create("res/BgDialog.png", Rect(0, 0, 108, 99), Rect(10, 10, 88, 79));
    bgDialog->setContentSize(Size(width, height));
    bgDialog->setAnchorPoint(Point(0, 0));
    solutionDialog->addChild(bgDialog, 0);

    solutionDialog->addCloseBtn();
    solutionDialog->addBackBtn();
    solutionDialog->addResetBtn();

    solutionDialog->solutionBoard = SolutionBoard::create(width, height - solutionDialog->backButton->getContentSize().height);
    solutionDialog->solutionBoard->setAnchorPoint(Point(0, 0));
    solutionDialog->solutionBoard->setPosition(Point(0, 0));
    solutionDialog->addChild(solutionDialog->solutionBoard, 0);

    return solutionDialog;
}

void SolutionDialog::SetOnCloseListener(std::function<void(Ref*)> listener) {
    this->closeButton->addClickEventListener(listener);
}

void SolutionDialog::onBackListener(cocos2d::Ref* pRef) {
    this->solutionBoard->GoBack();
}

void SolutionDialog::addCloseBtn() {
    float height = this->getContentSize().height;
    this->closeButton = Button::create("res/BgDialog.png", "res/BgDialog_Pressed.png");
    this->closeButton->setScale9Enabled(true);
    this->closeButton->setCapInsets(Rect(10, 10, 88, 79));
    this->closeButton->setContentSize(Size(height * 1.5 / 10, height / 10));

    // add close icon
    auto closeIcon = Sprite::create("res/IconClose.png");
    closeIcon->setScale(this->closeButton->getContentSize().height * 0.6 / closeIcon->getContentSize().height);
    closeIcon->setAnchorPoint(Point(0.5, 0.5));
    closeIcon->setPosition(Point(this->closeButton->getContentSize().width / 2, this->closeButton->getContentSize().height / 2));
    this->closeButton->addChild(closeIcon, 0);

    this->closeButton->setAnchorPoint(Point(0, 1));
    this->closeButton->setPosition(Point(0, height));
    this->addChild(this->closeButton, 0);
}

void SolutionDialog::addBackBtn() {
    float width = this->getContentSize().width;
    float height = this->getContentSize().height;
    this->backButton = Button::create("res/BgDialog.png", "res/BgDialog_Pressed.png");
    this->backButton->setScale9Enabled(true);
    this->backButton->setCapInsets(Rect(10, 10, 88, 79));
    this->backButton->setContentSize(Size(height * 1.5 / 10, height / 10));

    // add back icon
    auto backIcon = Sprite::create("res/IconBack.png");
    backIcon->setScale(this->backButton->getContentSize().height * 0.6 / backIcon->getContentSize().height);
    backIcon->setAnchorPoint(Point(0.5, 0.5));
    backIcon->setPosition(Point(this->backButton->getContentSize().width / 2, this->backButton->getContentSize().height / 2));
    this->backButton->addChild(backIcon, 0);

    this->backButton->setAnchorPoint(Point(1, 1));
    this->backButton->setPosition(Point(width, height));
    this->addChild(this->backButton, 0);
    this->backButton->addClickEventListener(CC_CALLBACK_1(SolutionDialog::onBackListener, this));
}

void SolutionDialog::addResetBtn() {
    float width = this->getContentSize().width;
    float height = this->getContentSize().height;
    this->resetButton = Button::create("res/BgDialog.png", "res/BgDialog_Pressed.png");
    this->resetButton->setScale9Enabled(true);
    this->resetButton->setCapInsets(Rect(10, 10, 88, 79));
    this->resetButton->setContentSize(Size(height * 1.5 / 10, height / 10));

    // add reset icon
    auto resetIcon = Sprite::create("res/IconReset.png");
    resetIcon->setScale(this->resetButton->getContentSize().height * 0.6 / resetIcon->getContentSize().height);
    resetIcon->setAnchorPoint(Point(0.5, 0.5));
    resetIcon->setPosition(Point(this->resetButton->getContentSize().width / 2, this->resetButton->getContentSize().height / 2));
    this->resetButton->addChild(resetIcon, 0);

    this->resetButton->setAnchorPoint(Point(0.5, 1));
    this->resetButton->setPosition(Point(width / 2, height));
    this->addChild(this->resetButton, 0);

    // add event
    this->resetButton->addClickEventListener([this](Ref* ref) {
        this->solutionBoard->InitNumber(this->accurateNumbers);
    });
}

void SolutionDialog::SetNumbers(AccurateNumber *accurateNumbers[4]) {
    for (int i = 0; i < 4; i++) {
        this->accurateNumbers[i] = accurateNumbers[i];
    }
    this->solutionBoard->InitNumber(this->accurateNumbers);
}

void SolutionDialog::SetOnFinishListener(std::function<void(InputStep*[3])> listener) {
    this->solutionBoard->SetOnFinishListener(listener);
}