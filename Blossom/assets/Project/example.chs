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
        span: 5
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
        Texture: Invalid
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
        Texture: Invalid
        color: [0, 0, 0, 1]
    - ID: 1
      NameComponent:
        name: Blue Square
      TransformComponent:
        translation: [0, 2]
        rotation: 0
        scale: [1, 1]
      SpriteComponent:
        Mode: color
        Texture: Invalid
        color: [0, 0.501930714, 1, 1]
    - ID: 0
      NameComponent:
        name: Green Square
      TransformComponent:
        translation: [2, 2]
        rotation: 0
        scale: [1, 1]
      SpriteComponent:
        Mode: color
        Texture: Invalid
        color: [0.0196180604, 0.725868702, 0.0305254217, 1]
  Assets:
    Textures:
      - ID: 0
        File: assets/Project/Smile.png
        Params:
          Format: 1
          MinFilter: 1
          MagFilter: 2
          Wrap: 1
