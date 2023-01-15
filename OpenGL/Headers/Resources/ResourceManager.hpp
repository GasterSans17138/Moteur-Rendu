#pragma once
#include <Resources/IResource.hpp>
#include <unordered_map>
#include <iostream>

namespace Resources
{
	class ResourceManager
	{
	private:
		std::unordered_map<std::string, IResource*> mResourceMap;

	public:
		static ResourceManager* GetInstance()
		{
			static ResourceManager* singleton = nullptr;
			if (singleton == nullptr)
				singleton = new ResourceManager{};
			return singleton;
		}

		template<typename T>
		T* Create(const std::string rsrcName, const char* path)
		{
			T* rsc = new T(path);
			mResourceMap[rsrcName] = (IResource*)rsc;
			return rsc;
		}

		template<typename T>
		void Create(const std::string rsrcName, T* rsrcPtr)
		{
			mResourceMap[rsrcName] = (IResource*)rsrcPtr;
		}

		template<typename T>
		T* Get(const std::string rsrcName)
		{
			IResource* rsrc = mResourceMap[rsrcName];
			if (rsrc)
				return reinterpret_cast<T*>(rsrc);
			else
				return nullptr;
		}

		void Delete(const std::string rsrcName);

		void Clear();

	private:
		ResourceManager() {};
	};
}