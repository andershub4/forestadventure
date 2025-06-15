/*
 *	Copyright (C) 2025 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "EntityDbIf.h"

namespace FA {

namespace Entity {

class EntityDbMock : public EntityDbIf
{
public:
    MOCK_METHOD((void), AddEntity, (std::unique_ptr<EntityIf>), (override));
    MOCK_METHOD((void), DeleteEntity, (EntityId), (override));
    MOCK_METHOD((EntityIf&), GetEntity, (EntityId), (const override));
};

}  // namespace Entity

}  // namespace FA
