#pragma once

#include "core/pointer.h"
#include "core/timestep.h"
#include "graphics/cameras/sceneCamera.h"
#include "math/matrix.h"
#include "nativeScript.h"
#include "renderer/texture.h"
#include "scripting/scriptEngine.h"
#include <unordered_map>

namespace Cherry {
    struct NameComponent {
        std::string Name;

        NameComponent() = default;
        NameComponent(const NameComponent&) = default;

        NameComponent(const std::string& name): Name(name) {}
    };

    struct TransformComponent {
        Vector2f Translation = Vector2f(0.0f);
        float Rotation = 0.0f;
        Vector2f Scale = Vector2f(1.0f);

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;

        TransformComponent(const Vector2f& pos, float rot, const Vector2f scale)
            : Translation(pos), Rotation(rot), Scale(scale) {}

        Matrix4x4f GetMatrix() {
            Matrix4x4f mat = Matrix4x4f::Identity();

            Translate(&mat, Translation.x, Translation.y);
            Rotate(&mat, Rotation);
            Cherry::Scale(&mat, Scale.x, Scale.y);

            return mat;
        }
    };

    struct SpriteComponent {
        Vector4f Color = { 1, 1, 1, 1 };

        Shared<SubTexture> SpriteTexture;

        bool UseTexture = false;

        SpriteComponent() = default;
        SpriteComponent(const SpriteComponent&) = default;

        SpriteComponent(const Vector4f& color)
            : Color(color), SpriteTexture(new SubTexture(nullptr)), UseTexture(false) {}

        SpriteComponent(const Shared<Texture>& texture,
                        const Vector2f& bottomLeft = Vector2f(0.0f, 0.0f),
                        const Vector2f& topRight = Vector2f(1.0f, 1.0f))
            : Color({ 1, 1, 1, 1 }), SpriteTexture(new SubTexture(texture, bottomLeft, topRight)),
              UseTexture(true) {}
    };

    struct CameraComponent {
        SceneCamera camera;
        bool IsPrimary = true;

        CameraComponent() = default;
        CameraComponent(const CameraComponent&) = default;

        CameraComponent(const SceneCamera& cam, bool primary): camera(cam), IsPrimary(primary) {}
    };

    struct FieldData {
        ScriptFieldType type;

        union {
            double number;
            const char* string;
            bool boolean;
        };
    };

    struct ScriptComponent {
        std::string Name;
        std::unordered_map<std::string, FieldData> Fields;

        ScriptComponent() = default;
        ScriptComponent(const std::string& name): Name(name) {};
    };

    struct NativeScriptComponent {
        NativeScript* script = nullptr;

        std::function<void()> CreateInstanceFn;
        std::function<void()> DeleteInstanceFn;

        std::function<void(NativeScript*)> OnCreateFn;
        std::function<void(NativeScript*)> OnDestroyFn;
        std::function<void(NativeScript*, Timestep)> OnUpdateFn;

        NativeScriptComponent() = default;
        NativeScriptComponent(const NativeScriptComponent&) = default;

        template<typename T>
        void Bind() {
            CreateInstanceFn = [&]() { script = new T; };
            DeleteInstanceFn = [&]() { delete script; };

            OnCreateFn = [](NativeScript* executor) { ((T*)executor)->OnCreate(); };
            OnDestroyFn = [](NativeScript* executor) { ((T*)executor)->OnDestroy(); };
            OnUpdateFn = [](NativeScript* executor, Timestep delta) {
                ((T*)executor)->OnUpdate(delta);
            };
        }
    };

    template<typename... T>
    struct ComponentList {};

    using AllComponents = ComponentList<NameComponent, TransformComponent, SpriteComponent,
                                        CameraComponent, NativeScriptComponent, ScriptComponent>;

    using OptionalComponents = ComponentList<TransformComponent, SpriteComponent, CameraComponent,
                                             NativeScriptComponent, ScriptComponent>;
}
