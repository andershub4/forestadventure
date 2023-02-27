/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimationSprite.h"

#include "Logging.h"

namespace FA {

namespace Entity {

AnimationSprite::AnimationSprite(const AnimationTable &table, std::function<void(const Shared::Animation &)> updateFn,
                                 bool center)
    : table_(table)
    , updateFn_(updateFn)
    , center_(center)
{}

AnimationSprite::AnimationSprite(const AnimationTable &table, bool center)
    : table_(table)
    , updateFn_([](const Shared::Animation &) {})
    , center_(center)
{}

AnimationSprite::~AnimationSprite() = default;

void AnimationSprite::Enter()
{
    currentAnimation_ = table_.GetAnimation();
    if (currentAnimation_.IsValid()) {
        currentAnimation_.Start();
    }
}

void AnimationSprite::Update(float deltaTime)
{
    if (currentAnimation_.IsValid()) {
        currentAnimation_.Update(deltaTime);
        currentAnimation_.ApplyTo(sprite_);
        if (center_) {
            sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
        }
        updateFn_(currentAnimation_);
    }
}

}  // namespace Entity

}  // namespace FA
