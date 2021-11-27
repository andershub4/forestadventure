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

namespace Entity {

struct BasicEvent;
struct PropertyData;
class BasicMode;
class EntityService;
struct Action;

class ModeController
{
public:
    ModeController(EntityService& entityService);
    ~ModeController();

    template <class T>
    std::shared_ptr<T> AddMode(bool startMode = false)
    {
        auto mode = std::make_shared<T>(entityService_);
        AddMode(mode, startMode);
        return mode;
    }

    void HandleEvent(std::shared_ptr<BasicEvent> event);
    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget& renderTarget);

    void RegisterCreateCB(std::function<void(std::shared_ptr<BasicEvent> event)> onCreate);
    void RegisterDestroyCB(std::function<void(std::shared_ptr<BasicEvent> event)> onDestroy);

private:
    std::unordered_map<ModeType, std::shared_ptr<BasicMode>> modes_;
    std::shared_ptr<BasicMode> currentMode_ = nullptr;
    std::function<void(std::shared_ptr<BasicEvent> event)> onDestroy_{};
    EntityService& entityService_;

private:
    void AddMode(std::shared_ptr<BasicMode> mode, bool startMode);
    void DoAction(const Action& action, std::shared_ptr<BasicEvent> event = nullptr);
};

}  // namespace Entity

}  // namespace FA
