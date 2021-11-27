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
    currentMode_ = AddMode<UninitializedMode>();
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

void ModeController::AddMode(std::shared_ptr<BasicMode> mode, bool startMode)
{
    mode->BindAction(Action::Call(onDestroy_), EventType::Destroy);

    auto modeType = mode->GetModeType();
    entityService_.AddModeType(modeType);
    modes_[modeType] = mode;
    mode->Awake();

    if (startMode) {
        startMode_ = modeType;
        auto u = modes_.at(ModeType::Uninitialized);
        u->BindAction(Action::ChangeTo(startMode_), EventType::Init);
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
