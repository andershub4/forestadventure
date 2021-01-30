/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "SceneComponent.h"

namespace FA {

class SceneComponentHelper : public SceneComponent
{
public:
    SceneComponentHelper(MessageBus& messageBus, const std::string& sceneName);
    virtual ~SceneComponentHelper();

    virtual SceneComponentId GetId() const override { return SceneComponentId::Helper; }
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

private:
    sf::RectangleShape dotShape_;
    sf::Font font_;
    sf::Text sceneText_;
    sf::Text fpsText_;
    sf::Text fpsNumberText_;
};

}  // namespace FA
