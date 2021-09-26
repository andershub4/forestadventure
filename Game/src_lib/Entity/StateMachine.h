/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "ComponentHandler.h"
#include "States/BasicState.h"

namespace FA {

namespace Entity {

class StateMachine
{
public:
    StateMachine(BasicState::StateData& stateData, const ComponentHandler& componentHandler);
    ~StateMachine();

    void Update(float deltaTime);
    void Awake();
    void LateUpdate();
    void DrawTo(sf::RenderTarget& renderTarget);
    void SetState(std::unique_ptr<BasicState> newState);

    template <class T>
    std::shared_ptr<T> GetComponent() const
    {
        return componentHandler_.GetComponent<T>();
    }

    template <class T>
    std::shared_ptr<T> AddComponent()
    {
        return componentHandler_.AddComponent<T>();
    }

    void OnInitStateData(const AnimationDb& animationDb);
    void OnStartMove(MoveDirection moveDir, FaceDirection faceDir);
    void OnStopMove();
    void OnAttack();
    void OnAttackWeapon();

private:
    std::unique_ptr<BasicState> currentState_;
    ComponentHandler componentHandler_;
};

}  // namespace Entity

}  // namespace FA
