/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ConfigurationBuilder.h"

namespace FA {

namespace Entity {

ConfigurationBuilder::ConfigurationBuilder(const sf::Vector2f &position, float scale, FaceDirection faceDir)
{
    configuration_ = std::make_unique<Configuration>();
    configuration_->faceDir_ = faceDir;
    configuration_->transform_ = std::make_unique<TransformComponent>(position, scale);
}

ConfigurationBuilder::~ConfigurationBuilder() = default;

void ConfigurationBuilder::AddSprite(const AnimationComponent &animation)
{
    configuration_->sprite_ = std::make_unique<SpriteComponent>(*configuration_->transform_, animation);
}

void ConfigurationBuilder::AddMovement(float velocity)
{
    configuration_->movement_ = std::make_unique<MovementComponent>(*configuration_->transform_, velocity);
}

std::unique_ptr<Configuration> ConfigurationBuilder::Build()
{
    return std::move(configuration_);
}

}  // namespace Entity

}  // namespace FA
