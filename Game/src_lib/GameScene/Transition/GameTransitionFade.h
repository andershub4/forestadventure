/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Effect/FadeAnimation.h"
#include "GameTransition.h"

namespace FA {

class GameTransitionFade : public GameTransition
{
public:
    GameTransitionFade(CreateSceneFn nextSceneFn);
    virtual ~GameTransitionFade();

    virtual void DrawTo(sf::RenderTarget& renderTarget) override;
    virtual void DrawTo(SceneComponent& sceneComponent) override;
    virtual void Update(float deltaTime) override;
    virtual bool IsFinished() const override;

private:
    FadeAnimation fade_;
};

}  // namespace FA
