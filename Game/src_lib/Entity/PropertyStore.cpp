/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PropertyStore.h"

#include "BasicProperty.h"

namespace FA {

namespace Entity {

void PropertyStore::Awake()
{
    for (const auto &c : properties_) {
        c.second->Awake();
    }
}

}  // namespace Entity

}  // namespace FA
