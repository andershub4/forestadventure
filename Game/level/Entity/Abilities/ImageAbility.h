/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include "BasicAbility.h"

#include "Fwd/SfmlFwd.h"
#include "Resource/Image.h"

namespace FA {

namespace Entity {

class ImageAbility : public BasicAbility
{
public:
    ImageAbility(std::function<std::string()> getKey, std::function<void(const Shared::Image &)>);
    virtual ~ImageAbility();

    virtual void Enter(std::shared_ptr<BasicEvent> event) override;
    virtual void Update(float deltaTime) override;

    void RegisterImage(const std::string &name, const Shared::Image &image);

private:
    std::unordered_map<std::string, Shared::Image> map_;
    Shared::Image currentImage_;
    std::function<std::string()> getKey_;
    std::function<void(const Shared::Image &)> updateFn_;
};

}  // namespace Entity

}  // namespace FA
