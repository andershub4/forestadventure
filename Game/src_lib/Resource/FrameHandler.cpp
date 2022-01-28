/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "FrameHandler.h"

#include "SheetManager.h"

namespace FA {

namespace {

SpriteSheet::Frame CreateFrame(const SpriteSheet& sheet, const sf::Vector2u position)
{
    SpriteSheet::Frame f;

    if (sheet.IsValid()) {
        f = sheet.At(position);
    }

    return f;
}

SpriteSheet::FrameSeq CreateFrameSeq(const SpriteSheet& sheet, const sf::Vector2u start, unsigned int n,
                                     unsigned int defaultIndex)
{
    SpriteSheet::FrameSeq f;

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
    auto frameSeq = CreateFrameSeq(sheet, location.start_, location.nRects_, location.defaultIndex_);

    if (frameSeq.isValid_) {
        auto rects = data.mirror_ ? SpriteSheet::MirrorX(frameSeq.rects_) : frameSeq.rects_;
        return Animation(frameSeq.texture_, rects, frameSeq.defaultIndex_, t);
    }

    return Animation();
}

Image FrameHandler::MakeImage(const ImageData& data) const
{
    auto sheet = sheetManager_.GetSheet(data.sheetId_);
    auto frame = CreateFrame(sheet, data.position_);

    if (frame.isValid_) {
        return Image(frame.texture_, frame.rect_, data.rotation_);
    }

    return Image();
}

}  // namespace FA
