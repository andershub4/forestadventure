/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "FaceDirectionAttribute.h"

namespace FA {

namespace Entity {

FaceDirectionAttribute::FaceDirectionAttribute(PropertyHandler *owner)
    : BasicAttribute(owner)
{}

void FaceDirectionAttribute::SetDirection(FaceDirection direction)
{
    direction_ = direction;
}

FaceDirection FaceDirectionAttribute::GetDirection() const
{
    return direction_;
}

void FaceDirectionAttribute::SetAvailableDirections(const std::vector<FaceDirection> &directions)
{
    availableDirections_ = directions;
}

std::vector<FaceDirection> FaceDirectionAttribute::GetAvailableDirections() const
{
    return availableDirections_;
}

}  // namespace Entity

}  // namespace FA
