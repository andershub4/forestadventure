/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "VelocityAttribute.h"

namespace FA {

namespace Entity {

VelocityAttribute::VelocityAttribute(EntityService *owner)
    : BasicAttribute(owner)
{}

void VelocityAttribute::SetVelocity(float velocity)
{
    velocity_ = velocity;
}

float VelocityAttribute::GetVelocity() const
{
    return velocity_;
}

}  // namespace Entity

}  // namespace FA
