#include "pch.h"
#include "ResourceManager.h"
#include "Mesh.h"
#include "CGraphicsShader.h"
namespace Renderer
{
	CResourceManager::CResourceManager()
	{
		//ResourceMap.InnerClear 하지말것.
	}
	CResourceManager::~CResourceManager()
	{

	}
	void CResourceManager::Initialize()
	{
		InitMesh();
		InitShader();
	}
	void CResourceManager::Release()
	{
		int TypeCnt = TYPETOINT(EResourceType::MAX);

		for (int i = 0; i < TypeCnt; ++i)
		{
			mResourceMap[i].clear();
		}
	}
	template<> General::SPtr<CMesh> CResourceManager::FindRes(const TCHAR* _resName)
	{
		EResourceType eType = EResourceType::Mesh;
		General::SPtr<General::CResource> Resource = mResourceMap[TYPETOINT(EResourceType::Mesh)][_resName];
		return (CMesh*)Resource.get();
	}
	template<> General::SPtr<CGraphicsShader> CResourceManager::FindRes(const TCHAR* _resName)
	{
		EResourceType eType = EResourceType::GraphicsShader;
		General::SPtr<General::CResource> Resource = mResourceMap[TYPETOINT(EResourceType::GraphicsShader)][_resName];
		return (CGraphicsShader*)Resource.get();
	}
	template<> void CResourceManager::AddRes(const TCHAR* _resName, General::SPtr<CMesh> _Resource)
	{
		EResourceType eType = EResourceType::Mesh;
		General::SPtr<CMesh> Resource = FindRes<CMesh>(_resName);
		if (Resource.get() != nullptr)
			Assert(nullptr, TEXT("ResourceManager AddRes Error! Resource Key 중복"));

		mResourceMap[TYPETOINT(eType)].insert(std::make_pair(_resName, _Resource.get()));
	}
	template<> void CResourceManager::AddRes(const TCHAR* _resName, General::SPtr<CGraphicsShader> _Resource)
	{
		EResourceType eType = EResourceType::GraphicsShader;
		General::SPtr<CGraphicsShader> Resource = FindRes<CGraphicsShader>(_resName);
		if (Resource.get() != nullptr)
			Assert(nullptr, TEXT("ResourceManager AddRes Error! Resource Key 중복"));

		mResourceMap[TYPETOINT(eType)].insert(std::make_pair(_resName, _Resource.get()));
	}
	void CResourceManager::InitMesh()
	{
		General::SPtr<CMesh> pMesh;

		//Triangle
		std::vector<t_VertexData> vertices;
		vertices.push_back(t_VertexData{ Vec3(0.0f, 0.5f, 0.5f), Vec4(1.0f, 1.0f, 0.0f, 1.0f), Vec2(0.f, 0.f) });
		vertices.push_back(t_VertexData{ Vec3(0.5f, -0.5f, 0.5f), Vec4(1.0f,1.0f,0.0f,1.0f), Vec2(0.f, 0.f) });
		vertices.push_back(t_VertexData{ Vec3(-0.5f, -0.5f, 0.5f), Vec4(1.0f,1.0f,0.0f,1.0f), Vec2(0.f, 0.f) });

		std::vector<UINT> indices;
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		pMesh = new CMesh(true);
		pMesh->Create(vertices.data(), vertices.size(), indices.data(), indices.size());
		AddRes<CMesh>(TEXT("TriangleMesh"), pMesh);


		vertices.clear();
		indices.clear();

		vertices.push_back(t_VertexData{ Vec3(-0.5f, 0.5f, 0.5f), Vec4(1.0f, 1.0f, 0.0f, 1.0f), Vec2(0.f, 0.f) });
		vertices.push_back(t_VertexData{ Vec3(0.5f, 0.5f, 0.5f), Vec4(1.0f,1.0f,0.0f,1.0f), Vec2(0.f, 0.f) });
		vertices.push_back(t_VertexData{ Vec3(0.5f, -0.5f, 0.5f), Vec4(1.0f,1.0f,0.0f,1.0f), Vec2(0.f, 0.f) });
		vertices.push_back(t_VertexData{ Vec3(-0.5f, -0.5f, 0.5f), Vec4(1.0f,1.0f,0.0f,1.0f), Vec2(0.f, 0.f) });
	    
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
		
		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);

		pMesh = new CMesh(true);
		pMesh->Create(vertices.data(), vertices.size(), indices.data(), indices.size());
		AddRes<CMesh>(TEXT("RectMesh"), pMesh);


		vertices.clear();
		indices.clear();

		float fRadius = 0.5f;
		UINT Slice = 40;
		float fTheta = XM_2PI / (float)Slice;
		
		vertices.push_back(t_VertexData{ Vec3(0.f, 0.f, 0.f), Vec4(1.f, 1.f, 1.f, 1.f), Vec2(0.5f, 0.5f) });

		for (UINT i = 0; i < Slice; ++i)
		{
			Vec3 pos = Vec3(fRadius * cosf(fTheta * (float)i), fRadius * sinf(fTheta * (float)i), 0.f);
			Vec2 uv = Vec2(pos.x + 0.5f, -pos.y + 0.5f);
			vertices.push_back(t_VertexData{ pos, Vec4(1.f, 1.f, 1.f, 1.f), uv });
		}

		for (UINT i = 0; i < Slice - 1; ++i)
		{
			indices.push_back(0);
			indices.push_back(i + 2);
			indices.push_back(i + 1);
		}

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(Slice);

		pMesh = new CMesh(true);
		pMesh->Create(vertices.data(), vertices.size(), indices.data(), indices.size());
		AddRes<CMesh>(TEXT("CircleMesh"), pMesh);
	}
	void CResourceManager::InitShader()
	{
		CGraphicsShader* shader;
		shader = new CGraphicsShader();
		shader->CreateVertexShader(TEXT("//std3D.fx"), "VS_Main", "vs_5_0");
		shader->CreatePixelShader(TEXT("//std3D.fx"), "PS_Main", "ps_5_0");
		AddRes<CGraphicsShader>(TEXT("DefaultShader"), shader);
	}
}