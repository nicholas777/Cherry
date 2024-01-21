#include "epch.h"
#include "ScriptEngine.h"
#include "core/Log.h"
#include "ScriptAPI.h"
#include "Debug/Profiler.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"

// TODO: Temporary
#define USER_PROJ_DLL_PATH "assets/Project/ScriptsBin/UserProject.dll"

namespace Cherry
{

	static const char* EntityIDMonoName = "__Entity_ID";

	MonoDomain* ScriptEngine::m_RootDomain = nullptr;
	MonoDomain* ScriptEngine::m_AppDomain = nullptr;
	Shared<Assembly> ScriptEngine::m_CoreAssembly = nullptr;
	Shared<Assembly> ScriptEngine::m_GameAssembly = nullptr;
	Shared<Class> ScriptEngine::m_EntityClass = nullptr;

	const char* ScriptEngine::m_GameDLLPath = "";

	std::vector<ScriptEngine::ScriptedEntity> ScriptEngine::m_ScriptedEntities{};
	std::unordered_map<std::string, ScriptEngine::EntityClass> ScriptEngine::m_EntityClasses{};

	static Scene* s_Scene = nullptr;

	// TODO: Better error messages in the scripting engine
	static char* ReadFile(std::string filename, uint32_t& filesize)
	{
		std::ifstream stream(filename, std::ios::binary | std::ios::ate);

		CH_VALIDATE(stream);

		uint32_t size = stream.tellg();
		stream.seekg(0, std::ios::beg);

		char* buffer = new char[size];
		if (!stream.read(buffer, size))
		{
			CH_ASSERT(false, "Unable to read stream");
			return nullptr;
		}

		filesize = size;
		return buffer;
	}

	void ScriptEngine::Init()
	{
		CH_PROFILE_FUNC();

		m_GameDLLPath = USER_PROJ_DLL_PATH;

		mono_set_assemblies_path("assets/mono/lib");
		
		MonoDomain* domain = mono_jit_init("ScriptingRuntime");
		if (domain == nullptr)
		{
			CH_ERROR("Mono unable to initialize!");
			return;
		}
		
		m_RootDomain = domain;
		InitScriptingSystem();
		ScriptAPI::Init();

	}

	void ScriptEngine::Shutdown()
	{
		mono_jit_cleanup(m_RootDomain);
	}

	Shared<Assembly> ScriptEngine::LoadAssembly(std::string path)
	{
		CH_PROFILE_FUNC();

		uint32_t filesize = 0;
		char* filedata = ReadFile(path, filesize);

		MonoImageOpenStatus status;
		MonoImage* image = mono_image_open_from_data_full(filedata, filesize, true, &status, false);

		CH_ASSERT(status == MONO_IMAGE_OK, "Error: failed to generate assembly image");

		MonoAssembly* assembly = mono_assembly_load_from_full(image, path.c_str(), &status, false);
		mono_image_close(image);

		CH_VALIDATE(assembly);

		delete[] filedata;
		return new Assembly(assembly, m_AppDomain);
	}

	

	void ScriptEngine::InitScriptedEntity(Entity entity)
	{
		if (!entity.HasComponent<ScriptComponent>())
			return;

		ScriptComponent& comp = entity.GetComponent<ScriptComponent>();

		if (!m_EntityClasses.count(comp.Name))
		{
			CH_ASSERT(false, "Invalid class name! Script doesn't exist");
			return;
		}

		EntityClass& c = m_EntityClasses[comp.Name];
		ScriptedEntity se{};
		se.OnCreate = c.OnCreate;
		se.OnUpdate = c.OnUpdate;
		se.OnDestroy = c.OnDestroy;

		se.entity = entity;

		se.Instance = c.klass->Instantiate(m_AppDomain);
		
		Shared<Method> constructor = m_EntityClass->GetMethod(".ctor", 1);
		uint32_t handle = entity.GetHandle();
		constructor->Invoke(se.Instance, handle);

		MonoException* exception = nullptr;
		if (se.OnCreate)
			se.OnCreate(se.Instance->GetMonoObject(), &exception);

		m_ScriptedEntities.push_back(se);
	}

	const std::vector<Shared<Field>>* ScriptEngine::ScriptClassGetFields(const char* c)
	{
		if (!IsScriptClass(c))
			return nullptr;

		return &m_EntityClasses.at(c).fields;
	}

	void ScriptEngine::UnloadScriptedEntities()
	{
		MonoException* exception = nullptr;
		for (auto& entity : m_ScriptedEntities)
		{
			if (entity.OnDestroy)
				entity.OnDestroy(entity.Instance->GetMonoObject(), &exception);
		}

		m_ScriptedEntities.clear();
	}

	bool ScriptEngine::IsScriptClass(const char* name)
	{
		return m_EntityClasses.count(std::string(name));
	}

	Shared<Object> ScriptEngine::GetScriptedEntity(Entity entity)
	{
		for (auto& se : m_ScriptedEntities)
		{
			if (se.entity == entity)
			{
				return se.Instance;
			}
		}

		return nullptr;
	}

	Scene* ScriptEngine::GetRuntimeScene()
	{
		return s_Scene;
	}

	void ScriptEngine::OnRuntimeStart(Scene* scene)
	{
		s_Scene = scene;
	}

	void ScriptEngine::OnRuntimeStop()
	{
		s_Scene = nullptr;
		UnloadScriptedEntities();
	}

	void ScriptEngine::UpdateScriptedEntities(float delta)
	{
		MonoException* exception;
		for (auto& entity : m_ScriptedEntities)
		{
			entity.OnUpdate(entity.Instance->GetMonoObject(), delta, &exception);
		}
	}

	// Reloads the core and game assembly. Used for hot reloading.
	void ScriptEngine::ReloadAssemblies()
	{
		UnloadAppDomain();
		CreateAppDomain();
		InitScriptingSystem();
	}

	void ScriptEngine::LoadEntityClasses()
	{
		auto image = m_GameAssembly->m_Image;

		for (uint32_t i = 0; i < m_GameAssembly->m_TypeDefinitions.Size; i++)
		{
			uint32_t columns[MONO_TYPEDEF_SIZE];
			mono_metadata_decode_row(m_GameAssembly->m_TypeDefinitions.Table, i, columns, MONO_TYPEDEF_SIZE);

			const char* name = mono_metadata_string_heap(image, columns[MONO_TYPEDEF_NAME]);
			const char* nameSpace = mono_metadata_string_heap(image, columns[MONO_TYPEDEF_NAMESPACE]);

			MonoClass* monoClass = mono_class_from_name(image, nameSpace, name);
			if (mono_class_is_subclass_of(monoClass, m_EntityClass->GetMonoClass(), false))
			{
				// Methods
				EntityClass c{};
				c.klass = new Class(monoClass);
				if (auto onCreate = c.klass->GetMethodIfExists("OnCreate", 0))
					c.OnCreate = (OnCreateFunc)onCreate->GetMethodThunk();
				if (auto onUpdate = c.klass->GetMethodIfExists("OnUpdate", 1))
					c.OnUpdate = (OnUpdateFunc)onUpdate->GetMethodThunk();
				if (auto onDestroy = c.klass->GetMethodIfExists("OnDestroy", 0))
					c.OnDestroy = (OnDestroyFunc)onDestroy->GetMethodThunk();

				// Fields

				CH_INFO("Class: {}", name);

				void* iterator = nullptr;
				while (MonoClassField* monoField = mono_class_get_fields(monoClass, &iterator))
				{
					Shared<Field> field = new Field(monoField, monoClass);

					ScriptFieldType type = field->GetType();

					if (field->GetAccessibility() & Accessibility::Public && type != ScriptFieldType::None)
						c.fields.push_back(field);
				}
				
				m_EntityClasses.emplace(std::string(name), c);
			}
		}
	}

	void ScriptEngine::InitScriptingSystem()
	{
		CreateAppDomain();

		m_CoreAssembly = LoadAssembly("assets/CoreScripts/ScriptLib.dll");
		m_GameAssembly = LoadAssembly(m_GameDLLPath);

		m_EntityClass = m_CoreAssembly->GetClassByName("Entity", "Cherry");
		LoadEntityClasses();
	}

	void ScriptEngine::CreateAppDomain()
	{
		m_AppDomain = mono_domain_create_appdomain("AppDomain", nullptr);
		mono_domain_set(m_AppDomain, true);
	}

	void ScriptEngine::UnloadAppDomain()
	{
		mono_domain_set(m_RootDomain, true);
		mono_domain_unload(m_AppDomain);
	}

}
