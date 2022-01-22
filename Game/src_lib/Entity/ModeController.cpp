/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ModeController.h"

#include "EntityService.h"
#include "Events/BasicEvent.h"
#include "Modes/UninitializedMode.h"

namespace FA {

namespace Entity {

ModeController::ModeController(EntityService& entityService)
    : entityService_(entityService)
{
    currentMode_ = RegisterMode<UninitializedMode>();
    currentMode_->Enter(nullptr);
}

ModeController::~ModeController()
{
    currentMode_->Exit();
}

void ModeController::HandleEvent(std::shared_ptr<BasicEvent> event)
{
    auto action = currentMode_->GetAction(event->GetEventType());
    DoAction(action, event);
}

void ModeController::QueueInitEvents(std::shared_ptr<BasicEvent> event)
{
    queuedInitEvents_.push_back(event);
}

void ModeController::HandleQueuedInitEvents()
{
    for (auto event : queuedInitEvents_) {
        HandleEvent(event);
    }
    queuedInitEvents_.clear();
}

void ModeController::Update(float deltaTime)
{
    currentMode_->Update(deltaTime);

    auto action = currentMode_->PollAction();
    DoAction(action);
}

void ModeController::DrawTo(sf::RenderTarget& renderTarget)
{
    currentMode_->DrawTo(renderTarget);
}

void ModeController::RegisterMode(std::shared_ptr<BasicMode> mode, bool startMode)
{
    mode->BindAction(Action::Call(onDestroy_), EventType::Destroy);

    auto modeType = mode->GetModeType();
    modes_[modeType] = mode;
    mode->Register();

    if (startMode) {
        auto u = modes_.at(ModeType::Uninitialized);
        u->BindAction(Action::ChangeTo(modeType), EventType::Init);
    }
}

void ModeController::RegisterCreateCB(std::function<void(std::shared_ptr<BasicEvent>)> onCreate)
{
    auto u = modes_.at(ModeType::Uninitialized);
    u->BindAction(Action::Call(onCreate), EventType::Create);
}

void ModeController::RegisterDestroyCB(std::function<void(std::shared_ptr<BasicEvent>)> onDestroy)
{
    onDestroy_ = onDestroy;
}

void ModeController::DoAction(const Action& action, std::shared_ptr<BasicEvent> event)
{
    if (action.cb_) action.cb_(event);

    auto nextModeType = action.modeType_;
    if (nextModeType != ModeType::None) {
        currentMode_->Exit();
        currentMode_ = modes_.at(nextModeType);
        currentMode_->Enter(event);
    }
}

}  // namespace Entity

}  // namespace FA
