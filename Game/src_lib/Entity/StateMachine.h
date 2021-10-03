/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "PropertyHandler.h"
#include "States/BasicState.h"

namespace FA {

namespace Entity {

class StateMachine
{
public:
    StateMachine(BasicState::StateData& stateData, const PropertyHandler& propertyHandler);
    ~StateMachine();

    void Update(float deltaTime);
    void Awake();
    void LateUpdate();
    void DrawTo(sf::RenderTarget& renderTarget);
    void SetState(std::unique_ptr<BasicState> newState);

    template <class T>
    std::shared_ptr<T> GetAttribute() const
    {
        return propertyHandler_.GetAttribute<T>();
    }

    template <class T>
    std::shared_ptr<T> GetBehavior() const
    {
        return propertyHandler_.GetBehavior<T>();
    }

    template <class T>
    std::shared_ptr<T> AddAttribute()
    {
        return propertyHandler_.AddAttribute<T>();
    }

    template <class T>
    std::shared_ptr<T> AddBehavior()
    {
        return propertyHandler_.AddBehavior<T>();
    }

    void OnInitStateData(const AnimationDb& animationDb);
    void OnStartMove(MoveDirection moveDir, FaceDirection faceDir);
    void OnStopMove();
    void OnAttack();
    void OnAttackWeapon();

private:
    std::unique_ptr<BasicState> currentState_;
    PropertyHandler propertyHandler_;
};

}  // namespace Entity

}  // namespace FA
