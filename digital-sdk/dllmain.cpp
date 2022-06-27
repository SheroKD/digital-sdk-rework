#include "sdk/sdk.hpp"
#include "sdk/interfaces/interfaces.h"
#include "dependencies/modules/modules.h"
#include "sdk/utils/netvar manager/netvar_manager.h"
#include "cheat/hooks/hooks.h"
#include "dependencies/config manager/config_manager.h"
#include "dependencies/render/render.h"
#include "cheat/functions/misc/events/events.h"

int instance()
{
	/* waiting for serverbrowser.dll module */
	while (!GetModuleHandleA(_("serverbrowser.dll")))
		std::this_thread::sleep_for(std::chrono::seconds(5));

	/* open console */
	AllocConsole();
	if (!freopen(_("CONOUT$"), _("w"), stdout))
	{
		FreeConsole();
		return EXIT_SUCCESS;
	}

	/* set title */
	SetConsoleTitleA(_("csgo-sdk console"));

	printf(_("[t.me/shero][+] init module list...\n"));
	c_modules::get()->init();

	printf(_("[t.me/shero][+] init interface list...\n"));
	c_interfaces::get()->init();

	printf(_("[t.me/shero][+] init netvars...\n"));
	c_netvars::get()->init();

	printf(_("[t.me/shero][+] init render...\n"));
	c_render::get()->init();

	printf(_("[t.me/shero][+] init config manager...\n"));

	printf(_("[t.me/shero][+] init hooks...\n"));
	c_hooks::get()->init();

	printf(_("[t.me/shero][+] init events...\n"));
	g_events.init();

	printf(_("[t.me/shero][*] done!\n"));

	FreeConsole();
	return EXIT_SUCCESS;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	DisableThreadLibraryCalls(hModule);
	if (ul_reason_for_call != DLL_PROCESS_ATTACH)
		return FALSE;

	//MessageBoxA(nullptr, "Attached", nullptr, 0);

	if (const HANDLE thread = CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(instance), hModule, NULL, nullptr))
		CloseHandle(thread);

	return TRUE;
}

