#include "epch.h"
#include "ScriptEngine.h"
#include "core/Log.h"

namespace Cherry
{

	MonoDomain* ScriptEngine::m_RootDomain = nullptr;
	MonoDomain* ScriptEngine::m_AppDomain = nullptr;
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
		mono_set_assemblies_path("assets/mono/lib");
		
		MonoDomain* domain = mono_jit_init("ScriptingRuntime");
		if (domain == nullptr)
		{
			CH_ERROR("Mono unable to initialize!");
			return;
		}
		
		m_RootDomain = domain;

		m_AppDomain = mono_domain_create_appdomain("AppDomain", nullptr);
		mono_domain_set(m_AppDomain, true);

	}

	void ScriptEngine::Shutdown()
	{
		delete m_RootDomain;
		delete m_AppDomain;
	}

	Shared<Script> ScriptEngine::LoadScript(std::string path)
	{
		uint32_t filesize = 0;
		char* filedata = ReadFile(path, filesize);

		MonoImageOpenStatus status;
		MonoImage* image = mono_image_open_from_data_full(filedata, filesize, true, &status, false);

		CH_ASSERT(status == MONO_IMAGE_OK, "Error: failed to generate assembly image");

		MonoAssembly* assembly = mono_assembly_load_from_full(image, path.c_str(), &status, false);
		mono_image_close(image);

		CH_VALIDATE(assembly);

		delete[] filedata;
		return new Script(assembly, m_AppDomain);
	}

}