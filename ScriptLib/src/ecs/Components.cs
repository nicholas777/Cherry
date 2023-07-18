using System;

namespace Cherry
{
    public abstract class Component
    {
        internal uint Entity;
    }

    public class NameComponent : Component
    {
        public string Name
        {
            get
            {
                Internal.NameComponent_GetName(Entity, out string name);
                return name;
            }
            set
            {
                Console.WriteLine(value);
                Internal.NameComponent_SetName(Entity, value);
            }
        }
    }

    public class TransformComponent : Component
    {
        public Vector2 Translation
        {
            get
            {
                Internal.TransformComponent_GetTranslation(Entity, out float x, out float y);
                return new Vector2(x, y);
            }
            set
            {
                Internal.TransformComponent_SetTranslation(Entity, ref value.x, ref value.y);
            }
        }

        public float Rotation
        {
            get
            {
                Internal.TransformComponent_GetRotation(Entity, out float rot);
                return rot;
            }
            set
            {
                Internal.TransformComponent_SetRotation(Entity, ref value);
            }
        }

        public Vector2 Scale
        {
            get
            {
                Internal.TransformComponent_GetScale(Entity, out float x, out float y);
                return new Vector2(x, y);
            }
            set
            {
                Internal.TransformComponent_SetScale(Entity, ref value.x, ref value.y);
            }
        }
    }

    public class SpriteComponent : Component
    {

    }

    public class CameraComponent : Component
    {

    }
}
