#include "logs.h"

void c_logs::push_log(const std::string& text, const float textalpha, const float spacing)
{
	m_logs.emplace_front
	(
		logs_data_t
		(
			g_sdk.m_interfaces.m_globals->m_realtime,
			text,
			textalpha,
			spacing
		)
	);

	while (m_logs.size() > 10)
		m_logs.pop_back();
}

void c_logs::instance()
{
	for (int i{}; i < m_logs.size(); i++)
	{
		auto* logs = &m_logs[i];
		if (!logs)
			continue;

		const auto time_after_creation = g_sdk.m_interfaces.m_globals->m_realtime - logs->m_creation_time;
		if (time_after_creation >= 5.0f)
		{
			m_logs.erase(m_logs.begin() + i);
		}

		if (time_after_creation >= 4.75f)
		{
			logs->m_TextAlpha = std::clamp(((5.0f - time_after_creation) / 0.25f) * 255.0f, 0.0f, 255.0f);
			logs->m_BackAlpha = std::clamp(((5.0f - time_after_creation) / 0.25f) * 50.0f, 0.0f, 50.0f);
			logs->m_spacing = std::clamp(((5.0f - time_after_creation) / 0.25f) * 24.0f, 0.0f, 24.0f);

		} else if (time_after_creation <= 0.25f) {

			logs->m_TextAlpha = std::clamp((1.0f - (0.25f - time_after_creation) / 0.25f) * 255.0f, 0.0f, 255.0f);
			logs->m_BackAlpha = std::clamp((1.0f - (0.25f - time_after_creation) / 0.25f) * 50.0f, 0.0f, 50.0f);
			logs->m_spacing = std::clamp((1.0f - (0.25f - time_after_creation) / 0.25f) * 24.0f, 0.0f, 24.0f);
		}

		auto spacing = 0.0f;
		if (i)
		{
			for (int i2{}; i2 < i; i2++)
				spacing += m_logs[i2].m_spacing;
		}

		c_color aColor = { 158, 209, 54, 255 };

		if (!logs->m_printed)
		{
			g_sdk.m_interfaces.m_cvar->console_color_print_f(aColor, _("[digital-sdk] "));
			g_sdk.m_interfaces.m_cvar->console_color_print_f(aColor, _("%s\n"), logs->m_text.c_str());

			logs->m_printed = true;
		}

		c_render::get()->text(g_sdk.m_fonts.m_logs, ImVec2(5.0f, spacing + 2.5f), logs->m_text, c_color(255, 255, 255, (int)(logs->m_TextAlpha) ), false);
	}
}