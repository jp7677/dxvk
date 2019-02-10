#include "d3d10core_main_internal.cpp"

namespace dxvk {
  Logger Logger::s_instance("d3d10core.log");
}

extern "C" {
  using namespace dxvk;

  DLLEXPORT HRESULT __stdcall D3D10CoreCreateDevice(
          IDXGIFactory*           pFactory,
          IDXGIAdapter*           pAdapter,
          UINT                    Flags,
          D3D_FEATURE_LEVEL       FeatureLevel,
          ID3D10Device**          ppDevice) {
    return D3D10CoreCreateDevice_Internal(pFactory, pAdapter, Flags, FeatureLevel, ppDevice);
  }

}
