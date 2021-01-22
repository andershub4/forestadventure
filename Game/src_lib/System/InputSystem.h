/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <unordered_set>

#include "Enum/KeyboardKey.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

class MessageBus;

class InputSystem
{
public:
    InputSystem(MessageBus& messageBus, sf::RenderWindow& window);

    void Update(float deltaTime);

private:
    sf::RenderWindow& window_;
    MessageBus& messageBus_;
    Keyboard::Key activeKey_ = Keyboard::Key::Undefined;

private:
    void ProcessEvent(const sf::Event& event);
    void IsKeyPressed(Keyboard::Key& pressedKey, Keyboard::Key& releasedKey) const;
    void ProcessIsKeyPressed();
};

}  // namespace FA
