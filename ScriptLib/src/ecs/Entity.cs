using System;

namespace Cherry
{

    public class Entity
    {
        private uint __Entity_ID;

        protected Entity() { __Entity_ID = 0; }

        internal Entity(uint id)
        {
            __Entity_ID = id;
            Console.WriteLine(__Entity_ID);
        }

        protected Vector2 Translation
        {
            get
            {
                Internal.GetEntityTranslation(__Entity_ID, out float x, out float y);
                return new Vector2(x, y);
            }
            set
            {
                Internal.SetEntityTranslation(__Entity_ID, ref value);
            }
        }
    }
}
