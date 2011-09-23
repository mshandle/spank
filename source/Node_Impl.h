/*!
 * \file Node_Impl.h
 * \date 7-28-2011 17:46:40
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __NODE_IMPL_H__
#define __NODE_IMPL_H__

#include <INode.h>
#include <vector>

class Node_Impl : public INode
{
public:
	typedef std::vector<INode*> TV_NODE;
	typedef std::vector<IObject*> TV_OBJECT;

public:
	DECLARE_RTTI(Node_Impl, INode);

	Node_Impl();
	virtual ~Node_Impl();

	virtual INode* CreateChildNode();
	virtual bool RemoveChildNode(INode* pNode);
	virtual INode* GetChildNode(int nIndex);
	virtual int GetNumChildNodes();
	virtual INode* GetParentNode();

	virtual bool AttachObject(IObject* pObject);
	virtual bool DettachObject(IObject* pObject);
	virtual IObject* GetAttachedObject(int nIndex);
	virtual int GetNumAttachedObjects();

	virtual void SetPosition(const Vector3& vPos);
	virtual void SetPosition(float x, float y, float z);
	virtual const Vector3& GetPosition();

	virtual void SetRotation(const Quaternion& qRot);
	virtual void SetRotation(const Vector3& vNormal, float fRadian);
	virtual const Quaternion& GetRotation();

	virtual void SetScale(const Vector3& vScale);
	virtual void SetScale(float x, float y, float z);
	virtual const Vector3& GetScale();

	virtual void RunAction(IActionBase* pAction);

	virtual const Matrix4x4& GetLocalMatrix();
	virtual const Matrix4x4& GetFinalMatrix();

	virtual void UpdateMatrix(float dt, bool bForceUpdate = false);
	virtual void UpdateAction(float dt);
	virtual void UpdateObjects(float dt);
	virtual void RenderObjects();

private:
	void FreeChildNodes();
	void ClearAttachedObjects();

	bool IsObjectExist(IObject* pObject);

	bool OnActionUpdate(IMsgBase* pMsg);

private:
	INode* m_pParentNode;
	TV_NODE m_vChildNodes;
	TV_OBJECT m_vAttachedObjects;

	Vector3 m_vPosition;
	Quaternion m_qRotation;
	Vector3 m_vScale;

	IActionBase* m_pAction;

	Matrix4x4 m_matLocal;
	Matrix4x4 m_matFinal;
	bool m_bNeedUpdateMatrix;

};
#endif // __NODE_IMPL_H__
