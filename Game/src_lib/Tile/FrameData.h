/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>
#include <vector>

namespace FA {

namespace Tile {

struct Frame
{
    std::string texturePath_;
    int u_{};
    int v_{};
    int width_{};
    int height_{};
};

struct FrameData
{
    FrameData() = default;
    FrameData(const std::vector<Frame> &frames)
        : frames_(frames)
    {}
    bool IsAnimation() { return frames_.size() > 1; }
    Frame Front() { return frames_.front(); }
    std::vector<Frame> GetFrames() const { return frames_; }

private:
    std::vector<Frame> frames_;
};

}  // namespace Tile

}  // namespace FA
