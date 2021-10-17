/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>

#include "Entity/EntityService.h"
#include "Enum/FaceDirection.h"
#include "Enum/MoveDirection.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

class AnimationDb;

namespace Entity {

class StateMachine;
struct PropertyData;

class BasicState
{
public:
    struct StateData
    {
    };

    BasicState(StateMachine& stateMachine, StateData& stateData, EntityService& entityService);
    virtual ~BasicState();

    virtual void Create(const PropertyData& data) {}
    virtual void Update(float deltaTime) = 0;
    virtual void DrawTo(sf::RenderTarget& renderTarget) = 0;
    virtual std::string Name() const = 0;
    virtual void Enter() {}
    virtual void Exit() {}

    virtual void Awake();
    virtual void LateUpdate() {}
    virtual void OnInitStateData(const AnimationDb& animationDb) {}
    virtual void OnStartMove(MoveDirection moveDir, FaceDirection faceDir) {}
    virtual void OnStopMove() {}
    virtual void OnAttack() {}
    virtual void OnAttackWeapon() {}

    void SwitchState(std::unique_ptr<BasicState> newState);

    template <class StateT, typename... Args>
    void SwitchState(Args&&... args)
    {
        static_assert(std::is_base_of<BasicState, StateT>::value, "StateT must derive from BasicState");

        SwitchState(std::make_unique<StateT>(stateMachine_, stateData_, entityService_, std::forward<Args>(args)...));
    }

    template <class T>
    std::shared_ptr<T> GetAttribute() const
    {
        return entityService_.GetAttribute<T>();
    }

    template <class T>
    std::shared_ptr<T> GetBehavior() const
    {
        return entityService_.GetBehavior<T>();
    }

    template <class T>
    std::shared_ptr<T> AddAttribute()
    {
        return entityService_.AddAttribute<T>();
    }

    template <class T>
    std::shared_ptr<T> AddBehavior()
    {
        return entityService_.AddBehavior<T>();
    }

    void InitProperties(const AnimationDb& animationDb);

protected:
    StateData& stateData_;

private:
    EntityService& entityService_;
    StateMachine& stateMachine_;
};

}  // namespace Entity

}  // namespace FA
