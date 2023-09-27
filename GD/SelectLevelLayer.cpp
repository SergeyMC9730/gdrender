#include "SelectLevelLayer.h"
#include "GameLayer.h"
#include "defines.h"
#if IMGUI
#include "imgui.h"
#endif
#include "Application.h"

#include <cpr/cpr.h>
#include "Common.h"

std::shared_ptr<SelectLevelLayer> SelectLevelLayer::create()
{
	std::shared_ptr<SelectLevelLayer> ptr(new SelectLevelLayer);

	if (ptr->init())
		return ptr;

	return nullptr;
}

bool SelectLevelLayer::init()
{
	ImageLoader::ParsePlist("Resources\\GJ_GameSheet-uhd.plist");
	ImageLoader::ParsePlist("Resources\\GJ_GameSheet02-uhd.plist");
	ImageLoader::ParsePlist("Resources\\GJ_GameSheet03-uhd.plist");
	ImageLoader::ParsePlist("Resources\\GJ_GameSheet04-uhd.plist");

	return true;
}

void SelectLevelLayer::draw()
{	
	#if IMGUI
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

	ImGui::Begin("Select Level", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize);

	ImGui::InputText("Search", searchStr, 50);

	if (ImGui::Button("Load Level"))
	{
		page = 0;
		levels.clear();
		searchLevels(searchStr, page);
		memcpy(searchStrPersistent, searchStr, 50);
	}

	ImGui::SameLine();

	if (ImGui::Button("More"))
	{
		page++;
		searchLevels(searchStrPersistent, page);
	}

	ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, { 10, 10 });
	if (ImGui::BeginTable("table1", 7,
		ImGuiTableFlags_RowBg | ImGuiTableFlags_PadOuterX | ImGuiTableFlags_Resizable |
		ImGuiTableFlags_Borders | ImGuiTableFlags_NoBordersInBody))
	{
		ImGui::TableSetupColumn("Name");
		ImGui::TableSetupColumn("Downloads");
		ImGui::TableSetupColumn("Likes");
		ImGui::TableSetupColumn("Description");
		ImGui::TableSetupColumn("Stars");
		ImGui::TableSetupColumn("ID");
		ImGui::TableSetupColumn("Open");
		ImGui::TableHeadersRow();

		ImGuiListClipper clipper;
		clipper.Begin(levels.size());

		while (clipper.Step())
		{
			for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; ++row)
			{
				auto level = &levels[row];

				ImGui::TableNextRow();
				ImGui::TableNextColumn();

				ImGui::Text(level->name.c_str());
				ImGui::TableNextColumn();

				ImGui::Text(std::to_string(level->downloads).c_str());
				ImGui::TableNextColumn();

				ImGui::Text(std::to_string(level->likes).c_str());
				ImGui::TableNextColumn();

				ImGui::Text("[View description]");
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(level->description.c_str());
				ImGui::TableNextColumn();

				ImGui::Text(std::to_string(level->stars).c_str());
				ImGui::TableNextColumn();

				ImGui::Text(std::to_string(level->levelID).c_str());
				ImGui::TableNextColumn();
				
				if (ImGui::Button(("Open##" + std::to_string(level->levelID)).c_str()))
				{
					std::shared_ptr<GameLayer> gameLayer = GameLayer::create(level->levelID);
					Application::instance->pushLayer(gameLayer);
				}

			}
		}

		clipper.End();

		ImGui::EndTable();
	}
	ImGui::PopStyleVar();

	ImGui::End();
	#endif
}

void SelectLevelLayer::searchLevels(std::string searchQuery, int page)
{
	cpr::Session session;

	auto url = cpr::Url("http://www.boomlings.com/database/getGJLevels21.php");
	auto payload = cpr::Payload{ { "secret", "Wmfd2893gb7" }, { "str", searchQuery }, {"type", "0"}, {"page", std::to_string(page)} };

	session.SetUrl(url);
	session.SetPayload(payload);
	session.SetUserAgent(cpr::UserAgent(""));

	cpr::Response r = session.Post();

	if (r.status_code == -1)
		return;

	auto levelSplit = Common::splitByDelim(Common::splitByDelim(r.text, '#')[0], '|');

	for (auto str : levelSplit)
	{
		GameLevel level = GameLevel::fromString(str);
		levels.push_back(level);
	}
}