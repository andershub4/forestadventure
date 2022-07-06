/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "InputSystem.h"

#include <algorithm>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Logging.h"
#include "Message/BroadcastMessage/CloseWindowMessage.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Message/BroadcastMessage/KeyReleasedMessage.h"
#include "Message/MessageBus.h"

namespace {

std::unordered_map<sf::Keyboard::Key, FA::Keyboard::Key> supportedKeys = {
    {sf::Keyboard::Left, FA::Keyboard::Key::Left},     {sf::Keyboard::Right, FA::Keyboard::Key::Right},
    {sf::Keyboard::Down, FA::Keyboard::Key::Down},     {sf::Keyboard::Up, FA::Keyboard::Key::Up},
    {sf::Keyboard::Return, FA::Keyboard::Key::Return}, {sf::Keyboard::Escape, FA::Keyboard::Key::Escape},
    {sf::Keyboard::Num1, FA::Keyboard::Key::Num1},     {sf::Keyboard::Num2, FA::Keyboard::Key::Num2},
    {sf::Keyboard::Num3, FA::Keyboard::Key::Num3},     {sf::Keyboard::RControl, FA::Keyboard::Key::RControl},
    {sf::Keyboard::Space, FA::Keyboard::Key::Space}};

std::unordered_map<sf::Keyboard::Key, FA::Keyboard::Key> supportedInstantKeys = {
    {sf::Keyboard::Left, FA::Keyboard::Key::Left},
    {sf::Keyboard::Right, FA::Keyboard::Key::Right},
    {sf::Keyboard::Down, FA::Keyboard::Key::Down},
    {sf::Keyboard::Up, FA::Keyboard::Key::Up}};

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

    ProcessIsKeyPressed();
}

void InputSystem::ProcessEvent(const sf::Event& event)
{
    switch (event.type) {
        case sf::Event::KeyPressed: {
            auto it = supportedKeys.find(event.key.code);
            auto key = (it != supportedKeys.end()) ? it->second : Keyboard::Key::Undefined;
            auto msg = std::make_shared<KeyPressedMessage>(key);
            pressedKeys_.emplace(key);
            messageBus_.SendMessage(msg);
            break;
        }
        case sf::Event::KeyReleased: {
            auto it = supportedKeys.find(event.key.code);
            auto key = (it != supportedKeys.end()) ? it->second : Keyboard::Key::Undefined;
            auto msg = std::make_shared<KeyReleasedMessage>(key);
            pressedKeys_.erase(key);
            messageBus_.SendMessage(msg);
            break;
        }
        case sf::Event::Closed: {
            auto msg = std::make_shared<CloseWindowMessage>();
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
        auto msg = std::make_shared<IsKeyPressedMessage>(k);
        messageBus_.SendMessage(msg);
    }
}

void InputSystem::ReleaseKeys()
{
    for (auto k : pressedKeys_) {
        auto msg = std::make_shared<KeyReleasedMessage>(k);
        messageBus_.SendMessage(msg);
    }
    pressedKeys_.clear();
}

}  // namespace FA
