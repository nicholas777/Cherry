#pragma once

#include "core/log.h"
#include "core/pointer.h"

#include "core/layer.h"
#include "core/layerStack.h"

#include "events/event.h"
#include "events/eventType.h"
#include "events/eventListener.h"

#include "events/input.h"
#include "core/keyCodes.h"
#include "core/mouseButtonCodes.h"

#include "renderer/renderCommand.h"
#include "renderer/renderer3D.h"
#include "renderer/renderer2D.h"
#include "renderer/shader.h"
#include "renderer/texture.h"
#include "renderer/vertexArray.h"
#include "renderer/buffers.h"
#include "renderer/framebuffer.h"

#include "graphics/ui/uiComponent.h"
#include "graphics/ui/label.h"
#include "graphics/ui/button.h"

#include "renderer/utils/textureAtlas.h"
#include "renderer/utils/shaderLibrary.h"
#include "renderer/utils/font.h"

#include "scene/component.h"
#include "scene/entity.h"
#include "scene/scene.h"
#include "scene/script.h"
#include "scene/sceneSerializer.h"
#include "scene/assetManager.h"

#include "graphics/cameras/camera.h"
#include "graphics/cameras/sceneCamera.h"
#include "graphics/cameras/staticCamera.h"

#include "math/vector.h"
#include "math/matrix.h"
#include "math/transform.h"
#include "math/algorithm.h"
#include "math/projection.h"

#include "core/application.h"
#include "core/timestep.h"

#include "utils/colorUtils.h"
