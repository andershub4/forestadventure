/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ComponentStore.h"

#include "Entity/Components/BasicComponent.h"

namespace FA {

namespace Entity {

void ComponentStore::Awake()
{
    for (const auto &c : components_) {
        c.second->Awake();
    }
}

}  // namespace Entity

}  // namespace FA
