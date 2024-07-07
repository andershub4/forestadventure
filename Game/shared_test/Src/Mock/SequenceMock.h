/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "SequenceIf.h"

namespace FA {

namespace Shared {

template <class T>
class SequenceMock : public SequenceIf<T>
{
public:
    MOCK_METHOD(void, Update, (float), (override));
    MOCK_METHOD(T, GetCurrent, (), (const override));
    MOCK_METHOD(void, Start, (), (override));
    MOCK_METHOD(void, Stop, (), (override));
    MOCK_METHOD(void, Restart, (), (override));
    MOCK_METHOD(bool, IsEmpty, (), (const override));
    MOCK_METHOD(bool, IsCompleted, (), (const override));
    MOCK_METHOD(void, Add, (const T&), (override));
};

}  // namespace Shared

}  // namespace FA
