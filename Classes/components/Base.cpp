#include "SimpleAudioEngine.h"
#include "ScoreBar.h"

USING_NS_CC;

BaseComponent::BaseComponent(): RootLayer(LayerColor::create()) {
    
}

Layer* BaseComponent::GetRootLayer() {
    return this->RootLayer;
}