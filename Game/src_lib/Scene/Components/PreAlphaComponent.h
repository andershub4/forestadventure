/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "BasicComponent.h"

namespace FA {

namespace Scene {

class PreAlphaComponent : public BasicComponent
{
public:
    PreAlphaComponent(MessageBus& messageBus, const sf::IntRect& rect);
    virtual ~PreAlphaComponent();

    virtual ComponentId GetId() const override { return ComponentId::Intro; }
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void EnableInput(bool enable) override {}
    virtual void OnCreate() override;

private:
    sf::Font font_;
    sf::Text versionText_;
};

}  // namespace Scene

}  // namespace FA
