
#include <Talon/TalonPublic.h>

#include <Talon/Graphics/RenderDeviceChild.h>

namespace Talon
{
	class Shader;
	class RenderDevice;
	
	struct InputElement;
	
	class TalonApi InputLayout : public RenderDeviceChild
	{
	public:
		static std::shared_ptr<InputLayout> Create(RenderDevice* device, const InputElement* inputElements, u32 elementCount, std::shared_ptr<Shader> vertexShader);
		~InputLayout();

#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		ID3D11InputLayout* GetInputLayout() const;
#endif

	private:
		InputLayout(RenderDevice* device, const InputElement* inputElements, u32 elementCount, std::shared_ptr<Shader> vertexShader);

	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}