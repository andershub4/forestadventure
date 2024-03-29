/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include "Font.h"
#include "RectangleShape.h"
#include "Text.h"

#include "BasicLayer.h"

namespace FA {

namespace Scene {

class HelperLayer : public BasicLayer
{
public:
    HelperLayer(Shared::MessageBus& messageBus, const sf::IntRect& rect, const std::string& sceneName);
    virtual ~HelperLayer();

    virtual std::string Name() const override { return "Helper"; }
    virtual LayerId GetId() const override { return LayerId::Helper; }
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void EnableInput(bool enable) override {}
    virtual void OnLoad() override;
    virtual void OnCreate() override;
    virtual void SubscribeMessages() override;
    virtual void UnsubscribeMessages() override;

private:
    Graphic::RectangleShape dotShape_;
    Graphic::Font font_;
    Graphic::Text sceneText_;
    Graphic::Text fpsText_;
    Graphic::Text fpsNumberText_;
    Graphic::Text nEntitiesText_;
    Graphic::Text nEntitiesCountText_;
    std::string sceneName_;
    unsigned int nEntities_ = 0;

private:
    virtual void OnMessage(std::shared_ptr<Shared::Message> message) override;
};

}  // namespace Scene

}  // namespace FA
