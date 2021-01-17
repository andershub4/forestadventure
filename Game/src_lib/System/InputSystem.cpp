/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "InputSystem.h"

#include <unordered_map>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Message/BroadcastMessage/CloseWindowMessage.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/KeyboardPressedMessage.h"
#include "Message/BroadcastMessage/KeyboardReleasedMessage.h"
#include "Message/MessageBus.h"

namespace {

std::unordered_map<sf::Keyboard::Key, FA::Keyboard::Key> supportedKeys = {
    {sf::Keyboard::Left, FA::Keyboard::Key::Left},     {sf::Keyboard::Right, FA::Keyboard::Key::Right},
    {sf::Keyboard::Down, FA::Keyboard::Key::Down},     {sf::Keyboard::Up, FA::Keyboard::Key::Up},
    {sf::Keyboard::Return, FA::Keyboard::Key::Return}, {sf::Keyboard::Escape, FA::Keyboard::Key::Escape},
    {sf::Keyboard::Num1, FA::Keyboard::Key::Num1},     {sf::Keyboard::Num2, FA::Keyboard::Key::Num2},
    {sf::Keyboard::Num3, FA::Keyboard::Key::Num3}};

}  // namespace

namespace FA {

InputSystem::InputSystem(MessageBus& messageBus, sf::RenderWindow& window)
    : messageBus_(messageBus)
    , window_(window)
{}

void InputSystem::Update(float deltaTime)
{
    sf::Event event;

    while (window_.pollEvent(event)) {
        PushEvent(event);
    }

    auto key = IsKeyPressed();
    if (key != Keyboard::Key::Undefined) {
        auto msg = std::make_shared<IsKeyPressedMessage>(key);
        messageBus_.PushMessage(msg);
    }
}

void InputSystem::PushEvent(const sf::Event& event)
{
    switch (event.type) {
        case sf::Event::KeyPressed: {
            auto it = supportedKeys.find(event.key.code);
            if (it != supportedKeys.end()) {
                auto msg = std::make_shared<KeyboardPressedMessage>(it->second);
                messageBus_.PushMessage(msg);
            }
            break;
        }
        case sf::Event::KeyReleased: {
            auto it = supportedKeys.find(event.key.code);
            if (it != supportedKeys.end()) {
                auto msg = std::make_shared<KeyboardReleasedMessage>(it->second);
                messageBus_.PushMessage(msg);
            }
            break;
        }
        case sf::Event::Closed: {
            auto msg = std::make_shared<CloseWindowMessage>();
            messageBus_.PushMessage(msg);
            break;
        }
    }
}

Keyboard::Key InputSystem::IsKeyPressed() const
{
    auto key = Keyboard::Key::Undefined;

    for (auto entry : supportedKeys) {
        if (sf::Keyboard::isKeyPressed(entry.first)) {
            key = entry.second;
        }
    }

    return key;
}

}  // namespace FA
