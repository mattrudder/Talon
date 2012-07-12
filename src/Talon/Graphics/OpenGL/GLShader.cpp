	
#include "TalonPrefix.h"

#include "GLUtility.h"
#include <Talon/Graphics/RenderDevice.h>
#include <Talon/Graphics/Shader.h>
#include <Talon/Platform/Platform.h>

#import <Cocoa/Cocoa.h>
namespace Talon
{
	class Shader::Impl
	{
	public:
		bool LoadFromMemory(RenderDevice* device, ShaderType type, const char* shaderText, const char* sourceFileName);
		
		GLuint shaderInstance;
	};
	
	std::shared_ptr<Shader> Shader::CreateFromFile(RenderDevice* device, ShaderType type, const char* filePath)
	{
		return CreateFromMemory(device, type, Platform::GetTextFromFile(filePath).c_str(), filePath);
	}
	
	std::shared_ptr<Shader> Shader::CreateFromMemory(RenderDevice* device, ShaderType type, const char* shaderText, const char* sourceFileName)
	{
		Shader* shader = new Shader(device, type);
		
		if (!shader->m_pImpl->LoadFromMemory(device, type, shaderText, sourceFileName))
		{
			delete shader;
			shader = nullptr;
		}
		
		return std::shared_ptr<Shader>(shader);
	}
	
	bool Shader::Impl::LoadFromMemory(RenderDevice* device, ShaderType type, const char* shaderText, const char* sourceFileName)
	{
		bool result = false;
		
		device->WithContext([this, type, &shaderText, &result]()
		{
			NSOpenGLContext* context = [NSOpenGLContext currentContext];
			bool hasContext = context == nil;
			
			if (false && hasContext)
				return;
			
			GLenum glType = GL::ToShaderType(type);
			
			shaderInstance = glCreateShader(glType);
			glShaderSource(shaderInstance, 1, &shaderText, 0);
			glCompileShader(shaderInstance);
			
			GLint shaderInfo;
			glGetShaderiv(shaderInstance, GL_COMPILE_STATUS, &shaderInfo);
			
			result = shaderInfo == GL_TRUE;
			if (!result)
			{
				GLsizei logLength;
				glGetShaderiv(shaderInstance, GL_INFO_LOG_LENGTH, &shaderInfo);
				char* szLog = new char[shaderInfo];
				glGetShaderInfoLog(shaderInstance, shaderInfo, &logLength, szLog);
				glDeleteShader(shaderInstance);
				
				TalonLog(szLog);
				
				delete [] szLog;
				
				shaderInstance = 0;
			}
		});
		
		
		return result;
	}
	
	/** Sets a texture on the current shader instance. */
	void Shader::SetTexture(u32 index, std::shared_ptr<Texture> texture)
	{
	}
	
	/** Sets a buffer of values on the current shader instance. */
	void Shader::SetConstantBuffer(u32 index, std::shared_ptr<ConstantBufferBase> buffer)
	{
	}
	
	Shader::Shader(RenderDevice* device, ShaderType type)
		: RenderDeviceChild(device)
		, m_type(type)
	{
	}
	
	Shader::~Shader()
	{
	}
}