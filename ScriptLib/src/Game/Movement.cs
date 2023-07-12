using Cherry;
using System;

public class Movement : Entity
{
    public void OnUpdate(float delta)
    {
        if (Input.IsKeyDown(Key.A))
        {
            Translation = new Vector2(Translation.x - 0.00000001f, Translation.y);
        }
        if (Input.IsKeyDown(Key.D))
        {
            //transform.position.x += 0.01f;
        }
        if (Input.IsKeyDown(Key.W))
        {
            //transform.position.y += 0.01f;
        }
        if (Input.IsKeyDown(Key.S))
        {
            //transform.position.y -= 0.01f;
        }
    }
}
