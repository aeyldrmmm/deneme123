#pragma once
#include "bindings/gui/gui_element.hpp"
#include "lua_patch.hpp"
#include "sol.hpp"
#include "core/data/menu_event.hpp"
#include <services/gui/gui_service.hpp>

namespace big
{
	class script;

	class lua_module
	{
		sol::state m_state;

		std::string m_module_name;
		rage::joaat_t m_module_id;

		std::chrono::time_point<std::chrono::file_clock> m_last_write_time;

	public:
		std::vector<script*> m_registered_scripts;
		std::vector<std::shared_ptr<lua_patch>> m_registered_patches;

		std::vector<big::tabs> m_owned_tabs;

		std::unordered_map<big::tabs, std::vector<big::tabs>> m_tab_to_sub_tabs;

		std::unordered_map<rage::joaat_t, std::vector<std::shared_ptr<lua::gui::gui_element>>> m_gui;
		std::unordered_map<menu_event, std::vector<sol::function>> m_event_callbacks;
		std::vector<void*> m_allocated_memory;

		lua_module(std::string module_name);
		~lua_module();

		rage::joaat_t module_id() const;
		const std::string& module_name() const;
		const std::chrono::time_point<std::chrono::file_clock> last_write_time() const;

		// used for adding our own paths to the search paths of the lua require function
		void add_folder_to_require_available_paths(const big::folder& scripts_folder);

		void init_lua_api();
	};
}