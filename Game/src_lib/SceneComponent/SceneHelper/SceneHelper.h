/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace FA {

class MessageBus;
class Layer;

class SceneHelper
{
public:
    SceneHelper(MessageBus& messageBus, const std::string& sceneName);
    virtual ~SceneHelper();

    void Update(float deltaTime);
    void DrawTo(Layer& layer);

private:
    MessageBus& messageBus_;
    sf::RectangleShape dotShape_;
    sf::Font font_;
    sf::Text sceneText_;
    sf::Text fpsText_;
    sf::Text fpsNumberText_;
};

}  // namespace FA
