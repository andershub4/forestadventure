/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "StateController.h"

#include "Logging.h"
#include "Modes/UninitializedMode.h"
#include "Events/BasicEvent.h"
#include "Shapes/BasicShape.h"
#include "EntityService.h"

namespace FA {

namespace Entity {

StateController::StateController(EntityService& entityService)
    : stateMachine_(entityService)
    , entityService_(entityService)
{
    auto u = AddMode<UninitializedMode>();
    auto s = u->CreateState(*this, nullptr);
    stateMachine_.Init(std::move(s));
}

std::shared_ptr<BasicMode> StateController::GetMode(ModeType modeType) const
{
    return modes_.at(modeType);
}

void StateController::HandleIsKeyPressed(Keyboard::Key key)
{
    stateMachine_.HandleIsKeyPressed(key);
}

void StateController::HandleIsKeyReleased(Keyboard::Key key)
{
    stateMachine_.HandleIsKeyReleased(key);
}

void StateController::HandleKeyPressed(Keyboard::Key key)
{
    stateMachine_.HandleKeyPressed(key);
}

void StateController::HandleEvent(ModeType currentModeType, std::shared_ptr<BasicEvent> event)
{
    auto currentMode = modes_.at(currentModeType);

    auto action = currentMode->GetAction(event->GetEventType());

    if (action.modeType_ != ModeType::None) {
        if (action.cb_) action.cb_(event);

        auto nextModeType = action.modeType_;
        if (nextModeType != ModeType::None) {
            auto nextMode = modes_.at(nextModeType);
            auto nextState = nextMode->CreateState(*this, event);
            stateMachine_.SetState(std::move(nextState));
        }
    }
}

void StateController::Update(float deltaTime)
{
    stateMachine_.Update(deltaTime);
}

void StateController::LateUpdate()
{
    stateMachine_.LateUpdate();
}

void StateController::DrawTo(sf::RenderTarget& renderTarget)
{
    stateMachine_.DrawTo(renderTarget);
}

void StateController::Create(const PropertyData& data)
{
    auto mode = modes_.at(ModeType::Uninitialized);
    auto u = std::dynamic_pointer_cast<UninitializedMode>(mode);
    u->Create(data);
}

void StateController::OnInit()
{
    stateMachine_.OnInit();
}

void StateController::Start()
{
    if (!startMode_) {
        LOG_INFO("No startMode found");
        std::abort();
    }
    auto nextState = startMode_->CreateState(*this, nullptr);
    stateMachine_.SetState(std::move(nextState));
}

void StateController::Update(ModeType currentModeType, std::shared_ptr<Shape> shape)
{
    auto currentMode = modes_.at(currentModeType);
    auto updateInfo = currentMode->GetUpdateInfo();
    if (updateInfo.cb_(shape)) {
        auto nextModeType = updateInfo.modeType_;
        auto nextMode = modes_.at(nextModeType);
        auto nextState = nextMode->CreateState(*this, nullptr);
        stateMachine_.SetState(std::move(nextState));
    }
}

void StateController::AddMode(std::shared_ptr<BasicMode> mode, bool startMode)
{
    entityService_.AddFrameType(mode->GetFrameType());

    modes_[mode->GetModeType()] = mode;
    mode->Awake();
    if (startMode) startMode_ = mode;
}

void StateController::SetOnCreateCB(std::function<void(EntityService&, const PropertyData&)> onCreate)
{
    auto mode = modes_.at(ModeType::Uninitialized);
    auto i = std::dynamic_pointer_cast<UninitializedMode>(mode);
    i->SetOnCreateCB(onCreate);
}

}  // namespace Entity

}  // namespace FA
