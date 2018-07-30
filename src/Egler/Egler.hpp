#pragma once

#include "../Egler.Core/Core/Core.hpp"
#include "../Egler.Core/IO/IO.hpp"
#include "../Egler.Core/Logging/Logging.hpp"
#include "../Egler.Core/Video/Video.hpp"

namespace Egler
{
	// the context holds everything we're about to include, so a forward declaration is needed
	class EglerContext;

	static constexpr int MaxModels = 64;
	static constexpr int MaxShaders = 64;
	static constexpr int MaxMaterials = 96;
	static constexpr int MaxEntities = 16;
}

#include "ModelMan.hpp"
#include "ShaderMan.hpp"
#include "MaterialMan.hpp"
#include "Entity.hpp"
#include "EntityMan.hpp"
#include "EglerContext.hpp"