/*
 *	Copyright (C) 2025 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "Id.h"
#include "SfmlFwd.h"

namespace FA {

namespace Entity {

class EntityDbIf;
class CollisionHandlerIf2;

class Grid
{
public:
    Grid(const sf::Vector2u &mapSize, const unsigned int cellSize, const EntityDbIf &entityDb,
         CollisionHandlerIf2 &colliderHandler);
    ~Grid();

    void Add(EntityId id);
    void Add(EntityId id, const sf::Vector2f &position, const sf::Vector2u &size);
    void Remove(EntityId);
    void DetectCollisions();
    void DetectOutsideTileMap();
    void HandleCollisions();
    void HandleOutsideTileMap();
    void Move(EntityId id, const sf::Vector2f &position, const sf::Vector2u &size);

    unsigned int Count() const;

private:
    class Cell
    {
    public:
        bool IsEmpty() const { return entities_.empty() && staticEntities_.empty(); }

        std::unordered_set<EntityId> entities_;
        std::unordered_set<EntityId> staticEntities_;
    };

    unsigned int cellSize_{};
    const sf::Vector2u mapSize_{};
    const EntityDbIf &entityDb_;
    CollisionHandlerIf2 &collisionHandler_;
    std::map<std::pair<int, int>, Cell> gridMap_;
    std::unordered_set<EntityId> allEntities_;
    std::unordered_set<EntityId> allStaticEntities_;
    sf::FloatRect mapRect_{};
    std::unordered_map<EntityId, std::vector<std::pair<int, int>>> entityToCellLookup_;

private:
    sf::Vector2u WorldToCellCoord(const sf::Vector2u &position) const;
    sf::Vector2u WorldToCellCoord(const sf::Vector2f &position) const;
    bool IsValidEntity(EntityId id, const sf::Vector2f &position, const sf::Vector2u &size) const;
    void AddToCells(EntityId id, const sf::Vector2u &cellPosMin, const sf::Vector2u &cellPosMax);
    void RemoveFromCells(EntityId id);
};

}  // namespace Entity

}  // namespace FA
