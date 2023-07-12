#include "epch.h"
#include "SceneSerializer.h"
#include "Entity.h"
#include "Component.h"
#include "Math/Vector.h"
#include "AssetManager.h"
#include "Debug/Profiler.h"

#include "entt.hpp"

namespace Cherry
{
    static void SerializeVec2(Vector2f vec, const char* name, YAML::Emitter& out)
    {
        CH_PROFILE_FUNC();

        out << YAML::Key << name;
        out << YAML::Flow;
        out << YAML::Value << YAML::BeginSeq;
        out << vec.x << vec.y;
        out << YAML::EndSeq;
    }

    static void SerializeVec4(Vector4f vec, const char* name, YAML::Emitter& out)
    {
        CH_PROFILE_FUNC();

        out << YAML::Key << name;
        out << YAML::Flow;
        out << YAML::Value << YAML::BeginSeq;
        out << vec.x << vec.y << vec.z << vec.w;
        out << YAML::EndSeq;
    }

    static void SerializeEntity(Entity entity, YAML::Emitter& out)
    {
        CH_PROFILE_FUNC();

        out << YAML::BeginMap;
        out << YAML::Key << "ID";
        out << YAML::Value << (uint32_t)entity;

        if (entity.HasComponent<NameComponent>())
        {
            NameComponent& comp = entity.GetComponent<NameComponent>();

            out << YAML::Key << "NameComponent";
            out << YAML::Value << YAML::BeginMap;

            out << YAML::Key << "name";
            out << YAML::Value << comp.Name.c_str();

            out << YAML::EndMap;
        }

        if (entity.HasComponent<TransformComponent>())
        {
            TransformComponent& comp = entity.GetComponent<TransformComponent>();

            out << YAML::Key << "TransformComponent";
            out << YAML::Value << YAML::BeginMap;

            SerializeVec2(comp.Translation, "translation", out);
            out << YAML::Key << "rotation" << YAML::Value << comp.Rotation;
            SerializeVec2(comp.Scale, "scale", out);

            out << YAML::EndMap;
        }

        if (entity.HasComponent<SpriteComponent>())
        {
            SpriteComponent& comp = entity.GetComponent<SpriteComponent>();

            out << YAML::Key << "SpriteComponent";
            out << YAML::Value << YAML::BeginMap;

            out << YAML::Key << "Mode";
            out << YAML::Value << (comp.UseTexture == true ? "texture" : "color");

            int id = -1;

            if (comp.UseTexture)
            {
                for (std::pair<const uint32_t, TextureAsset>& asset : AssetManager::GetTextures())
                {
                    if (asset.second.ptr.Get() == comp.SpriteTexture->texture.Get())
                    {
                        id = asset.first;
                        break;
                    }
                }

            }

            out << YAML::Key << "Texture" << YAML::Value << id;

            SerializeVec2(comp.SpriteTexture->textureCoords[0], "BottomLeftUV", out);
            SerializeVec2(comp.SpriteTexture->textureCoords[2], "TopRightUV", out);
            
            SerializeVec4(comp.Color, "color", out);

            out << YAML::EndMap;
        }

        if (entity.HasComponent<CameraComponent>())
        {
            CameraComponent& comp = entity.GetComponent<CameraComponent>();

            out << YAML::Key << "CameraComponent";
            out << YAML::Value << YAML::BeginMap;

            out << YAML::Key << "primary";
            out << YAML::Value << comp.IsPrimary;

            out << YAML::Key << "span";
            out << YAML::Value << comp.camera.GetSpan();

            out << YAML::Key << "znear";
            out << YAML::Value << comp.camera.GetNear();

            out << YAML::Key << "zfar";
            out << YAML::Value << comp.camera.GetFar();

            out << YAML::EndMap;
        }

        out << YAML::EndMap;
    }
    
    void SceneSerializer::Serialize(Scene* scene, const std::string& filepath)
    {
        CH_PROFILE_FUNC();

        YAML::Emitter out;
        out << YAML::BeginMap << YAML::Key << "Scene";
        out << YAML::Value << YAML::BeginMap;

        out << YAML::Key << "name";
        out << YAML::Value << "Untitled";

        out << YAML::Key << "Entities";
        out << YAML::Value << YAML::BeginSeq;

        scene->m_Registry.each([&](auto entity)
        {
            SerializeEntity(Entity(entity, scene), out);
        });
        
        out << YAML::EndSeq;
        out << YAML::EndMap << YAML::EndMap;
        
        std::ofstream stream(filepath);
        stream << out.c_str();
    }

    Scene* SceneSerializer::Deserialize(const std::string& filepath)
    {
        CH_PROFILE_FUNC();

        YAML::Node scene = YAML::LoadFile(filepath);
        Scene* s = new Scene;

        if (!scene["Scene"])
        {
            CH_ASSERT(false, "Invadlid scene file!");
            return nullptr;
        }

        // TODO: Scene names
        if (!scene["Scene"]["Entities"])
        {
            CH_ASSERT(false, "Invalid scene file!");
            return nullptr;
        }

        if (!scene["Scene"]["Entities"].IsSequence())
        {
            CH_ASSERT(false, "Invalid scene file!");
            return nullptr;
        }

        for (int i = 0; i < scene["Scene"]["Entities"].size(); i++)
        {
            YAML::Node entity = scene["Scene"]["Entities"][i];
            Entity e;

            if (entity["NameComponent"])
            {
                e = s->CreateEntity(entity["NameComponent"]["name"].as<std::string>());
            }
            else
            {
                e = s->CreateEntity("Untitled Entity");
            }

            if (entity["TransformComponent"])
            {
                TransformComponent& comp = e.AddComponent<TransformComponent>();
                
                comp.Translation.x = entity["TransformComponent"]["translation"][0].as<float>();
                comp.Translation.y = entity["TransformComponent"]["translation"][1].as<float>();
                
                comp.Rotation = entity["TransformComponent"]["rotation"].as<float>();

                comp.Scale.x = entity["TransformComponent"]["scale"][0].as<float>();
                comp.Scale.y = entity["TransformComponent"]["scale"][1].as<float>();
            }

            if (entity["SpriteComponent"])
            {
                SpriteComponent& comp = e.AddComponent<SpriteComponent>();

                if (entity["SpriteComponent"]["Mode"].as<std::string>() == "color")
                {
                    comp.UseTexture = false;

                    comp.SpriteTexture = new SubTexture(Shared<Texture>(nullptr));
                }
                else
                {
                    comp.UseTexture = true;
                    Shared<Texture> texture;

                    if (entity["SpriteComponent"]["Texture"].as<int>() == -1)
                        texture = Shared<Texture>(nullptr);
                    else
                        texture = AssetManager::GetTexture(entity["SpriteComponent"]["Texture"].as<int>()).ptr;
                    
                    comp.SpriteTexture = new SubTexture(
                        texture,
                        Vector2f(entity["SpriteComponent"]["BottomLeftUV"][0].as<float>(),
                                 entity["SpriteComponent"]["BottomLeftUV"][1].as<float>()),
                        Vector2f(entity["SpriteComponent"]["TopRightUV"][0].as<float>(),
                                 entity["SpriteComponent"]["TopRightUV"][1].as<float>())
                    );
                }




                comp.Color.x = entity["SpriteComponent"]["color"][0].as<float>();
                comp.Color.y = entity["SpriteComponent"]["color"][1].as<float>();
                comp.Color.z = entity["SpriteComponent"]["color"][2].as<float>();
                comp.Color.w = entity["SpriteComponent"]["color"][3].as<float>();
            }

            if (entity["CameraComponent"])
            {
                CameraComponent& comp = e.AddComponent<CameraComponent>();

                comp.IsPrimary = entity["CameraComponent"]["primary"].as<bool>();

                comp.camera.SetNear(entity["CameraComponent"]["zfar"].as<float>());
                comp.camera.SetFar(entity["CameraComponent"]["znear"].as<float>());
                comp.camera.SetSpan(entity["CameraComponent"]["span"].as<float>());
                
                comp.camera.RecelcProjection();
            }
        }

        return s;
    }
}
