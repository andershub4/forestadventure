/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

namespace FA {

namespace Shared {

class Screen
{
public:
    static constexpr unsigned int width = 1280;
    static constexpr unsigned int height = 780;
    static constexpr float width_f = static_cast<float>(width);
    static constexpr float height_f = static_cast<float>(height);

    static constexpr unsigned int centerX = width / 2;
    static constexpr unsigned int centerY = height / 2;
    static constexpr float centerX_f = width_f / 2.0;
    static constexpr float centerY_f = height_f / 2.0;
};

}  // namespace Shared

}  // namespace FA
