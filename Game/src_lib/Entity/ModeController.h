/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "Fwd/SfmlFwd.h"
#include "ModeType.h"

namespace FA {

namespace Keyboard {
enum class Key;
}

namespace Entity {

struct BasicEvent;
struct PropertyData;
class BasicMode;
class EntityService;

class ModeController
{
public:
    ModeController(EntityService& entityService);
    ~ModeController();

    template <class T>
    std::shared_ptr<T> AddMode(bool startMode = false)
    {
        auto mode = std::make_shared<T>(&entityService_);
        AddMode(mode, startMode);
        return mode;
    }

    void HandleIsKeyPressed(Keyboard::Key key);
    void HandleIsKeyReleased(Keyboard::Key key);
    void HandleKeyPressed(Keyboard::Key key);
    void HandleEvent(std::shared_ptr<BasicEvent> event);
    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget& renderTarget);

    void Create(const PropertyData& data);
    void Init();
    void SetOnCreateCB(std::function<void(EntityService&, const PropertyData&)> onCreate);

private:
    std::unordered_map<ModeType, std::shared_ptr<BasicMode>> modes_;
    std::shared_ptr<BasicMode> currentMode_ = nullptr;
    ModeType startMode_ = ModeType::None;
    std::function<void(EntityService&, const PropertyData&)> onCreate_{};
    EntityService& entityService_;

private:
    void AddMode(std::shared_ptr<BasicMode> mode, bool startMode);
};

}  // namespace Entity

}  // namespace FA
