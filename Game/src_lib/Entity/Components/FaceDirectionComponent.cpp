/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "FaceDirectionComponent.h"

namespace FA {

namespace Entity {

FaceDirectionComponent::FaceDirectionComponent(ComponentHandler *owner)
    : BasicComponent(owner)
{}

void FaceDirectionComponent::SetDirection(FaceDirection direction)
{
    direction_ = direction;
}

FaceDirection FaceDirectionComponent::GetDirection() const
{
    return direction_;
}

void FaceDirectionComponent::SetAvailableDirections(const std::vector<FaceDirection> &directions)
{
    availableDirections_ = directions;
}

std::vector<FaceDirection> FaceDirectionComponent::GetAvailableDirections() const
{
    return availableDirections_;
}

}  // namespace Entity

}  // namespace FA
