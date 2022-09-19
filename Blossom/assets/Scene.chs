Scene
---
name: Untitled
Entities:
  - ID: 1
    NameComponent:
      name: Smiley
    TransformComponent:
      translation: [0, 0]
      rotation: 0
      scale: [1, 1]
    SpriteComponent:
      Mode: color
      Texture: Invalid
      color: [1, 1, 1, 1]
  - ID: 0
    NameComponent:
      name: Main camera
    TransformComponent:
      translation: [0, 0]
      rotation: 0
      scale: [1, 1]
    CameraComponent:
      primary: true
      span: 12
      znear: 1
      zfar: -1