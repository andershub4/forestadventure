/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <vector>

#include "SfmlFwd.h"

namespace FA {

namespace Shared {

class BasicSprite
{
public:
    BasicSprite() = default;
    BasicSprite(std::shared_ptr<sf::Sprite> sprite);
    ~BasicSprite() = default;

    virtual void Update(float deltaTime) = 0;  // delta time; time since previous time to current frame

    void SetPosition(const sf::Vector2f &position);
    void SetRotation(float rot);
    void DrawTo(sf::RenderTarget &renderTarget);
    void Center();
    bool IsValid() const;

protected:
    std::shared_ptr<sf::Sprite> sprite_;

private:
    bool isValid_ = false;
};

}  // namespace Shared

}  // namespace FA
