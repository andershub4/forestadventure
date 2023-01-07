/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace FA {

namespace Shared {

class Message;
enum class MessageType;

class MessageBus
{
public:
    using MessageCB = std::function<void(std::shared_ptr<Message>)>;

    void AddSubscriber(const std::string& subscriber, MessageType messageType, MessageCB onMessage);
    void AddSubscriber(const std::string& subscriber, const std::vector<MessageType>& messageTypes,
                       MessageCB onMessage);
    void RemoveSubscriber(const std::string& subscriber, MessageType messageType);
    void RemoveSubscriber(const std::string& subscriber, const std::vector<MessageType>& messageTypes);
    void SendMessage(std::shared_ptr<Message> message);

private:
    struct Subscriber
    {
        std::string name_;
        MessageCB onMessage_ = nullptr;
    };

    std::unordered_map<MessageType, std::vector<Subscriber>> subscribersMap_;
};

}  // namespace Shared

}  // namespace FA
