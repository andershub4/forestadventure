/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicTransition.h"

namespace FA {

namespace Scene {

class NoneTransition : public BasicTransition
{
public:
    NoneTransition(CreateSceneFn nextSceneFn);
    virtual ~NoneTransition();

    virtual void DrawTo(sf::RenderTarget& renderTarget) override;
    virtual void DrawTo(BasicComponent& component) override;
    virtual void Update(float deltaTime) override;
    virtual bool IsFinished() const { return true; }
};

}  // namespace Scene

}  // namespace FA
