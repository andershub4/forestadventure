/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "FaceDirectionComponent.h"

namespace FA {

namespace Entity {

void FaceDirectionComponent::SetDirection(FaceDirection direction)
{
    direction_ = direction;
}

FaceDirection FaceDirectionComponent::GetDirection() const
{
    return direction_;
}

}  // namespace Entity

}  // namespace FA
