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
		General::SPtr<CMesh> mesh;

		//Triangle
		std::vector<t_VertexData> vertices;
		vertices.push_back(t_VertexData{ Vec3(0.0f, 0.5f, 0.5f), Vec4(1.0f, 1.0f, 0.0f, 1.0f), Vec2(0.f, 0.f) });
		vertices.push_back(t_VertexData{ Vec3(0.5f, -0.5f, 0.5f), Vec4(1.0f,1.0f,0.0f,1.0f), Vec2(0.f, 0.f) });
		vertices.push_back(t_VertexData{ Vec3(-0.5f, -0.5f, 0.5f), Vec4(1.0f,1.0f,0.0f,1.0f), Vec2(0.f, 0.f) });

		const int indexCnt = 3;
		int indexs[indexCnt] =
		{
			0,1,2
		};

		mesh = new CMesh(true);
		mesh->Create(vertices.data(), vertices.size(), indexs, indexCnt);
		AddRes<CMesh>(TEXT("TriangleMesh"), mesh);
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