/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "States/BasicState.h"

namespace FA {

namespace Keyboard {
enum class Key;
}

namespace Entity {

class BasicState;

class StateMachine
{
public:
    StateMachine(EntityService& entityService);
    ~StateMachine();

    void Init(std::unique_ptr<BasicState> state);
    void HandleIsKeyPressed(Keyboard::Key key);
    void HandleIsKeyReleased(Keyboard::Key key);
    void HandleKeyPressed(Keyboard::Key key);
    void Update(float deltaTime);
    void LateUpdate();
    void DrawTo(sf::RenderTarget& renderTarget);
    void SetState(std::unique_ptr<BasicState> newState);

private:
    std::unique_ptr<BasicState> currentState_;
    BasicState::StateData stateData_;
};

}  // namespace Entity

}  // namespace FA
