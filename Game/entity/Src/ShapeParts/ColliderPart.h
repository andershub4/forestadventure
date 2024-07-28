/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "Animation/ColliderAnimation.h"
#include "BasicColliderPart.h"
#include "Logging.h"

namespace FA {

namespace Entity {

template <class KeyT>
class ColliderPartWith : public BasicColliderPart
{
public:
    /* Constructor for multiple colliders */
    ColliderPartWith(const KeyT *const key)
    {
        selectFn_ = [key](const std::unordered_map<KeyT, std::shared_ptr<Shared::ColliderAnimation>> &animations) {
            bool found = animations.find(*key) != animations.end();
            Shared::ColliderAnimation *result = nullptr;

            if (found) {
                result = animations.at(*key).get();
            }
            else {
                LOG_ERROR("%s can not be found", DUMP(key));
            }

            return result;
        };
    }

    /* Constructor for singel collider */
    ColliderPartWith(std::shared_ptr<Shared::ColliderAnimation> animation)
    {
        KeyT defaultKey{};
        selectFn_ =
            [defaultKey](const std::unordered_map<KeyT, std::shared_ptr<Shared::ColliderAnimation>> &animations) {
                bool found = animations.find(defaultKey) != animations.end();
                Shared::ColliderAnimation *result = nullptr;

                if (found) {
                    result = animations.at(defaultKey).get();
                }

                return result;
            };

        RegisterCollider(defaultKey, animation);
    }

    virtual ~ColliderPartWith() = default;

    virtual void Enter() override
    {
        currentAnimation_ = selectFn_(map_);
        currentAnimation_->Restart();
    }

    virtual void Update(float deltaTime) override
    {
        currentAnimation_->Update(deltaTime);
        updateCB_(*currentAnimation_);
    }

    virtual void DrawTo(Graphic::RenderTargetIf &renderTarget) const { currentAnimation_->DrawTo(renderTarget); }

    virtual void SetPosition(const sf::Vector2f &position) override { currentAnimation_->SetPosition(position); }

    virtual void SetRotation(float angle) override { currentAnimation_->SetRotation(angle); }

    bool Intersects(const BasicColliderPart &otherPart)
    {
        auto other = static_cast<const ColliderPartWith<KeyT> &>(otherPart);
        return currentAnimation_->Intersects(*other.currentAnimation_);
    }

    void RegisterCollider(const KeyT &key, std::shared_ptr<Shared::ColliderAnimation> animation)
    {
        auto res = map_.emplace(key, animation);
        if (!res.second) {
            LOG_WARN("%s is already inserted", DUMP(key));
        }
    }

    void RegisterUpdateCB(std::function<void(const Shared::ColliderAnimation &)> updateCB) { updateCB_ = updateCB; }

private:
    using SelectFn = std::function<Shared::ColliderAnimation *(
        const std::unordered_map<KeyT, std::shared_ptr<Shared::ColliderAnimation>> &)>;

    std::unordered_map<KeyT, std::shared_ptr<Shared::ColliderAnimation>> map_;
    SelectFn selectFn_;
    Shared::ColliderAnimation *currentAnimation_{nullptr};
    std::function<void(const Shared::ColliderAnimation &)> updateCB_{[](const Shared::ColliderAnimation &) {}};
};

using ColliderPart = ColliderPartWith<int>;

}  // namespace Entity

}  // namespace FA
