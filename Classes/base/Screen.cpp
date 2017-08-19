#include "SimpleAudioEngine.h"
#include "Screen.h"

USING_NS_CC;

Screen* Screen::instance = NULL;

Screen* Screen::GetInstance() {
    if (Screen::instance == NULL) {
        Screen::instance = new Screen();
    }
    return Screen::instance;
}