#include <d3dcompiler.h>

#include "d3d10_include.h"
#include "d3d10_reflection.h"

#include "../dxgi/dxgi_adapter.h"

extern "C" {
  using namespace dxvk;

  HRESULT __stdcall D3D11CoreCreateDevice(
          IDXGIFactory*       pFactory,
          IDXGIAdapter*       pAdapter,
          UINT                Flags,
    const D3D_FEATURE_LEVEL*  pFeatureLevels,
          UINT                FeatureLevels,
          ID3D11Device**      ppDevice);


  DLLEXPORT HRESULT __stdcall D3D10CoreCreateDevice_Internal(
          IDXGIFactory*           pFactory,
          IDXGIAdapter*           pAdapter,
          UINT                    Flags,
          D3D_FEATURE_LEVEL       FeatureLevel,
          ID3D10Device**          ppDevice) {
    Com<ID3D11Device> d3d11Device;

    if (ppDevice != nullptr)
      *ppDevice = nullptr;

    HRESULT hr = pAdapter->CheckInterfaceSupport(
      __uuidof(ID3D10Device), nullptr);
    
    if (FAILED(hr))
      return hr;

    hr = D3D11CoreCreateDevice(pFactory, pAdapter,
      Flags, &FeatureLevel, 1, &d3d11Device);

    if (FAILED(hr))
      return hr;
    
    Com<ID3D10Multithread> multithread;
    d3d11Device->QueryInterface(__uuidof(ID3D10Multithread), reinterpret_cast<void**>(&multithread));
    multithread->SetMultithreadProtected(!(Flags & D3D10_CREATE_DEVICE_SINGLETHREADED));
    
    if (FAILED(d3d11Device->QueryInterface(
        __uuidof(ID3D10Device), reinterpret_cast<void**>(ppDevice))))
      return E_FAIL;
    
    return S_OK;
  }

}
