#include <Cherry.h>
#include <vector>

using namespace Cherry;

class Main : public EventListener
{
public:
	Main(std::vector<EventType> types)
		: EventListener(types) {};

	void OnEvent(Event e) override
	{
		CH_INFO("Mouse Moved");
	};
};

void Cherry::OnStart()
{
	//CH_INFO("Game startup");
	std::vector<EventType> types = std::vector<EventType>();
	types.push_back(EventType::MouseMoveEvent);

	Main* main = new Main(types);
}

void Cherry::OnUpdate()
{

}

void Cherry::OnShutdown()
{
	
}
