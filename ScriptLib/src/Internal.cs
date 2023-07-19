using System;
using System.Runtime.CompilerServices;

namespace Cherry
{
    internal class Internal
    {
        // Input
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static bool InputIsKeyDown(Key key);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static bool InputIsMouseDown(MouseButton button);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static Vector2 InputGetMousePos();

        // Entities

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static uint Scene_GetEntityByName(string name, out bool valid);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static void Entity_HasComponent(uint entity, Type type, out bool result);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static void Entity_GetComponent(uint entity, Type type);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static void Entity_RemoveComponent(uint entity, Type type);

        // NameComponent

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static void NameComponent_GetName(uint id, out string name);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static void NameComponent_SetName(uint id, string name);

        // TransformComponent
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static void TransformComponent_GetTranslation(uint id, out float x, out float y);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static void TransformComponent_SetTranslation(uint id, ref float x, ref float y);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static void TransformComponent_GetRotation(uint id, out float rot);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static void TransformComponent_SetRotation(uint id, ref float rot);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static void TransformComponent_GetScale(uint id, out float x, out float y);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static void TransformComponent_SetScale(uint id, ref float x, ref float y);
    }
}
