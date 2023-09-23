/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "IRenderTarget.h"

namespace FA {

namespace Graphic {

class RenderTargetMock : public IRenderTarget
{
public:
    MOCK_METHOD((void), draw, (const IDrawable&), (override));
};

}  // namespace Graphic

}  // namespace FA
