/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Game.h"

#include <fstream>
#include <memory>

#include <SFML/Config.hpp>
#include <SFML/System/Err.hpp>

#include "Message/BroadcastMessage/CloseWindowMessage.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/KeyboardPressedMessage.h"
#include "Message/BroadcastMessage/KeyboardReleasedMessage.h"
#include "Sprite/SpriteSheet.h"
#include "System/InputSystem.h"
#include "Utils/Logger.h"
#include "Utils/Path.h"
#include "Version.h"

namespace FA {

const sf::Vector2u Game::screen = {1280, 780};
const sf::Vector2u Game::centerScreen = {Game::screen.x / 2, Game::screen.y / 2};

Game::Game()
{
    LOG_INFO("Start up ", FA_APP_NAME, " version ", FA_APP_VERSION);
    LOG_INFO("SFML version ", SFML_VERSION_MAJOR, ".", SFML_VERSION_MINOR);

    RedirectSfmlLogEntries();
    InitWindow();
#ifdef _DEBUG
    InitDebugSceneGraphics();
#endif
    auto cb = [this](std::shared_ptr<Message> message) { OnMessage(message); };
    messageBus_.AddSubscriber("game",
                              {MessageType::IsKeyPressed, MessageType::KeyboardPressed, MessageType::KeyboardReleased,
                               MessageType::CloseWindow},
                              cb);

    entity_.rectShape_.setPosition(
        sf::Vector2f(static_cast<float>(centerScreen.x), static_cast<float>(centerScreen.y)));
    constexpr int size = 64;
    entity_.rectShape_.setSize({static_cast<float>(size), static_cast<float>(size)});
    InitAnimations();
    entity_.SetAnimation();
}

Game::~Game()
{
    sfmlLogStream_->close();
}

void Game::GameLoop()
{
    LOG_INFO_ENTER_FUNC();
    sf::Clock clock;
    InputSystem inputSystem(messageBus_, window_);

    while (window_.isOpen()) {
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

        inputSystem.Update(deltaTime);
        messageBus_.DispatchMessages();

        entity_.Update(deltaTime);

        window_.clear();
        entity_.Draw(window_);
#ifdef _DEBUG
        window_.draw(sceneText_);
        window_.draw(dotShape_);
#endif
        window_.display();
    }

    LOG_INFO_EXIT_FUNC();
}

void Game::OnMessage(std::shared_ptr<Message> message)
{
    if (message->GetMessageType() == MessageType::KeyboardPressed) {
    }
    else if (message->GetMessageType() == MessageType::KeyboardReleased) {
    }
    else if (message->GetMessageType() == MessageType::IsKeyPressed) {
        auto m = std::dynamic_pointer_cast<IsKeyPressedMessage>(message);
        auto key = m->GetKey();
        if (key == Keyboard::Key::Right) {
            entity_.dir_ = AnimationHandler::FaceDir::Right;
            entity_.SetAnimation();
        }
        else if (key == Keyboard::Key::Left) {
            entity_.dir_ = AnimationHandler::FaceDir::Left;
            entity_.SetAnimation();
        }
        else if (key == Keyboard::Key::Up) {
            entity_.dir_ = AnimationHandler::FaceDir::Up;
            entity_.SetAnimation();
        }
        else if (key == Keyboard::Key::Down) {
            entity_.dir_ = AnimationHandler::FaceDir::Down;
            entity_.SetAnimation();
        }
        else if (key == Keyboard::Key::Num1) {
            entity_.frameType_ = AnimationHandler::FrameType::Idle;
            entity_.SetAnimation();
        }
        else if (key == Keyboard::Key::Num2) {
            entity_.frameType_ = AnimationHandler::FrameType::Move;
            entity_.SetAnimation();
        }
        else if (key == Keyboard::Key::Num3) {
            entity_.frameType_ = AnimationHandler::FrameType::Attack;
            entity_.SetAnimation();
        }
        else if (key == Keyboard::Key::Escape) {
            window_.close();
        }
    }
    else if (message->GetMessageType() == MessageType::CloseWindow) {
        window_.close();
    }
    else {
        // cant happened
    }
}

void Game::RedirectSfmlLogEntries()
{
    sfmlLogStream_ = std::make_unique<std::ofstream>();
    const std::string sfmlLog = "sfml-log.txt";
    sfmlLogStream_->open(GetExePath() + "\\/" + sfmlLog);

    if (sfmlLogStream_->is_open()) {
        LOG_INFO("Redirecting sfml log entries to ", sfmlLog);
        (*sfmlLogStream_) << "SFML version " << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << std::endl;
        sf::err().rdbuf(sfmlLogStream_->rdbuf());
    }
}

void Game::InitWindow()
{
    LOG_INFO("Create main window");
#ifdef _DEBUG
    const std::string title = std::string(FA_APP_NAME) + " v" + FA_APP_VERSION;
    window_.create(sf::VideoMode(screen.x, screen.y), title);
#else
    window_.create(sf::VideoMode::getDesktopMode(), FA_APP_NAME, sf::Style::Fullscreen);
    view_.reset(sf::FloatRect(0.0, 0.0, static_cast<float>(screen.x), static_cast<float>(screen.y)));
    window_.setView(view_);
#endif
    window_.setFramerateLimit(120);
}

#ifdef _DEBUG
void Game::InitDebugSceneGraphics()
{
    if (!font_.loadFromFile("assets/font/cello-sans/hinted-CelloSans-Medium.ttf")) {
        LOG_ERROR("Could not load hinted-CelloSans-Medium");
    }

    sceneText_.setFont(font_);
    sceneText_.setString("GamePlayScene");
    sceneText_.setCharacterSize(24);
    sceneText_.setFillColor(sf::Color::White);
    sf::Vector2f sceneTextPos(0.0f, 0.0f);
    sceneText_.setPosition(sceneTextPos);

    dotShape_.setSize(sf::Vector2f(1.0, 1.0));
    dotShape_.setPosition(sf::Vector2f(static_cast<float>(centerScreen.x), static_cast<float>(centerScreen.y)));
}
#endif

void Game::InitAnimations()
{
    auto textureWalkSide =
        textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/walk/hero-walk-side.png");
    if (textureWalkSide != nullptr) {
        SpriteSheet spriteSheet("heroWalkSide", textureWalkSide, {6, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 6, 0);
        entity_.RegisterAnimationInfo(AnimationHandler::FrameType::Move, AnimationHandler::FaceDir::Left, f.texture_,
                                      f.frames_, f.defaultFrame_, true);
        entity_.RegisterAnimationInfo(AnimationHandler::FrameType::Move, AnimationHandler::FaceDir::Right, f.texture_,
                                      f.frames_, f.defaultFrame_);
    }
    auto textureWalkFront =
        textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/walk/hero-walk-front.png");
    if (textureWalkFront != nullptr) {
        SpriteSheet spriteSheet("heroWalkFront", textureWalkFront, {6, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 6, 0);
        entity_.RegisterAnimationInfo(AnimationHandler::FrameType::Move, AnimationHandler::FaceDir::Down, f.texture_,
                                      f.frames_, f.defaultFrame_);
    }
    auto textureWalkBack =
        textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/walk/hero-back-walk.png");
    if (textureWalkBack != nullptr) {
        SpriteSheet spriteSheet("heroWalkBack", textureWalkBack, {6, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 6, 0);
        entity_.RegisterAnimationInfo(AnimationHandler::FrameType::Move, AnimationHandler::FaceDir::Up, f.texture_,
                                      f.frames_, f.defaultFrame_);
    }

    auto textureAttackSide =
        textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/attack/hero-attack-side.png");
    if (textureAttackSide != nullptr) {
        SpriteSheet spriteSheet("heroAttackSide", textureAttackSide, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        entity_.RegisterAnimationInfo(AnimationHandler::FrameType::Attack, AnimationHandler::FaceDir::Left, f.texture_,
                                      f.frames_, f.defaultFrame_, true);
        entity_.RegisterAnimationInfo(AnimationHandler::FrameType::Attack, AnimationHandler::FaceDir::Right, f.texture_,
                                      f.frames_, f.defaultFrame_);
    }
    auto textureAttackFront =
        textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/attack/hero-attack-front.png");
    if (textureAttackFront != nullptr) {
        SpriteSheet spriteSheet("heroAttackFront", textureAttackFront, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        entity_.RegisterAnimationInfo(AnimationHandler::FrameType::Attack, AnimationHandler::FaceDir::Down, f.texture_,
                                      f.frames_, f.defaultFrame_);
    }
    auto textureAttackBack =
        textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/attack/hero-attack-back.png");
    if (textureAttackBack != nullptr) {
        SpriteSheet spriteSheet("heroAttackBack", textureAttackBack, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        entity_.RegisterAnimationInfo(AnimationHandler::FrameType::Attack, AnimationHandler::FaceDir::Up, f.texture_,
                                      f.frames_, f.defaultFrame_);
    }

    auto textureIdleSide =
        textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/idle/hero-idle-side.png");
    if (textureIdleSide != nullptr) {
        SpriteSheet spriteSheet("heroIdleSide", textureIdleSide, {1, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 1, 0);
        entity_.RegisterAnimationInfo(AnimationHandler::FrameType::Idle, AnimationHandler::FaceDir::Left, f.texture_,
                                      f.frames_, f.defaultFrame_, true);
        entity_.RegisterAnimationInfo(AnimationHandler::FrameType::Idle, AnimationHandler::FaceDir::Right, f.texture_,
                                      f.frames_, f.defaultFrame_);
    }
    auto textureIdleFront =
        textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/idle/hero-idle-front.png");
    if (textureIdleFront != nullptr) {
        SpriteSheet spriteSheet("heroIdleFront", textureIdleFront, {1, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 1, 0);
        entity_.RegisterAnimationInfo(AnimationHandler::FrameType::Idle, AnimationHandler::FaceDir::Down, f.texture_,
                                      f.frames_, f.defaultFrame_);
    }
    auto textureIdleBack =
        textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/idle/hero-idle-back.png");
    if (textureIdleBack != nullptr) {
        SpriteSheet spriteSheet("heroIdleBack", textureIdleBack, {1, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 1, 0);
        entity_.RegisterAnimationInfo(AnimationHandler::FrameType::Idle, AnimationHandler::FaceDir::Up, f.texture_,
                                      f.frames_, f.defaultFrame_);
    }
}

}  // namespace FA
