#pragma once

/*
PCH: Yes
*/

namespace ba
{
	class GraphicComponent;

	class GraphicComponentManager : private Uncopiable
	{
	private:
		GraphicComponentManager();

	public:
		static GraphicComponentManager& GetInstance();

		bool Init();
		void Destroy();

		template<class Type>
		Type* CreateComponent(const std::string& key_str);

		void DestroyComponent(const std::string& key_str);

	private:
		std::map<std::string, GraphicComponent*> components_;
	};

	template<class Type>
	inline Type* GraphicComponentManager::CreateComponent(const std::string& key_str)
	{
		auto iter = components_.find(key_str);

		GraphicComponent* component = nullptr;

		if (iter == components_.end())
		{
			// Create new component for the key.
			component = new Type;
			components_.insert({ key_str, component });
		}
		else
		{
			// There is already a value for the key.
			component = iter->second;
		}
		
		return dynamic_cast<Type*>(component);
	}
}
