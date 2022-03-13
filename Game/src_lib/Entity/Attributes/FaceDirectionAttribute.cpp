/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "FaceDirectionAttribute.h"

namespace FA {

namespace Entity {

FaceDirectionAttribute::FaceDirectionAttribute(EntityService *owner)
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

void FaceDirectionAttribute::SetAllDirections(const std::vector<FaceDirection> &allDirections)
{
    allDirections_ = allDirections;
}

std::vector<FaceDirection> FaceDirectionAttribute::GetAllDirections() const
{
    return allDirections_;
}

}  // namespace Entity

}  // namespace FA
