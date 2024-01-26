#pragma once

#include <scene/assetManager.h>
#include <scene/component.h>

namespace Cherry {

    class ReversableAction
    {
    public:
        virtual void Reverse() = 0;
        virtual ReversableAction* ToReversed() = 0;

        bool IsEntityCreateAction = false;
    };

    class EntityCreateAction : public ReversableAction
    {
    public:
        virtual void Reverse() override {
            Entity::Delete(entity);
            IsEntityCreateAction = true;
        }

        virtual ReversableAction* ToReversed() override { return nullptr; }

        Entity entity;
    };

    class EntityDeleteAction : public ReversableAction
    {
    public:
        virtual void Reverse() override {
            Entity e = entity.m_Scene->CreateEntity(name == nullptr ? "Entity" : name->Name);

            if (transform)
                e.AddComponent<TransformComponent>(transform->Translation, transform->Rotation,
                                                   transform->Scale);

            if (sprite)
                e.AddComponent<SpriteComponent>(sprite->Color).SpriteTexture =
                    sprite->SpriteTexture;

            if (camera)
                e.AddComponent<CameraComponent>(camera->camera, camera->IsPrimary);

            delete name;
            delete transform;
            delete sprite;
            delete camera;
        }

        virtual ReversableAction* ToReversed() override {
            EntityCreateAction* action = new EntityCreateAction;
            action->entity = entity;
            return action;
        }

        Entity entity;
        NameComponent* name = nullptr;
        TransformComponent* transform = nullptr;
        SpriteComponent* sprite = nullptr;
        CameraComponent* camera = nullptr;
    };

    class NameComponentEditAction : public ReversableAction
    {
    public:
        virtual void Reverse() override { entity.GetComponent<NameComponent>().Name = oldName; }

        virtual ReversableAction* ToReversed() override {
            NameComponentEditAction* action = new NameComponentEditAction;
            action->entity = entity;
            action->oldName = newName;
            action->newName = oldName;

            return action;
        }

        Entity entity;
        std::string oldName, newName;
    };

    class TransformComponentEditAction : public ReversableAction
    {
    public:
        virtual void Reverse() override {
            TransformComponent& comp = entity.GetComponent<TransformComponent>();
            comp.Translation = oldPos;
            comp.Rotation = oldRot;
            comp.Scale = oldSize;
        }

        virtual ReversableAction* ToReversed() override {
            TransformComponentEditAction* action = new TransformComponentEditAction;
            action->entity = entity;

            action->oldPos = newPos;
            action->newPos = oldPos;

            action->oldSize = newSize;
            action->newSize = oldSize;

            action->oldRot = newRot;
            action->newRot = oldRot;

            return action;
        }

        Entity entity;
        Vector2f oldPos, newPos, oldSize, newSize;
        float oldRot, newRot;
    };

    class SpriteComponentEditAction : public ReversableAction
    {
    public:
        virtual void Reverse() override {
            SpriteComponent& comp = entity.GetComponent<SpriteComponent>();
            comp.SpriteTexture = new SubTexture(oldTexture);
            comp.Color = oldColor;
            comp.UseTexture = oldUseTexture;
        }

        virtual ReversableAction* ToReversed() override {
            SpriteComponentEditAction* action = new SpriteComponentEditAction;
            action->entity = entity;

            action->oldColor = newColor;
            action->newColor = oldColor;

            action->oldTexture = newTexture;
            action->newTexture = oldTexture;

            action->oldUseTexture = newUseTexture;
            action->newUseTexture = oldUseTexture;

            return action;
        }

        Entity entity;
        SubTexture oldTexture, newTexture;
        Vector4f oldColor, newColor;
        bool oldUseTexture, newUseTexture;
    };

    class CameraComponentEditAction : public ReversableAction
    {
    public:
        virtual void Reverse() override {
            CameraComponent& comp = entity.GetComponent<CameraComponent>();

            comp.camera = oldCamera;
            comp.IsPrimary = oldPrimary;
        }

        virtual ReversableAction* ToReversed() override {
            CameraComponentEditAction* action = new CameraComponentEditAction;
            action->entity = entity;

            action->oldCamera = newCamera;
            action->newCamera = oldCamera;

            action->oldPrimary = newPrimary;
            action->newPrimary = oldPrimary;

            return action;
        }

        Entity entity;
        SceneCamera oldCamera, newCamera;
        bool oldPrimary, newPrimary;
    };

    class TextureAssetEditAction : public ReversableAction
    {
    public:
        virtual void Reverse() override {
            TextureAsset& asset = AssetManager::GetTexture(ID);

            asset.params.wrap = oldWrap;
            asset.params.minFilter = oldMinFilter;
            asset.params.magFilter = oldMagFilter;

            if (oldFormat != asset.params.format) {
                asset.params.format = oldFormat;
                asset.ptr = Texture::Create(asset.filepath, asset.params);
                return;
            }

            asset.ptr->ResetParams(asset.params);
        }

        virtual ReversableAction* ToReversed() override {
            TextureAssetEditAction* action = new TextureAssetEditAction;
            action->ID = ID;

            action->oldWrap = newWrap;
            action->newWrap = oldWrap;

            action->oldMinFilter = newMinFilter;
            action->newMinFilter = oldMinFilter;

            action->oldMagFilter = newMagFilter;
            action->newMagFilter = oldMagFilter;

            action->oldFormat = newFormat;
            action->newFormat = oldFormat;

            return action;
        }

        uint32_t ID;
        TextureWrap oldWrap, newWrap;
        TextureFilter oldMinFilter, newMinFilter;
        TextureFilter oldMagFilter, newMagFilter;
        TextureFormat oldFormat, newFormat;
    };

    // TODO: Adding/removing components undo/redo
} // namespace Cherry
