/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "SequenceIf.h"

#include <vector>

#include "Logging.h"

namespace FA {

namespace Shared {

template <class T>
class Sequence : public SequenceIf<T>
{
public:
    Sequence(float switchTime)
        : switchTime_(switchTime)
        , time_(0.0)
    {}

    virtual void Update(float deltaTime) override
    {
        if (!isStopped_ && nElements_ > 1) {
            time_ += deltaTime;

            if (time_ >= switchTime_) {
                time_ = 0.0;
                ++iElement_ %= nElements_;
                isCompleted_ = (iElement_ == 0);
            }
        }
    }
    virtual T GetCurrent() const override { return nElements_ >= 1 ? elements_[iElement_] : T{}; }
    virtual void Start() override
    {
        isCompleted_ = false;
        if (nElements_ <= 0) {
            LOG_WARN("Can't start sequence, no elements");
        }
        else {
            isStopped_ = false;
        }
    }
    virtual void Stop() override
    {
        isStopped_ = true;
        iElement_ = 0;
    }
    virtual bool IsCompleted() const override { return nElements_ > 1 ? isCompleted_ : true; }
    virtual void Add(const T &element) override
    {
        if (!isStopped_) {
            LOG_WARN("Can't add element when sequence is started");
            return;
        }

        elements_.push_back(element);
        nElements_ = elements_.size();
    }

private:
    bool isStopped_ = true;
    float switchTime_{};  // time before to switch to next frame
    float time_{};        // time since we last switched frame
    unsigned int iElement_{};
    std::vector<T> elements_;
    unsigned int nElements_{};
    bool isCompleted_ = false;
};

}  // namespace Shared

}  // namespace FA
