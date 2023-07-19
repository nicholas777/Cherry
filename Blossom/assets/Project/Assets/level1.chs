Scene:
  name: Untitled
  Entities:
    - ID: 2
      NameComponent:
        name: Ground
      TransformComponent:
        translation: [0, 0]
        rotation: 0
        scale: [10, 1]
      SpriteComponent:
        Mode: color
        Texture: -1
        BottomLeftUV: [0, 0]
        TopRightUV: [1, 1]
        color: [0.420849442, 0.107243486, 0, 1]
    - ID: 1
      NameComponent:
        name: Player
      TransformComponent:
        translation: [0, 4]
        rotation: 0
        scale: [0.5, 1]
      SpriteComponent:
        Mode: texture
        Texture: 0
        BottomLeftUV: [0, 0]
        TopRightUV: [1, 1]
        color: [1, 1, 1, 1]
    - ID: 0
      NameComponent:
        name: MainCamera
      TransformComponent:
        translation: [0, 0]
        rotation: 0
        scale: [1, 1]
      ScriptComponent:
        name: Player
      CameraComponent:
        primary: true
        span: 40
        znear: 1
        zfar: -1