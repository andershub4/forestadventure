/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

namespace FA {

namespace Shared {

class Animation;
class Image;
class SheetManager;
struct AnimationData;
struct ImageData;

}  // namespace Shared

namespace Entity {

class EntityService
{
public:
    EntityService(const Shared::SheetManager &sheetManager);
    ~EntityService();

    Shared::Animation MakeAnimation(const Shared::AnimationData &data) const;
    Shared::Image MakeImage(const Shared::ImageData &data) const;

private:
    const Shared::SheetManager &sheetManager_;
};

}  // namespace Entity

}  // namespace FA
