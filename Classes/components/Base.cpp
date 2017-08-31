#include "SimpleAudioEngine.h"
#include "ScoreBar.h"

USING_NS_CC;

BaseComponent::BaseComponent(Node* node): RootNode(node) {
    
}

Node* BaseComponent::GetRootNode() {
    return this->RootNode;
}