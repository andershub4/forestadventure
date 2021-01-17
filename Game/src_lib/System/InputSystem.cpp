/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "InputSystem.h"

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
        ProcessEvent(event);
    }
}

void InputSystem::ProcessEvent(const sf::Event& event)
{
    switch (event.type) {
        case sf::Event::KeyPressed: {
            auto it = supportedKeys.find(event.key.code);
            auto key = (it != supportedKeys.end()) ? it->second : Keyboard::Key::Undefined;
            keyPressed_.clear();  // Let only one key be considered as pressed one at a time
            if (key != Keyboard::Key::Undefined) keyPressed_.insert(key);
            auto msg = std::make_shared<KeyboardPressedMessage>(key);
            messageBus_.PushMessage(msg);
            break;
        }
        case sf::Event::KeyReleased: {
            auto it = supportedKeys.find(event.key.code);
            auto key = (it != supportedKeys.end()) ? it->second : Keyboard::Key::Undefined;
            if (key != Keyboard::Key::Undefined) keyPressed_.erase(key);
            auto msg = std::make_shared<KeyboardReleasedMessage>(key);
            messageBus_.PushMessage(msg);
            break;
        }
        case sf::Event::Closed: {
            auto msg = std::make_shared<CloseWindowMessage>();
            messageBus_.PushMessage(msg);
            break;
        }
    }

    // This will give continuously messages when key is pressed. It is equivalent to sf::Keyboard::isKeyPressed(...).
    for (auto key : keyPressed_) {
        auto msg = std::make_shared<IsKeyPressedMessage>(key);
        messageBus_.PushMessage(msg);
    }
}

}  // namespace FA
