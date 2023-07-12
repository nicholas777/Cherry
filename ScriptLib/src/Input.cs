using Cherry;

public class Input
{
    public static bool IsKeyDown(Key key)
    {
        return Internal.InputIsKeyDown(key);
    }

    public static bool IsMouseDown(MouseButton button)
    {
        return Internal.InputIsMouseDown(button);
    }

    public static Vector2 GetMousePos()
    {
        return Internal.InputGetMousePos();
    }
}
