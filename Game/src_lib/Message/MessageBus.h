/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "Enum/MessageType.h"

namespace FA {

class Message;

class MessageBus
{
public:
    using MessageCB = std::function<void(std::shared_ptr<Message>)>;

    void AddSubscriber(const std::string& subscriber, MessageType messageType, MessageCB onMessage);
    void AddSubscriber(const std::string& subscriber, const std::vector<MessageType>& messageTypes,
                       MessageCB onMessage);
    void RemoveSubscriber(const std::string& subscriber, MessageType messageType);
    void PushMessage(std::shared_ptr<Message> message);
    void DispatchMessages();

private:
    struct Subscriber
    {
        std::string name_;
        MessageCB onMessage_;
    };

    std::unordered_map<MessageType, std::vector<Subscriber>> subscribersMap_;
    std::queue<std::shared_ptr<Message>> queue_;
};

}  // namespace FA
