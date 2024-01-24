#pragma once
#include "Component.h"
namespace RKEngine
{
	class CTransform :
		public CComponent
	{
	private:
		Vec3 m_v3RelativePos;
		Vec3 m_v3RelativeScale;
		Vec3 m_v3RelativeRot;

		Vec3 m_v3RelativeDir;
		Vec3 m_v3WorldDir;

		Matrix m_matWorldPos;
		Matrix m_matWorldScale;
		Matrix m_matWorldRot;

		Matrix m_matWorld;
		Matrix m_matWorldInv;
	public:
		CTransform();
		CTransform(const CTransform& _ref);
		virtual ~CTransform();
	public:
		virtual void Start()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
	public:
		virtual void SaveToSceneMetaFile()override;
		virtual void LoadToSceneMetaFile()override;
	public:
		CLASS_COPY(CTransform)
	};
}


