
#include "TalonPrefix.h"
#include <Talon/Graphics/RenderDevice.h>
#include <Talon/Platform/Window.h>


using namespace std;

namespace Talon
{
	
    class RenderDevice::Impl
    {
	public:
		void CreateDevice(Window* window);

		void DrawIndexed(u32 indexCount, u32 startIndex, i32 baseVertexLocation);
    public:
		CComPtr<IDXGISwapChain> swapChain;
		CComPtr<ID3D11RenderTargetView> backBufferRTV;
		CComPtr<ID3D11Device> device;
		CComPtr<ID3D11DeviceContext> context;
		CComPtr<IDXGIDevice1> dxgiDevice;
		CComPtr<IDXGIAdapter1> dxgiAdapter;
		CComPtr<IDXGIFactory1> dxgiFactory;

		DXGI_ADAPTER_DESC1 adapterDesc;
		D3D_FEATURE_LEVEL featureLevel;
    };

	void RenderDevice::Impl::CreateDevice(Window* window)
	{
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
		ThrowIfFailed(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, creationFlags, nullptr, 0, D3D11_SDK_VERSION, &device, &featureLevel, &context));

		ThrowIfFailed(device.QueryInterface(&dxgiDevice));
		ThrowIfFailed(dxgiDevice->GetParent(__uuidof(IDXGIAdapter1), (void **)&dxgiAdapter));
		ThrowIfFailed(dxgiAdapter->GetParent(__uuidof(IDXGIFactory1), (void **)&dxgiFactory));

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
		ThrowIfFailed(dxgiFactory->CreateSwapChain(device, &swapDesc, &swapChain));
		// #endif

		CComPtr<ID3D11Texture2D> backBuffer;
		ThrowIfFailed(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&backBuffer));
		ThrowIfFailed(device->CreateRenderTargetView(backBuffer, nullptr, &backBufferRTV));
	}

	void RenderDevice::Impl::DrawIndexed(u32 indexCount, u32 startIndex, i32 baseVertexLocation)
	{
		context->DrawIndexed(indexCount, startIndex, baseVertexLocation);
	}

    RenderDevice::RenderDevice(Window* window)
        : m_window(window)
        , m_pImpl(make_unique<Impl>())
    {
		m_pImpl->CreateDevice(window);
	}

	RenderDevice::~RenderDevice()
	{
	}

    void RenderDevice::BeginFrame()
    {
		ID3D11RenderTargetView* views = m_pImpl->backBufferRTV;
		m_pImpl->context->OMSetRenderTargets(1, &views, nullptr);
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
		ThrowIfFailed(m_pImpl->swapChain->Present(1, 0));

		ID3D11RenderTargetView* nullView = nullptr;
		m_pImpl->context->OMSetRenderTargets(1, &nullView, nullptr);
    }

	void RenderDevice::DrawIndexed(u32 indexCount, u32 startIndex, i32 baseVertexLocation)
	{
		m_pImpl->DrawIndexed(indexCount, startIndex, baseVertexLocation);
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