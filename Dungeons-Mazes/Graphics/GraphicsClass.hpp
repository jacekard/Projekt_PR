////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#include "Config.hpp"
#include "GraphicsConf.hpp"

class D3DClass;
class CameraClass;
class ModelClass;
class ColorShaderClass;

////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
    __declspec(dllexport) GraphicsClass();
    __declspec(dllexport) GraphicsClass(const GraphicsClass&);
    __declspec(dllexport) ~GraphicsClass();

    __declspec(dllexport) bool Initialize(int, int, HWND);
    __declspec(dllexport) void Shutdown();
    __declspec(dllexport) bool BeginFrame();
    __declspec(dllexport) void EndFrame();
    __declspec(dllexport) bool Render(int32_t x, int32_t y);

private:

    D3DClass* m_pDirect3D;
    CameraClass* m_Camera;
    ModelClass* m_Model;
    ColorShaderClass* m_ColorShader;

};

#endif