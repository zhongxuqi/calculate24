#include "SimpleAudioEngine.h"
#include "GameOverDialog.h"
#include "../base/Colors.h"

USING_NS_CC;

bool GameOverDialog::init() {
    if (!LayerColor::initWithColor(Colors::HalfTransparent)) {
        return false;
    }
    return true;
}

GameOverDialog* GameOverDialog::create(float width, float height) {
    auto gameOverDialog = GameOverDialog::create();
    gameOverDialog->setContentSize(Size(width, height));
    gameOverDialog->setIgnoreAnchorPointForPosition(false);
    
    // add game over text
    auto gameLabel = Label::createWithTTF("Game Over", "fonts/arial.ttf", height / 18);
    gameLabel->setAnchorPoint(Point(0.5, 0.5));
    gameLabel->setPosition(Point(width * 0.5, height * 0.5));
    gameLabel->setTextColor(Colors::White);
    gameOverDialog->addChild(gameLabel, 0);

    return gameOverDialog;
}