/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ConfigurationBuilder.h"

#include "Components/MovementComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"

namespace FA {

namespace Entity {

ConfigurationBuilder::ConfigurationBuilder(const sf::Vector2f &position, float scale, FaceDirection faceDir)
{
    configuration_ = std::make_unique<Configuration>();
    configuration_->faceDir_ = faceDir;
    configuration_->AddComponent<TransformComponent>(position, scale);
}

ConfigurationBuilder::~ConfigurationBuilder() = default;

void ConfigurationBuilder::AddSprite(const AnimationComponent &animation)
{
    auto t = configuration_->GetComponent<TransformComponent>();
    configuration_->AddComponent<SpriteComponent>(*t, animation);
}

void ConfigurationBuilder::AddMovement(float velocity)
{
    auto t = configuration_->GetComponent<TransformComponent>();
    configuration_->AddComponent<MovementComponent>(*t, velocity);
}

std::unique_ptr<Configuration> ConfigurationBuilder::Build()
{
    return std::move(configuration_);
}

}  // namespace Entity

}  // namespace FA
