#include "SimpleAudioEngine.h"
#include "Colors.h"

USING_NS_CC;

Color4B Colors::Transparent = Color4B(0, 0, 0, 0);
Color4B Colors::HalfTransparent = Color4B(0, 0, 0, 200);
Color4B Colors::White = Color4B(255, 255, 255, 255);
Color4B Colors::BgColor = Color4B(38, 50, 56, 255);
Color4B Colors::OutNumberColor = Color4B(169, 169, 169, 255);
Color4B Colors::Number24DefaultColor = Color4B(33, 150, 243, 255);
Color4B Colors::Number24FailColor = Color4B(244, 67, 54, 255);
Color4B Colors::Number24SuccessColor = Color4B(0, 230, 118, 255);
Color4B Colors::DangerColor = Color4B(229, 57, 53, 255);
Color4B Colors::SuccessColor = Color4B(118, 255, 3, 255);

Color4B Colors::NumberColors[NUMBER_MAX] = {Color4B(255, 87, 34, 255), \
    Color4B(255, 152, 0, 255), \
    Color4B(255, 235, 59, 255), \
    Color4B(43, 175, 43, 255), \
    Color4B(29, 233, 182, 255), \
    Color4B(38, 166, 152, 255), \
    Color4B(0, 188, 212, 255), \
    Color4B(0, 176, 255, 255), \
    Color4B(86, 119, 252, 255), \
    Color4B(103, 58, 183, 255), \
    Color4B(121, 85, 72, 255), \
    Color4B(156, 39, 176, 255), \
    Color4B(216, 27, 96, 255)};

Color4B Colors::GetColorsByNumber(AccurateNumber *accurateNumber) {
    if (accurateNumber->wrong) {
        return Colors::Transparent;
    }
    if (accurateNumber->value % accurateNumber->divider != 0) {
        return Colors::White;
    }
    auto number = accurateNumber->value / accurateNumber->divider;
    if (number > 0 && number <= NUMBER_MAX) {
        return Colors::NumberColors[number - 1];
    }
    return Colors::White;
}