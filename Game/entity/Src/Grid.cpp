/*
 *	Copyright (C) 2025 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Grid.h"

#include <SFML/System/Vector2.hpp>

#include "CollisionHandlerIf.h"
#include "EntityDbIf.h"
#include "EntityIf.h"
#include "Logging.h"
#include "SfmlPrint.h"

namespace FA {

namespace Entity {

Grid::Grid(const sf::Vector2u &mapSize, const unsigned int cellSize, const EntityDbIf &entityDb,
           CollisionHandlerIf2 &colliderHandler)
    : cellSize_(cellSize)
    , mapSize_(mapSize)
    , entityDb_(entityDb)
    , collisionHandler_(colliderHandler)
{
    mapRect_ = sf::FloatRect(0.0f, 0.0f, static_cast<float>(mapSize.x), static_cast<float>(mapSize.y));
}

Grid::~Grid() = default;

void Grid::Add(EntityId id)
{
    const auto &entity = entityDb_.GetEntity(id);
    // entity.AddToGrid(*this)  // can be done in CollisionHAndler as well
}

bool Grid::IsValidEntity(EntityId id, const sf::Vector2f &position, const sf::Vector2u &size) const
{
    auto it = allEntities_.find(id);
    if (it != allEntities_.end()) {
        LOG_ERROR("%s already exist", DUMP(id));
        return false;
    }
    else {
        bool isInsideMap = mapRect_.contains(position);
        bool isSizeLessThanMap = size.x <= mapSize_.y && size.y <= mapSize_.y;
        bool isNonZeroSize = size.x > 0 && size.y > 0;
        bool validSize = isNonZeroSize && isSizeLessThanMap;

        if (!isInsideMap) {
            LOG_ERROR("%s with %s, is outside map", DUMP(id), DUMP(position));
            return false;
        }
        else if (!validSize) {
            LOG_ERROR("%s with %s, is invalid size", DUMP(id), DUMP(size));
            return false;
        }
    }

    return true;
}

void Grid::AddToCells(EntityId id, const sf::Vector2u &cellPosMin, const sf::Vector2u &cellPosMax)
{
    const auto &entity = entityDb_.GetEntity(id);
    bool isStatic = entity.IsStatic();

    std::vector<std::pair<int, int>> cellPositions;
    for (auto cellPosY = cellPosMin.y; cellPosY <= cellPosMax.y; cellPosY++) {
        for (auto cellPosX = cellPosMin.x; cellPosX <= cellPosMax.x; cellPosX++) {
            auto cellPos = std::make_pair(cellPosX, cellPosY);
            auto &cell = gridMap_[cellPos];

            if (isStatic) {
                cell.staticEntities_.insert(id);
            }
            else {
                cell.entities_.insert(id);
            }
            cellPositions.push_back(cellPos);
        }
    }
    entityToCellLookup_[id] = cellPositions;
}

void Grid::Add(EntityId id, const sf::Vector2f &position, const sf::Vector2u &size)
{
    if (IsValidEntity(id, position, size)) {
        allEntities_.insert(id);
        auto cellPosMin = WorldToCellCoord(position);
        auto cellPosMax = WorldToCellCoord(static_cast<sf::Vector2u>(position) + size);
        AddToCells(id, cellPosMin, cellPosMax);
    }
}

void Grid::Remove(EntityId id)
{
    auto it = allEntities_.find(id);
    if (it == allEntities_.end()) {
        LOG_WARN("%s does not exist", DUMP(id));
    }
    else {
        allEntities_.erase(id);
        RemoveFromCells(id);
    }
}

void Grid::RemoveFromCells(EntityId id)
{
    auto it = entityToCellLookup_.find(id);
    if (it != entityToCellLookup_.end()) {
        const auto &entity = entityDb_.GetEntity(id);
        bool isStatic = entity.IsStatic();
        auto cellPositions = it->second;
        for (const auto &cellPos : cellPositions) {
            auto &cell = gridMap_[cellPos];

            if (isStatic) {
                cell.staticEntities_.erase(id);
            }
            else {
                cell.entities_.erase(id);
            }

            if (cell.IsEmpty()) {
                gridMap_.erase(cellPos);
            }
        }
    }
    entityToCellLookup_.erase(id);
}

unsigned int Grid::Count() const
{
    return allEntities_.size();
}

void Grid::DetectCollisions()
{
    for (auto &entry : gridMap_) {
        auto &cell = entry.second;
        collisionHandler_.DetectCollisions(cell.entities_, cell.staticEntities_);
    }
}

void Grid::DetectOutsideTileMap()
{
    for (auto &entry : gridMap_) {
        auto &cell = entry.second;
        collisionHandler_.DetectOutsideTileMap(mapSize_, cell.entities_);
    }
}

void Grid::HandleCollisions()
{
    collisionHandler_.HandleCollisions();
}

void Grid::HandleOutsideTileMap()
{
    collisionHandler_.HandleOutsideTileMap();
}

sf::Vector2u Grid::WorldToCellCoord(const sf::Vector2f &position) const
{
    return static_cast<sf::Vector2u>(position) / cellSize_;
}

sf::Vector2u Grid::WorldToCellCoord(const sf::Vector2u &position) const
{
    return position / cellSize_;
}

void Grid::Move(EntityId id, const sf::Vector2f &position, const sf::Vector2u &size)
{
    RemoveFromCells(id);
    auto cellPosMin = WorldToCellCoord(position);
    auto cellPosMax = WorldToCellCoord(static_cast<sf::Vector2u>(position) + size);
    AddToCells(id, cellPosMin, cellPosMax);
}

}  // namespace Entity

}  // namespace FA
