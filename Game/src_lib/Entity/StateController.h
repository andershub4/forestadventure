/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "Modes/BasicMode.h"
#include "StateMachine.h"

namespace FA {

namespace Keyboard {
enum class Key;
}

namespace Entity {

struct BasicEvent;
class Shape;

class StateController
{
public:
    StateController(EntityService& entityService);

    template <class T>
    std::shared_ptr<T> AddMode(bool startMode = false)
    {
        auto mode = std::make_shared<T>(&entityService_);
        AddMode(mode, startMode);
        return mode;
    }

    template <class T>
    std::unique_ptr<T> CreateState(std::shared_ptr<BasicEvent> event)
    {
        return std::make_unique<T>(*this, stateData_, entityService_, event);
    }

    std::shared_ptr<BasicMode> GetMode(ModeType modeType) const;
    void HandleIsKeyPressed(Keyboard::Key key);
    void HandleIsKeyReleased(Keyboard::Key key);
    void HandleKeyPressed(Keyboard::Key key);
    void HandleEvent(ModeType currentModeType, std::shared_ptr<BasicEvent> event);
    void Update(float deltaTime);
    void LateUpdate();
    void DrawTo(sf::RenderTarget& renderTarget);

    void Create(const PropertyData& data);
    void Init();
    void Update(ModeType currentModeType, std::shared_ptr<Shape> shape);
    void SetOnCreateCB(std::function<void(EntityService&, const PropertyData&)> onCreate);

private:
    std::unordered_map<ModeType, std::shared_ptr<BasicMode>> modes_;
    ModeType startMode_ = ModeType::None;
    std::function<void(EntityService&, const PropertyData&)> onCreate_{};
    StateMachine stateMachine_;
    BasicState::StateData stateData_;
    EntityService& entityService_;

private:
    void AddMode(std::shared_ptr<BasicMode> mode, bool startMode);
};

}  // namespace Entity

}  // namespace FA
