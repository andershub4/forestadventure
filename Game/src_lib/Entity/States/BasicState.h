/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>

#include "Entity/ModeType.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

namespace Keyboard {
enum class Key;
}

namespace Entity {

class StateController;
struct PropertyData;
struct BasicEvent;
class EntityService;
class Shape;

class BasicState
{
public:
    struct StateData
    {
    };

    BasicState(StateController& stateController, StateData& stateData, EntityService& entityService);
    virtual ~BasicState();

    virtual void Create(const PropertyData& data) {}
    virtual void Update(float deltaTime) = 0;
    virtual void DrawTo(sf::RenderTarget& renderTarget) = 0;
    virtual std::string Name() const = 0;
    virtual ModeType GetModeType() const = 0;
    virtual void Enter() {}
    virtual void Exit() {}

    virtual void LateUpdate() {}
    virtual void OnInit() {}

    std::shared_ptr<Shape> GetShape() const;

    void HandleIsKeyPressed(Keyboard::Key key);
    void HandleIsKeyReleased(Keyboard::Key key);
    void HandleKeyPressed(Keyboard::Key key);

protected:
    StateData& stateData_;

protected:
    void Update();
    void InternalCreate(const PropertyData& data);
    void Start();
    void InternalEnter(std::shared_ptr<BasicEvent> event);
    void InternalExit();
    void InternalUpdate(float deltaTime);

private:
    EntityService& entityService_;
    StateController& stateController_;
};

}  // namespace Entity

}  // namespace FA
