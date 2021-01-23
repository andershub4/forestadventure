/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MessageBus.h"

#include "Message.h"

namespace FA {

void MessageBus::AddSubscriber(const std::string& subscriber, MessageType messageType, MessageCB onMessage)
{
    auto& subscribers = subscribersMap_[messageType];
    subscribers.push_back({subscriber, onMessage});
}

void MessageBus::AddSubscriber(const std::string& subscriber, const std::vector<MessageType>& messageTypes,
                               MessageCB onMessage)
{
    for (auto messageType : messageTypes) {
        AddSubscriber(subscriber, messageType, onMessage);
    }
}

void MessageBus::RemoveSubscriber(const std::string& subscriber, MessageType messageType)
{
    auto& subscribers = subscribersMap_[messageType];
    auto removeMe = std::remove_if(subscribers.begin(), subscribers.end(),
                                   [subscriber](Subscriber& s) { return s.name_ == subscriber; });

    subscribers.erase(removeMe, subscribers.end());
}

void MessageBus::PushMessage(std::shared_ptr<Message> message)
{
    queue_.push(message);
}

void MessageBus::DispatchMessages()
{
    while (!queue_.empty()) {
        auto msg = queue_.front();
        auto type = msg->GetMessageType();
        const auto& subscribers = subscribersMap_[type];
        for (const auto& subscriber : subscribers) {
            subscriber.onMessage_(msg);
        }

        queue_.pop();
    }
}

}  // namespace FA