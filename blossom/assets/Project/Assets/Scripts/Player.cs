using Cherry;
using System;

public class Player : Entity
{
    public TransformComponent transform, playerTransform;
    public Entity player;

    public float startY;
    public bool jumping;
    public float jumpCoefficient;
    public float startCoefficient = 0.09f;
    public float gravity = 0.0003f;

    public string str;

    int i;
    uint ui;
    float f;
    double d;
    public bool b = true;
    short s;
    ushort us;
    long l;
    ulong ul;
    byte by;

    Vector2 vec2;
    Vector3 vec3;
    Vector4 vec4;

    public void OnCreate()
    {
        transform = GetComponent<TransformComponent>();
        player = GetEntityByName("Player");
        playerTransform = player.GetComponent<TransformComponent>();

        transform.Translation = -playerTransform.Translation;
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
        if (Input.IsKeyDown(Key.Space) && !jumping)
        {
            startY = transform.Translation.y;
            jumping = true;
            jumpCoefficient = startCoefficient;
        }

        if (jumping)
        {
            velocity.y -= jumpCoefficient;
            jumpCoefficient -= gravity * delta;
        }

        transform.Translation += velocity * delta;
        playerTransform.Translation += -velocity * (delta / 2);

        if (transform.Translation.y >= startY && jumping)
        {
            jumping = false;
            transform.Translation = new Vector2(transform.Translation.x, startY);
            playerTransform.Translation = new Vector2(playerTransform.Translation.x, -startY);
        }
    }
}
