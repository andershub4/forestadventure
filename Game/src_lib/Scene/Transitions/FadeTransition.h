/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicTransition.h"
#include "Effect/FadeAnimation.h"

namespace FA {

namespace Scene {

class FadeTransition : public BasicTransition
{
public:
    FadeTransition(CreateSceneFn nextSceneFn);
    virtual ~FadeTransition();

    virtual void DrawTo(sf::RenderTarget& renderTarget) override;
    virtual void DrawTo(BasicComponent& component) override;
    virtual void Update(float deltaTime) override;
    virtual bool IsFinished() const override;

private:
    FadeAnimation fade_;
};

}  // namespace Scene

}  // namespace FA
