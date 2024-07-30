/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

namespace FA {

namespace Entity {

template <class ValueT>
class SelectionBaseIf
{
public:
    virtual ~SelectionBaseIf() = default;
    virtual ValueT *Get() const = 0;
};

}  // namespace Entity

}  // namespace FA
