/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include <SFML/System/Vector2.hpp>

#include "BasicAttribute.h"
#include "Enum/FaceDirection.h"

namespace FA {

namespace Entity {

class FaceDirectionAttribute : public BasicAttribute
{
public:
    FaceDirectionAttribute(PropertyHandler *owner);

    virtual void Update(float deltaTime) override {}

    void SetDirection(FaceDirection direction);
    FaceDirection GetDirection() const;
    void SetAvailableDirections(const std::vector<FaceDirection> &directions);
    std::vector<FaceDirection> GetAvailableDirections() const;

private:
    FaceDirection direction_ = FaceDirection::Down;
    std::vector<FaceDirection> availableDirections_;
};

}  // namespace Entity

}  // namespace FA
