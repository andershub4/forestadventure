/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "BasicLayer.h"

namespace FA {

namespace Scene {

class IntroLayer : public BasicLayer
{
public:
    IntroLayer(MessageBus& messageBus, const sf::IntRect& rect);
    virtual ~IntroLayer();

    virtual std::string Name() const override { return "Intro"; }
    virtual LayerId GetId() const override { return LayerId::Intro; }
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void EnableInput(bool enable) override {}
    virtual void OnCreate() override;

private:
    sf::Font font_;
    sf::Text introText_;
    sf::Text pressText_;
};

}  // namespace Scene

}  // namespace FA
