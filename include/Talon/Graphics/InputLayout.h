
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
		InputLayout(RenderDevice* device, const InputElement* inputElements, u32 elementCount, Shader* vertexShader);
		~InputLayout();


	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}