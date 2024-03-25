/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "SfmlFwd.h"
#include "ViewIf.h"

namespace FA {

namespace Graphic {

class View : public ViewIf
{
public:
    View();

    virtual void setSize(const sf::Vector2f &size) override;
    virtual void zoom(float factor) override;
    virtual void setCenter(const sf::Vector2f &center) override;

private:
    std::shared_ptr<sf::View> view_;

    friend class RenderTexture;

private:
    operator const sf::View &() const { return *view_; };
};

}  // namespace Graphic

}  // namespace FA
