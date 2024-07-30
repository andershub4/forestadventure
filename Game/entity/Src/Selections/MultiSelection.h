/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "SelectionBaseIf.h"

#include "Logging.h"

namespace FA {

namespace Entity {

template <class ValueT, class KeyT>
class MultiSelection : public SelectionBaseIf<ValueT>
{
    using SelectFn = std::function<ValueT *(const std::unordered_map<KeyT, std::shared_ptr<ValueT>> &)>;

public:
    MultiSelection(const KeyT *const key)
    {
        selectFn_ = [key](const std::unordered_map<KeyT, std::shared_ptr<ValueT>> &map) {
            bool found = map.find(*key) != map.end();
            ValueT *result = nullptr;

            if (found) {
                result = map.at(*key).get();
            }
            else {
                LOG_ERROR("%s can not be found", DUMP(key));
            }

            return result;
        };
    }

    void RegisterSelection(const KeyT &key, std::shared_ptr<ValueT> selection)
    {
        auto it = map_.find(key);
        if (it != map_.end()) {
            LOG_WARN("%s is already registered", DUMP(key));
        }
        else {
            map_.insert({key, selection});
        }
    }

    virtual ValueT *Get() const override { return selectFn_(map_); }

private:
    SelectFn selectFn_;
    std::unordered_map<KeyT, std::shared_ptr<ValueT>> map_;
};

}  // namespace Entity

}  // namespace FA
