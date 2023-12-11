#pragma once

namespace RendererModule
{
	enum class FILL_MODE : int
	{
		SOLID,    // 솔리드 
		WIRE_FRAME, // 와이어 프레임  
		END
	};

	enum class INPUT_LAYOUT : int
	{
		SIMPLE,
		BASIC,
		END,
	};

}