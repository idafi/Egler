#pragma once

#include "../Egler.Core/Common.hpp"
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
	static constexpr int MaxUnits = 16;
}

#include "EntitySystem.hpp"
#include "ModelSystem.hpp"
#include "ShaderSystem.hpp"
#include "MaterialSystem.hpp"
#include "Unit.hpp"
#include "UnitSystem.hpp"
#include "EglerContext.hpp"