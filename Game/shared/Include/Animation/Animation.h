/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "AnimationIf.h"

#include "ColliderTraits.h"
#include "ImageTraits.h"
#include "SequenceIf.h"

namespace FA {

namespace Shared {

template <class FrameT>
class Animation : public AnimationIf<FrameT>
{
    using AnimationIf<FrameT>::DrawableType;

public:
    Animation(std::shared_ptr<SequenceIf<FrameT>> seq, bool center = true)
        : seq_(seq)
        , center_(center)
    {
        validSeq_ = !seq->IsEmpty();
    }

    virtual void Update(float deltaTime) override  // delta time; time since previous time to current frame
    {
        if (validSeq_) {
            seq_->Update(deltaTime);
        }
    }

    virtual void ApplyTo(DrawableType &drawable) const override
    {
        auto frame = seq_->GetCurrent();
        AnimationTraits<FrameT>::Apply(frame, drawable, center_);
    }

    virtual void Start() override { seq_->Start(); }
    virtual void Stop() override { seq_->Stop(); }
    virtual void Restart() override { seq_->Restart(); }
    virtual bool IsCompleted() const override { return seq_->IsCompleted(); }

private:
    std::shared_ptr<SequenceIf<FrameT>> seq_;
    bool center_{false};
    bool validSeq_{false};
};

}  // namespace Shared

}  // namespace FA
