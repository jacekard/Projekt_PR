#include "GraphicsClass.hpp"


GraphicsClass::GraphicsClass()
{
    m_pDirect3D = 0;
    m_Camera = 0;
    m_Model = 0;
    m_ColorShader = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{

    bool result;


    // Create the Direct3D object.
    m_pDirect3D = new D3DClass();
    if (!m_pDirect3D)
    {
        return false;
    }

    // Initialize the Direct3D object.
    result = m_pDirect3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
    if (!result)
    {
        MessageBox(hwnd, "Could not initialize Direct3D", "Error", MB_OK);
        return false;
    }

    // Create the camera object.
    m_Camera = new CameraClass;
    if (!m_Camera)
    {
        return false;
    }

    // Set the initial position of the camera.
    m_Camera->SetPosition(0.0f, 0.0f, -screenHeight / 32.0f);

    // Create the model object.
    m_Model = new ModelClass;
    if (!m_Model)
    {
        return false;
    }

    // Initialize the model object.
    result = m_Model->Initialize(m_pDirect3D->GetDevice());
    if (!result)
    {
        MessageBox(hwnd, "Could not initialize the model object.", "Error", MB_OK);
        return false;
    }

    // Create the color shader object.
    m_ColorShader = new ColorShaderClass;
    if (!m_ColorShader)
    {
        return false;
    }

    // Initialize the color shader object.
    result = m_ColorShader->Initialize(m_pDirect3D->GetDevice(), hwnd);
    if (!result)
    {
        MessageBox(hwnd, "Could not initialize the color shader object.", "Error", MB_OK);
        return false;
    }

    return true;
}


void GraphicsClass::Shutdown()
{
    // Release the color shader object.
    if (m_ColorShader)
    {
        m_ColorShader->Shutdown();
        delete m_ColorShader;
        m_ColorShader = 0;
    }

    // Release the model object.
    if (m_Model)
    {
        m_Model->Shutdown();
        delete m_Model;
        m_Model = 0;
    }

    // Release the camera object.
    if (m_Camera)
    {
        delete m_Camera;
        m_Camera = 0;
    }

    // Release the Direct3D object.
    if (m_pDirect3D)
    {
        m_pDirect3D->Shutdown();
        delete m_pDirect3D;
        m_pDirect3D = 0;
    }

    return;
}


bool GraphicsClass::BeginFrame()
{
  //  bool result;


  //  // Render the graphics scene.
  //  result = Render();
  //  if (!result)
  //  {
  //      return false;
  //  }

    // Clear the buffers to begin the scene.
    m_pDirect3D->BeginScene(0.0f, 0.41f, 0.70f, 1.0f);
    return true;
}


bool GraphicsClass::Render(int32_t x, int32_t y)
{
    XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
    bool result;


    // Generate the view matrix based on the camera's position.
    m_Camera->Render();

    // Get the world, view, and projection matrices from the camera and d3d objects.
    m_Camera->GetViewMatrix(viewMatrix);
    m_pDirect3D->GetProjectionMatrix(projectionMatrix);

    // Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
    m_Model->Render(m_pDirect3D->GetDeviceContext());

    // Render the model using the color shader.
    worldMatrix = XMMatrixTranslation(x, y, 0.0);
    result = m_ColorShader->Render(m_pDirect3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
    if (!result)
    {
        return false;
    }


    return true;
}

void GraphicsClass::EndFrame()
{

    // Present the rendered scene to the screen.
    m_pDirect3D->EndScene();
}
