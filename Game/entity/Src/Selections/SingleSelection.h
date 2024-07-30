/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "SelectionBaseIf.h"

namespace FA {

namespace Entity {

template <class ValueT>
class SingleSelection : public SelectionBaseIf<ValueT>
{
public:
    SingleSelection(std::shared_ptr<ValueT> selection)
        : selection_(selection)
    {}

    virtual ValueT *Get() const override { return selection_.get(); }

private:
    std::shared_ptr<ValueT> selection_;
};

}  // namespace Entity

}  // namespace FA
