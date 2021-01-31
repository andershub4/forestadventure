/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "BasicComponent.h"

namespace FA {

namespace Scene {

class HelperComponent : public BasicComponent
{
public:
    HelperComponent(MessageBus& messageBus, const std::string& sceneName);
    virtual ~HelperComponent();

    virtual ComponentId GetId() const override { return ComponentId::Helper; }
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void ProcessMessages(bool process) override {}

private:
    sf::RectangleShape dotShape_;
    sf::Font font_;
    sf::Text sceneText_;
    sf::Text fpsText_;
    sf::Text fpsNumberText_;
};

}  // namespace Scene

}  // namespace FA
