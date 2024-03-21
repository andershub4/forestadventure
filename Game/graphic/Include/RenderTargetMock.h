/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "RenderTargetIf.h"

namespace FA {

namespace Graphic {

class RenderTargetMock : public RenderTargetIf
{
public:
    MOCK_METHOD((void), draw, (const DrawableIf&), (override));
};

}  // namespace Graphic

}  // namespace FA
