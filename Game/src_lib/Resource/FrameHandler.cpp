/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "FrameHandler.h"

#include "SheetManager.h"

namespace FA {

namespace {

SpriteSheet::SingleFrame CreateSingleFrame(const SpriteSheet& sheet, const sf::Vector2u position)
{
    SpriteSheet::SingleFrame f;

    if (sheet.IsValid()) {
        f = sheet.At(position);
    }

    return f;
}

SpriteSheet::FrameData CreateFrameData(const SpriteSheet& sheet, const sf::Vector2u start, unsigned int n,
                                       unsigned int defaultIndex)
{
    SpriteSheet::FrameData f;

    if (sheet.IsValid()) {
        f = sheet.Scan(start, n, defaultIndex);
    }

    return f;
}

}  // namespace

FrameHandler::FrameHandler(const SheetManager& sheetManager)
    : sheetManager_(sheetManager)
{}

Animation FrameHandler::MakeAnimation(const AnimationData& data) const
{
    float t = 0.1f;

    auto location = data.locationData_;
    auto sheet = sheetManager_.GetSheet(data.sheetId_);
    auto frameData = CreateFrameData(sheet, location.start_, location.nFrames_, location.defaultFrame_);

    if (frameData.isValid_) {
        auto frames = data.mirror_ ? SpriteSheet::MirrorX(frameData.frames_) : frameData.frames_;
        return Animation(frameData.texture_, frames, frameData.defaultFrame_, t);
    }

    return Animation();
}

Image FrameHandler::MakeImage(const ImageData& data) const
{
    auto sheet = sheetManager_.GetSheet(data.sheetId_);
    auto singleFrame = CreateSingleFrame(sheet, data.position_);

    if (singleFrame.isValid_) {
        return Image(singleFrame.texture_, singleFrame.frame_, data.rotation_);
    }

    return Image();
}

}  // namespace FA
