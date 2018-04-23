#include "ModelClass.hpp"

ModelClass::ModelClass()
{
    m_vertexBuffer = 0;
    m_indexBuffer = 0;
    m_Texture = 0;
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}

bool ModelClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* textureFilename)
{
    bool result;


    // Initialize the vertex and index buffers.
    result = InitializeBuffers(device);
    if (!result)
    {
        return false;
    }

    // Load the texture for this model.
    result = LoadTexture(device, deviceContext, textureFilename);
    if (!result)
    {
        return false;
    }

    return true;
}

void ModelClass::Shutdown()
{
    // Release the model texture.
    ReleaseTexture();
    
    // Shutdown the vertex and index buffers.
    ShutdownBuffers();

    return;
}

int ModelClass::GetIndexCount()
{
    return m_indexCount;
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
    return m_Texture->GetTexture();
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
    VertexType* vertices;
    unsigned long* indices;
    D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
    HRESULT result;
 
    // Set the number of vertices in the vertex array.
    m_vertexCount = 4;

    // Set the number of indices in the index array.
    m_indexCount = 6;

    // Create the vertex array.
    vertices = new VertexType[m_vertexCount];
    if (!vertices)
    {
        return false;
    }

    // Create the index array.
    indices = new unsigned long[m_indexCount];
    if (!indices)
    {
        return false;
    }

    // Load the vertex array with data.
    vertices[0].position = XMFLOAT3(-0.5f, -0.5f, 0.0f);  // Bottom left.
    vertices[0].texture = XMFLOAT2(0.5f, 0.5f);

    vertices[1].position = XMFLOAT3(0.5f, 0.5f, 0.0f);  // Top right.
    vertices[1].texture = XMFLOAT2(1.0f, 0.0f);

    vertices[2].position = XMFLOAT3(0.5f, -0.5f, 0.0f);  // top left.
    vertices[2].texture = XMFLOAT2(0.5f, 0.0f);

    vertices[3].position = XMFLOAT3(-0.5f, 0.5f, 0.0f);  // botom right.
    vertices[3].texture = XMFLOAT2(1.0f, 0.5f);

    // Load the index array with data.
    indices[0] = 0;  // Bottom left.
    indices[1] = 1;  // Top middle.
    indices[2] = 2;  // Bottom right.
    indices[3] = 3;
    indices[4] = 1;
    indices[5] = 0;
                     
    // Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
    vertexData.SysMemPitch = 0;
    vertexData.SysMemSlicePitch = 0;

    // Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
    if (FAILED(result))
    {
        return false;
    }

    // Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
    indexBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
    indexData.SysMemPitch = 0;
    indexData.SysMemSlicePitch = 0;

    // Create the index buffer.
    result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
    if (FAILED(result))
    {
        return false;
    }

    // Release the arrays now that the vertex and index buffers have been created and loaded.
    delete[] vertices;
    vertices = 0;

    delete[] indices;
    indices = 0;

    return true;
}

void ModelClass::ShutdownBuffers()
{
    // Release the index buffer.
    if (m_indexBuffer)
    {
        m_indexBuffer->Release();
        m_indexBuffer = 0;
    }

    // Release the vertex buffer.
    if (m_vertexBuffer)
    {
        m_vertexBuffer->Release();
        m_vertexBuffer = 0;
    }

    return;
}

void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext, float x_start, float x_end, float y_start, float y_end)
{
    unsigned int stride;
    unsigned int offset;
    static D3D11_MAPPED_SUBRESOURCE resource;
    static VertexType* vertices = new VertexType[m_vertexCount];

    vertices[0].position = XMFLOAT3(-0.5f, -0.5f, 0.0f);  // Bottom left.
    vertices[0].texture = XMFLOAT2( x_start, y_end);

    vertices[1].position = XMFLOAT3(0.5f, 0.5f, 0.0f);  // bottom right.
    vertices[1].texture = XMFLOAT2(x_end, y_start);

    vertices[2].position = XMFLOAT3(0.5f, -0.5f, 0.0f);  // top left.
    vertices[2].texture = XMFLOAT2(x_end, y_end);

    vertices[3].position = XMFLOAT3(-0.5f, 0.5f, 0.0f);  // top right.
    vertices[3].texture = XMFLOAT2(x_start, y_start);
    deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
    memcpy(resource.pData, &vertices[0], sizeof(VertexType) * m_vertexCount);
    deviceContext->Unmap(m_vertexBuffer, 0);
    
    // Set vertex buffer stride and offset.
    stride = sizeof(VertexType);
    offset = 0;

    // Set the vertex buffer to active in the input assembler so it can be rendered.
    deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
    deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    return;
}

bool ModelClass::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename)
{
	bool result;


	// Create the texture object.
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, deviceContext, filename);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::ReleaseTexture()
{
	// Release the texture object.
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}