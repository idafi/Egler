#pragma once

#include "../Egler.Core/Core/Core.hpp"
#include "../Egler.Core/IO/IO.hpp"
#include "../Egler.Core/Logging/Logging.hpp"
#include "../Egler.Core/Video/Video.hpp"

namespace Egler
{
	static constexpr int MaxShaders = 64;
	static constexpr int MaxModels = 64;
	static constexpr int MaxMaterials = 96;
	static constexpr int MaxEntities = 16;
}

#include "Entity.hpp"

#include "ShaderMan.hpp"
#include "MaterialMan.hpp"
#include "ModelMan.hpp"
#include "EntityMan.hpp"
#include "EglerContext.hpp"