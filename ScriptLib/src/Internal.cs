using System;
using System.Runtime.CompilerServices;

namespace Cherry
{
    public static class Internal
    {
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static bool InputIsKeyDown(Key key);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static bool InputIsMouseDown(MouseButton button);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static Vector2 InputGetMousePos();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static void GetEntityTranslation(uint id, out float x, out float y);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static void SetEntityTranslation(uint id, ref Vector2 vec);
        
    }
}
