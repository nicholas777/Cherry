using Cherry;
using System;

public class Movement : Entity
{
    public void OnUpdate(float delta)
    {
        Vector2 velocity = new Vector2(0, 0);

        float speed = 0.01f;

        if (Input.IsKeyDown(Key.A))
        {
            velocity.x -= speed;
        }
        if (Input.IsKeyDown(Key.D))
        {
            velocity.x += speed;
        }
        if (Input.IsKeyDown(Key.W))
        {
            velocity.y += speed;
        }
        if (Input.IsKeyDown(Key.S))
        {
            velocity.y -= speed;
        }

        Vector2 translation = Translation;
        translation += velocity * delta;
        Translation = translation;
    }
}
