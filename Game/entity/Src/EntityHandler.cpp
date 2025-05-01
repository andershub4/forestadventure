/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityHandler.h"

#include <memory>

#include "EntityDb.h"
#include "EntityIf.h"
#include "EntityService.h"
#include "Factory.h"

namespace FA {

namespace Entity {

EntityHandler::EntityHandler(EntityDb &entityDb)
    : entityDb_(entityDb)
{}

EntityHandler::~EntityHandler() = default;

void EntityHandler::Update(float deltaTime)
{
    for (const auto id : allEntities_) {
        entityDb_.GetEntity(id).Update(deltaTime);
    }
}

EntityId EntityHandler::AddEntity(const Shared::EntityData &data, const Factory &factory,
                                  Shared::MessageBus &messageBus, const Shared::TextureManager &textureManager,
                                  const Shared::SheetManager &sheetManager, const Shared::CameraViews &cameraViews,
                                  EntityLifeHandler &entityLifeHandler, const ObjIdTranslator &objIdTranslator)
{
    auto service = std::make_unique<Entity::EntityService>(messageBus, textureManager, sheetManager, cameraViews,
                                                           entityDb_, entityLifeHandler, objIdTranslator);
    auto entity = factory.Create(data, std::move(service));
    entity->Init();
    auto id = entity->GetId();
    entityDb_.AddEntity(std::move(entity));
    allEntities_.insert(id);
    return id;
}

void EntityHandler::RemoveEntity(EntityId id)
{
    allEntities_.erase(id);
    entityDb_.DeleteEntity(id);
}

}  // namespace Entity

}  // namespace FA
