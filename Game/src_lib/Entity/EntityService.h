/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <vector>

#include "AttributeStore.h"
#include "Enum/FaceDirection.h"
#include "Enum/FrameType.h"
#include "Logging.h"
#include "ModeType.h"
#include "Resource/AnimationDb.h"
#include "Resource/ImageDb.h"

namespace FA {

class CameraManager;
class Animation;
class SheetManager;

namespace Entity {

class CameraAttribute;
class Shape;

class EntityService
{
public:
    EntityService(CameraManager &cameraManager, SheetManager &sheetManager);
    ~EntityService();

    template <class T>
    std::shared_ptr<T> AddAttribute()
    {
        return attributeStore_.AddAttribute<T>(this);
    }

    template <class T>
    std::shared_ptr<T> GetAttribute()
    {
        if (attributeStore_.HasAttribute<T>()) {
            return attributeStore_.GetAttribute<T>();
        }
        else {
            LOG_ERROR(typeid(T).name(), " is not in attributeStore");
            return AddAttribute<T>();
        }
    }

    template <>
    std::shared_ptr<CameraAttribute> AddAttribute<CameraAttribute>();

    void LoadAnimation(EntityType entityType, const AnimationData &data);
    Animation GetAnimation(EntityType entityType, FrameType frameType, FaceDirection faceDir) const;
    
    void LoadImage(EntityType entityType, const ImageData &data);
    Image GetImage(EntityType entityType, FrameType frameType, FaceDirection faceDir) const;
    
    std::vector<ModeType> GetModeTypes() const { return modeTypes_; }
    std::shared_ptr<Shape> GetShape() const { return shape_; }
    void AddModeType(ModeType modeType);

private:
    AttributeStore attributeStore_;
    std::vector<ModeType> modeTypes_;
    CameraManager &cameraManager_;
    AnimationDb animationDb_;
    ImageDb imageDb_;
    std::shared_ptr<Shape> shape_ = nullptr;
};

}  // namespace Entity

}  // namespace FA
