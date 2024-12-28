/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

namespace FA {

namespace Graphic {

class DrawableIf;

}  // namespace Graphic

namespace Shared {

template <class FrameT>
struct AnimationTraits
{
    using DrawableT = Graphic::DrawableIf;
};

}  // namespace Shared

}  // namespace FA
