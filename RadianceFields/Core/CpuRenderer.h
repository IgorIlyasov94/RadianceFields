#pragma once

#include "../Includes.h"
#include "IRadianceFieldGrid.h"
#include "Camera.h"
#include "Viewport.h"
#include "DataTypes.h"
#include "GridSampleMethod.h"

namespace Core
{
	class CpuRenderer
	{
	public:
		CpuRenderer();
		~CpuRenderer();

		void SetCamera(const Camera& camera);
		void SetViewport(const Viewport& viewport);
		void SetTargetImage(std::vector<float>& target);

		void SetGrid(IRadianceFieldGrid* grid) noexcept;

		void DispatchRays(GridSampleMethod sampleMethod, bool useMultithreading);

	private:
		inline void ValidateViewport(const Viewport& viewport) const;

		static const uint32_t MIN_THREAD_NUMBER = 1u;

		Camera _camera;
		Viewport _viewport;
		IRadianceFieldGrid* _grid;
		float* targetImageAddress;
	};
}
