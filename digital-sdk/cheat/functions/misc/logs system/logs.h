#pragma once
#include "../../../../sdk/sdk.hpp"
#include <deque>

struct logs_data_t
{
	logs_data_t(const float time, const std::string& text, const float textalpha, const float spacing)
	{
		this->m_text = text;
		this->m_creation_time = time;
		this->m_TextAlpha = textalpha;
		this->m_spacing = spacing;
	}

	std::string m_text{};
	std::string m_icon{};
	float m_creation_time{};
	float m_TextAlpha{};
	float m_BackAlpha = 50.0f;
	float m_spacing{};
	bool m_printed{};
};

class c_logs : public c_singleton<c_logs>
{
	std::deque <logs_data_t> m_logs{};
public:
	void instance();
	void push_log(const std::string& text, const float textalpha, const float spacing);
};

