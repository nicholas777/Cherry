using System;

namespace Cherry
{

    public class Entity
    {
        internal uint __Entity_ID;

        protected Entity() { __Entity_ID = 0; }

        internal Entity(uint id)
        {
            __Entity_ID = id;
        }

        public Entity GetEntityByName(string name)
        {
            Entity result = new Entity(Internal.Scene_GetEntityByName(name, out bool valid));
            if (!valid)
                return null;

            return result;
        }

        public bool HasComponent<T>() where T : Component
        {
            Internal.Entity_HasComponent(__Entity_ID, typeof(T), out bool result);
            return result;
        }

        public void RemoveComponent<T>() where T : Component
        {
            Internal.Entity_RemoveComponent(__Entity_ID, typeof(T));
        }

        public T GetComponent<T>() where T : Component, new()
        {
            if (HasComponent<T>())
            {
                T component = new T();
                component.Entity = __Entity_ID;
                return component;
            }

            return null;
        }
    }
}
