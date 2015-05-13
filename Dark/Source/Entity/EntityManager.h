#pragma once
#include <map>
#include <vector>
#include "RenderProperty.h"

using namespace::std;

//Forward Declarations
class RenderEntity;

namespace DarkEngine
{
	class EntityManager
	{
	public:
		static EntityManager& Instance()
		{
			static EntityManager obj;
			return obj;
		}

		virtual ~EntityManager(void);
		bool Register(RenderEntity& entity);
		bool UpdateEntites(float dt);
		bool RenderEntities();
	private:
		bool PrepareRendering(CRenderProperty&);

		EntityManager(void);
		EntityManager(const EntityManager& rhs);
		EntityManager operator= (const EntityManager& rhs);

		typedef std::map<char * /* Name of the render property*/, std::vector<RenderEntity*>> RenderMap;
		RenderMap m_renderMap;
	};

}
