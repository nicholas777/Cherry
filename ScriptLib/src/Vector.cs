using System;

namespace Cherry
{
    public class Vector2
    {
        public float x, y;

        public static readonly Vector2 Zero = new Vector2(0f, 0f);

        public Vector2()
        {
            x = 0;
            y = 0;
        }

        public Vector2(float x, float y)
        {
            this.x = x;
            this.y = y;
        }

        public float Length()
        {
            return (float)Math.Sqrt(x * x + y * y);
        }

        public static Vector2 operator +(Vector2 value, float scalar)
        {
            return new Vector2(scalar + value.x, scalar + value.y);
        }

        public static Vector2 operator +(Vector2 value, Vector2 scalar)
        {
            return new Vector2(scalar.x + value.x, scalar.y + value.y);
        }

        public static Vector2 operator *(Vector2 value, float scalar)
        {
            return new Vector2(scalar * value.x, scalar * value.y);
        }

        public static Vector2 operator *(Vector2 value, Vector2 scalar)
        {
            return new Vector2(scalar.x * value.x, scalar.y * value.y);
        }

        public static Vector2 operator -(Vector2 value)
        {
            return new Vector2(-value.x, -value.y);
        }

        public static Vector2 operator -(Vector2 value, float scalar)
        {
            return new Vector2(scalar + value.x, scalar + value.y);
        }

        public static Vector2 operator -(Vector2 value, Vector2 scalar)
        {
            return new Vector2(scalar.x - value.x, scalar.y - value.y);
        }
    }

    public class Vector3
    {
        public float x, y, z;

        public static Vector3 Zero = new Vector3(0f, 0f, 0f);

        public Vector3()
        {
            x = 0;
            y = 0;
            z = 0;
        }

        public Vector3(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public float Length()
        {
            return (float)Math.Sqrt(x * x + y * y + z * z);
        }
    }

    public class Vector4
    {
        public float x, y, z, w;

        public static Vector4 Zero = new Vector4(0f, 0f, 0f, 0f);

        public Vector4()
        {
            x = 0;
            y = 0;
            z = 0;
            w = 0;
        }

        public Vector4(float x, float y, float z, float w)
        {
            this.x = x;
            this.y = y;
            this.z = z;
            this.w = w;
        }

        public float Length()
        {
            return (float)Math.Sqrt(x * x + y * y + z * z + w * w);
        }

    }
}
