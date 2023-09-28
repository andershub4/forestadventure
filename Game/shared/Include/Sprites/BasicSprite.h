/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class ISprite;
class IRenderTarget;

}  // namespace Graphic

namespace Shared {

class BasicSprite
{
public:
    BasicSprite(std::shared_ptr<Graphic::ISprite> sprite);
    virtual ~BasicSprite() = default;

    virtual void Update(float deltaTime);  // delta time; time since previous time to current frame

    void SetPosition(const sf::Vector2f &position);
    void SetRotation(float rot);
    void DrawTo(Graphic::IRenderTarget &renderTarget) const;
    void Center();

protected:
    std::shared_ptr<Graphic::ISprite> sprite_;
};

}  // namespace Shared

}  // namespace FA
