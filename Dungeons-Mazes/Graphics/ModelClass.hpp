#pragma once
#include "TextureClass.hpp"
#include "GraphicsConf.hpp"

class ModelClass
{
private:
    
    struct VertexType
    {
        XMFLOAT3 position;
        XMFLOAT2 texture;
    };

public:
    ModelClass();
    ModelClass(const ModelClass&);
    ~ModelClass();

    bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*);
    void Shutdown();

    int GetIndexCount();

    ID3D11ShaderResourceView* GetTexture();
    void RenderBuffers(ID3D11DeviceContext*, float, float, float, float);


private:
    bool InitializeBuffers(ID3D11Device*);
    void ShutdownBuffers();
    
    bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
    void ReleaseTexture();
private:
    ID3D11Buffer * m_vertexBuffer, *m_indexBuffer;
    int m_vertexCount, m_indexCount;

    TextureClass* m_Texture;
};