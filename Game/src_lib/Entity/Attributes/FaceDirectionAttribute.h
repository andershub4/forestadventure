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
    FaceDirectionAttribute(EntityService *owner);

    void SetDirection(FaceDirection direction);
    FaceDirection GetDirection() const;
    void SetAllDirections(const std::vector<FaceDirection> &allDirections);
    std::vector<FaceDirection> GetAllDirections() const;

private:
    FaceDirection direction_ = FaceDirection::Undefined;
    std::vector<FaceDirection> allDirections_{FaceDirection::Undefined};
};

}  // namespace Entity

}  // namespace FA
