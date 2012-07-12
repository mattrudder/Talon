
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Graphics/BufferUsage.h>
#include <Talon/Graphics/BufferMapType.h>
#include <Talon/Graphics/RenderDeviceChild.h>

namespace Talon
{
	class ConstantBufferBase : public RenderDeviceChild
	{
	public:
		virtual ~ConstantBufferBase();
		
		u32 GetBufferSize() const;
		
#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		ID3D11Buffer* GetBuffer() const;
#else
		u32 GetBuffer() const;
#endif
	protected:
		ConstantBufferBase(RenderDevice* renderDevice, u32 bufferSize, BufferUsage bufferUsage, void* initialData = nullptr);

		void Update(u32 bufferSize, void* data);
		void Map(BufferMapType mapType, void** ppData);
		void Unmap();
		
	private:
		u32 m_bufferSize;
		BufferUsage m_bufferUsage;
		
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
	
	template <typename BufferType>
	class ConstantBuffer : public ConstantBufferBase
	{
	public:
		static std::shared_ptr<ConstantBufferBase> Create(RenderDevice* renderDevice, BufferUsage bufferUsage, BufferType* initialData = nullptr)
		{
			return std::shared_ptr<ConstantBufferBase>(new ConstantBuffer(renderDevice, bufferUsage, initialData));
		}
		
		void Update(BufferType* data) { ConstantBufferBase::Update(sizeof(BufferType), data); }
		void Map(BufferMapType mapType, BufferType** ppData) { ConstantBufferBase::Map(mapType, ppData); }
		void Unmap() { ConstantBufferBase::Unmap(); }
		
	protected:
		ConstantBuffer(RenderDevice* renderDevice, BufferUsage bufferUsage, BufferType* initialData = nullptr)
		: ConstantBufferBase(renderDevice, sizeof(BufferType), bufferUsage, initialData)
		{
		}
	};
}