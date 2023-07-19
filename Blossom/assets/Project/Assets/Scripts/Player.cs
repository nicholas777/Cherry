using Cherry;
using System;

public class Player : Entity
{
    public TransformComponent transform;
    public void OnCreate()
    {
        transform = GetComponent<TransformComponent>();
    }

    public void OnUpdate(float delta)
    {
        Vector2 velocity = new Vector2(0, 0);

        float speed = 0.025f;

        if (Input.IsKeyDown(Key.A))
        {
            velocity.x += speed;
        }
        if (Input.IsKeyDown(Key.D))
        {
            velocity.x -= speed;
        }
        if (Input.IsKeyDown(Key.W))
        {
            velocity.y -= speed;
        }
        if (Input.IsKeyDown(Key.S))
        {
            velocity.y += speed;
        }

        transform.Translation += velocity * delta;
    }
}
