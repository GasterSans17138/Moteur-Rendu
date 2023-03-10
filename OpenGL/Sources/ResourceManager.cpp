#include <ResourceManager.hpp>
#include "Debug.hpp"
#include "Material.hpp"
#include "Interface.hpp"
#include <iostream>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

using namespace Resources;
using namespace std;

unordered_map<string, Resource*> ResourceManager::resourceMap;

Resource* ResourceManager::Create(Resource* resource, const string& name, const string& path)
{
	resource->name = name;
	resource->Load(path);
	if (!resource)
	{
		DEBUG_LOGERROR("Resource loading failed.");
		return nullptr;
	}
	resourceMap.emplace(name, resource);
	return resource;
}

Resource* ResourceManager::Create(Resource* resource, const string& name)
{
	resource->name = name;
	resourceMap.emplace(name, resource);
	return resource;
}

Resource* ResourceManager::Get(const string& name)
{

	if (resourceMap[name])
	{
		return resourceMap[name];
	}
}

void ResourceManager::Clear()
{
	//std::cout << "Clearing all resources" << std::endl;
	for (std::pair<string, Resource*> resource : resourceMap)
	{
		resource.second->Unload();
		//std::cout << resource.first << std::endl;
		delete resource.second;
	}
}

void ResourceManager::DisplayGUI()
{
	ImGui::Begin("Resources", 0, ImGuiWindowFlags_NoMove);
	CustomInterface::SetResourceManager();
	
	ImGui::OpenPopupOnItemClick("Add Resource");
	if (ImGui::Button("New Material"))
	{
		Create(new Resources::Material(nullptr, Core::myMath::Vec3(1, 1, 1), 32), ("new mat##" + to_string(resourceMap.size())).c_str());
	}

	int index = 0;
	for (std::pair<string, Resource*> resource : resourceMap)
	{
		if ((int)resource.second->type == 2 || (int)resource.second->type == 3)
			continue;

		bool headerOpen = ImGui::CollapsingHeader(resource.first.c_str());

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
		{
			void** ptr = new void* (resource.second);
			ImGui::SetDragDropPayload(to_string((int)resource.second->type).c_str(), ptr, sizeof(resource.second));
			ImGui::Text(resource.second->name.c_str());
			ImGui::EndDragDropSource();
			delete ptr;
		}

		if (headerOpen)
		{
			resource.second->DisplayGUI(index);
			index++;
		}
	}

	ImGui::End();
}