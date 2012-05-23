
#include "TalonPrefix.h"
#include <Talon/Graphics/RenderDevice.h>
#include <Talon/Platform/Window.h>


using namespace std;

namespace Talon
{
    class RenderDevice::Impl
    {
    public:
		IDXGISwapChain* swapChain;
		ID3D11RenderTargetView* backBufferRTV;
		ID3D11Device* device;
		ID3D11DeviceContext* context;
		D3D_FEATURE_LEVEL featureLevel;
		

		static IDXGIFactory1* s_DXGI;
    };

	IDXGIFactory1* RenderDevice::Impl::s_DXGI = nullptr;

    RenderDevice::RenderDevice(Window* window)
        : m_window(window)
        , m_pImpl(make_unique<Impl>())
    {
		if (RenderDevice::Impl::s_DXGI == nullptr)
			CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&RenderDevice::Impl::s_DXGI);
		else
			RenderDevice::Impl::s_DXGI->AddRef();

		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
		HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, creationFlags, nullptr, 0, D3D11_SDK_VERSION, &m_pImpl->device, &m_pImpl->featureLevel, &m_pImpl->context);
		
		// #if TALON_WINRT
		// TODO: Handle creation from Metro (Win 8).
		// #else
		DXGI_SWAP_CHAIN_DESC swapDesc;
		ZeroMemory(&swapDesc, sizeof(swapDesc));
		swapDesc.BufferCount = 1;
		swapDesc.BufferDesc.Width = window->GetWidth();
		swapDesc.BufferDesc.Height = window->GetHeight();
		swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapDesc.OutputWindow = window->GetHandle();
		swapDesc.SampleDesc.Count = 1;
		swapDesc.SampleDesc.Quality = 0;
		swapDesc.Windowed = TRUE;
		hr = RenderDevice::Impl::s_DXGI->CreateSwapChain(m_pImpl->device, &swapDesc, &m_pImpl->swapChain);
		// #endif

		ID3D11Texture2D* backBuffer;
		hr = m_pImpl->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
		hr = m_pImpl->device->CreateRenderTargetView(backBuffer, nullptr, &m_pImpl->backBufferRTV);
	}

	RenderDevice::~RenderDevice()
	{
		TALON_SAFE_RELEASE(m_pImpl->backBufferRTV);
		TALON_SAFE_RELEASE(m_pImpl->swapChain);
		TALON_SAFE_RELEASE(m_pImpl->context);
		TALON_SAFE_RELEASE(m_pImpl->device);
		TALON_SAFE_RELEASE(m_pImpl->device);

		if (RenderDevice::Impl::s_DXGI)
		{
			if (RenderDevice::Impl::s_DXGI->Release() == 0)
				RenderDevice::Impl::s_DXGI = nullptr;
		}
	}

    void RenderDevice::BeginFrame()
    {
		m_pImpl->context->OMSetRenderTargets(1, &m_pImpl->backBufferRTV, nullptr);
		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT) GetWindow()->GetWidth();
		vp.Height = (FLOAT) GetWindow()->GetHeight();
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;

		FLOAT clearColor[] = { 1.0f, 0.3882352941176471f, 0.2784313725490196f, 1.0f };

		m_pImpl->context->RSSetViewports(1, &vp);
		m_pImpl->context->ClearRenderTargetView(m_pImpl->backBufferRTV, clearColor);
    }

    void RenderDevice::EndFrame()
    {
		m_pImpl->context->OMSetRenderTargets(1, nullptr, nullptr);
    }

	D3D_FEATURE_LEVEL RenderDevice::GetFeatureLevel() const
	{
		return m_pImpl->featureLevel;
	}

	ID3D11Device* RenderDevice::GetDevice() const
	{
		return m_pImpl->device;
	}

	ID3D11DeviceContext* RenderDevice::GetDeviceContext() const
	{
		return m_pImpl->context;
	}
}