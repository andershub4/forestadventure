/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicMode.h"

namespace FA {

namespace Entity {

class FaceDirectionAttribute;

class AttackMode : public BasicMode
{
public:
    AttackMode(EntityService &entityService);

    virtual void Enter(std::shared_ptr<BasicEvent> event) override;

    virtual void Awake() override;
    virtual void Update(float deltaTime) override;
    virtual ModeType GetModeType() const override { return ModeType::Attack; }

private:
    std::shared_ptr<FaceDirectionAttribute> faceDirection_ = nullptr;
    std::shared_ptr<Shape> shape_ = nullptr;
};

}  // namespace Entity

}  // namespace FA
