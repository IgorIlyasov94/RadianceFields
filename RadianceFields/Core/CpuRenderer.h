#pragma once

#include "../Includes.h"
#include "IRadianceFieldGrid.h"
#include "Viewport.h"
#include "DataTypes.h"

namespace Core
{
	class CpuRenderer
	{
	public:
		CpuRenderer();
		~CpuRenderer();

		void SetViewport(const Viewport& viewport);
		void SetTargetImage(std::vector<float>& target);

		void SetGrid(IRadianceFieldGrid* grid) noexcept;

		void DispatchRays(uint2 groupNumber, uint2 groupInnerLoopSize);

	private:
		inline void ValidateViewport(const Viewport& viewport) const;
		inline uint32_t CalculateTotalThreadNumber(const Viewport& viewport, uint2 groupNumber) const;

		Viewport _viewport;
		IRadianceFieldGrid* _grid;
		float* targetImageAddress;
	};
}
