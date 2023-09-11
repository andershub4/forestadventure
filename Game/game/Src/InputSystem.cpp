/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "InputSystem.h"

#include <algorithm>

#include <SFML/Window/Event.hpp>

#include "Logging.h"
#include "Message/BroadcastMessage/CloseWindowMessage.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Message/BroadcastMessage/KeyReleasedMessage.h"
#include "Message/MessageBus.h"

namespace FA {

InputSystem::InputSystem(Shared::MessageBus& messageBus, Graphic::IRenderWindow& window)
    : messageBus_(messageBus)
    , window_(window)
{}

void InputSystem::Update(float deltaTime)
{
    sf::Event event;

    while (window_.pollEvent(event)) {
        ProcessEvent(event);
    }

    ProcessIsKeyPressed();
}

void InputSystem::ProcessEvent(const sf::Event& event)
{
    switch (event.type) {
        case sf::Event::KeyPressed: {
            auto key = event.key.code;
            auto msg = std::make_shared<Shared::KeyPressedMessage>(key);
            pressedKeys_.emplace(key);
            messageBus_.SendMessage(msg);
            break;
        }
        case sf::Event::KeyReleased: {
            auto key = event.key.code;
            auto msg = std::make_shared<Shared::KeyReleasedMessage>(key);
            pressedKeys_.erase(key);
            messageBus_.SendMessage(msg);
            break;
        }
        case sf::Event::Closed: {
            auto msg = std::make_shared<Shared::CloseWindowMessage>();
            messageBus_.SendMessage(msg);
            break;
        }
        case sf::Event::LostFocus: {
            ReleaseKeys();
        }
    }
}

void InputSystem::ProcessIsKeyPressed()
{
    for (auto k : pressedKeys_) {
        auto msg = std::make_shared<Shared::IsKeyPressedMessage>(k);
        messageBus_.SendMessage(msg);
    }
}

void InputSystem::ReleaseKeys()
{
    for (auto k : pressedKeys_) {
        auto msg = std::make_shared<Shared::KeyReleasedMessage>(k);
        messageBus_.SendMessage(msg);
    }
    pressedKeys_.clear();
}

}  // namespace FA
