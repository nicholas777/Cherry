Scene:
  name: Untitled
  Entities:
    - ID: 4
      NameComponent:
        name: Camera
      TransformComponent:
        translation: [-3, 0]
        rotation: 0
        scale: [1, 1]
      CameraComponent:
        primary: true
        span: 1
        znear: -1
        zfar: 1
    - ID: 3
      NameComponent:
        name: White Square
      TransformComponent:
        translation: [0, 0]
        rotation: 0
        scale: [1, 1]
      SpriteComponent:
        Mode: color
        Texture: -1
        BottomLeftUV: [0, 0]
        TopRightUV: [1, 1]
        color: [1, 1, 1, 1]
    - ID: 2
      NameComponent:
        name: Black square
      TransformComponent:
        translation: [2, 0]
        rotation: 0
        scale: [1, 1]
      SpriteComponent:
        Mode: color
        Texture: -1
        BottomLeftUV: [0, 0]
        TopRightUV: [1, 1]
        color: [0, 0, 0, 1]
    - ID: 1
      NameComponent:
        name: Smiley
      TransformComponent:
        translation: [-2, 2]
        rotation: 0
        scale: [1, 1]
      SpriteComponent:
        Mode: texture
        Texture: 0
        BottomLeftUV: [0, 0]
        TopRightUV: [1, 1]
        color: [1, 1, 1, 1]
    - ID: 0
      NameComponent:
        name: Green Square
      TransformComponent:
        translation: [2, 2]
        rotation: 0
        scale: [1, 1]
      SpriteComponent:
        Mode: color
        Texture: -1
        BottomLeftUV: [0, 0]
        TopRightUV: [1, 1]
        color: [0.0196180604, 0.725868702, 0.0305254217, 1]