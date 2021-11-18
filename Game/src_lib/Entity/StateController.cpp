/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "StateController.h"

#include "EntityService.h"
#include "Events/BasicEvent.h"
#include "Events/CreateEvent.h"
#include "Events/InitEvent.h"
#include "Logging.h"
#include "Modes/UninitializedMode.h"

namespace FA {

namespace Entity {

StateController::StateController(EntityService& entityService)
    : entityService_(entityService)
{
    auto u = AddMode<UninitializedMode>();
    u->AddEvent(EventType::Create, ModeType::None, [this](std::shared_ptr<BasicEvent> event) {
        auto c = std::dynamic_pointer_cast<CreateEvent>(event);
        auto data = c->data_;
        onCreate_(entityService_, data);
    });

    currentMode_ = u;
}

StateController::~StateController()
{
    currentMode_->Exit();
}

void StateController::HandleIsKeyPressed(Keyboard::Key key)
{
    auto event = currentMode_->HandleIsKeyPressed(key);
    if (event) {
        HandleEvent(event);
    }
}

void StateController::HandleIsKeyReleased(Keyboard::Key key)
{
    auto event = currentMode_->HandleIsKeyReleased(key);
    if (event) {
        HandleEvent(event);
    }
}

void StateController::HandleKeyPressed(Keyboard::Key key)
{
    auto event = currentMode_->HandleKeyPressed(key);
    if (event) {
        HandleEvent(event);
    }
}

void StateController::HandleEvent(std::shared_ptr<BasicEvent> event)
{
    auto action = currentMode_->GetAction(event->GetEventType());

    if (action.cb_) action.cb_(event);

    auto nextModeType = action.modeType_;
    if (nextModeType != ModeType::None) {
        currentMode_->Exit();
        currentMode_ = modes_.at(nextModeType);
        currentMode_->Enter(event);
    }
}

void StateController::Update(float deltaTime)
{
    currentMode_->Update(deltaTime);

    auto nextModeType = currentMode_->PollUpdate();
    if (nextModeType != ModeType::None) {
        currentMode_->Exit();
        currentMode_ = modes_.at(nextModeType);
        currentMode_->Enter(nullptr);
    }
}

void StateController::DrawTo(sf::RenderTarget& renderTarget)
{
    currentMode_->DrawTo(renderTarget);
}

void StateController::Create(const PropertyData& data)
{
    auto event = std::make_shared<CreateEvent>(data);
    HandleEvent(event);
}

void StateController::Init()
{
    auto event = std::make_shared<InitEvent>();
    HandleEvent(event);
}

void StateController::AddMode(std::shared_ptr<BasicMode> mode, bool startMode)
{
    entityService_.AddFrameType(mode->GetFrameType());

    modes_[mode->GetModeType()] = mode;
    mode->Awake();
    if (startMode) {
        startMode_ = mode->GetModeType();
        auto u = modes_.at(ModeType::Uninitialized);
        u->AddEvent(EventType::Init, startMode_, nullptr);
    }
}

void StateController::SetOnCreateCB(std::function<void(EntityService&, const PropertyData&)> onCreate)
{
    onCreate_ = onCreate;
}

}  // namespace Entity

}  // namespace FA
