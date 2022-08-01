/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

namespace FA {

class Animation;
class Image;
class SheetManager;
struct AnimationData;
struct ImageData;

namespace Entity {

class EntityService
{
public:
    EntityService(const SheetManager &sheetManager);
    ~EntityService();

    Animation MakeAnimation(const AnimationData &data) const;
    Image MakeImage(const ImageData &data) const;

private:
    const SheetManager &sheetManager_;
};

}  // namespace Entity

}  // namespace FA
