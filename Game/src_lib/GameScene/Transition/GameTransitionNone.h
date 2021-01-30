/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "GameTransition.h"

namespace FA {

class GameTransitionNone : public GameTransition
{
public:
    GameTransitionNone(CreateSceneFn nextSceneFn);
    virtual ~GameTransitionNone();

    virtual void DrawTo(sf::RenderTarget& renderTarget) override;
    virtual void DrawTo(SceneComponent& sceneComponent) override;
    virtual void Update(float deltaTime) override;
    virtual bool IsFinished() const { return true; }
};

}  // namespace FA
