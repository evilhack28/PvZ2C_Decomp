//
//  Toggles.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Toggles.h"
#include "PVZLiveConfig.h"
#include "GameEventMgr.h"

/////////////// Lifecycle ///////////////

Toggles::Toggles(LiveConfigToggleGetter& i_liveConfigToggleGetter)
	: m_toggleGetter(i_liveConfigToggleGetter)
{
}

Toggles::~Toggles()
{
}

Toggles& Toggles::GetInstance()
{
	static Toggles s_instance __attribute__((section(".bss.TogglesInstance"))) (LiveConfigToggleGetter::GetInstance());
	return s_instance;
}

/////////////// Toggles ///////////////

void Toggles::OverrideToggle(const std::string& key, bool enabled)
{
	m_overrides[key] = enabled;
	gMessageRouter->Broadcast(Message::ToggleOverrideSet, std::string(key), IsEnabled(key));
}

void Toggles::SwrveToggle(const std::string& key, bool enabled)
{
	m_swrvedToggles[key] = enabled;
	gMessageRouter->Broadcast(Message::ToggleOverrideSet, std::string(key), IsEnabled(key));
}

bool Toggles::IsEnabled(const std::string& key)
{
	std::map<std::string, bool>* toggles = &m_overrides;
	bool result;
	if (!(toggles->find(key) != toggles->end()))
	{
		toggles = &m_swrvedToggles;
		if (__builtin_expect(!(toggles->find(key) != toggles->end()), 1))
		{
			std::vector<Toggle> liveToggles = m_toggleGetter.GetLiveConfigToggles();
			std::vector<Toggle>::iterator it = liveToggles.begin();
			for (; (result = (it != liveToggles.end())); ++it)
			{
				if ((*it).Key.compare(key) == 0)
				{
					result = (*it).Enabled;
					goto done;
				}
			}
			Sexy::OutputDebugStrF("\n!! Toggle \"%s\" not found in liveconfig.json!  Did you typo the name?\n", key.c_str());
			goto done;
		}
	}
	result = (*toggles)[key];
done:
	return result;
}

__asm__(".pushsection .bss.DsoHandle,\"aw\",@nobits\n.local __dso_handle\n__dso_handle: .zero 8\n.popsection");
