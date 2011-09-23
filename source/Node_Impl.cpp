/*!
 * \file Node_Impl.cpp
 * \date 7-28-2011 17:46:47
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Node_Impl.h"
#include <IRenderableObject.h>
#include <msg/MsgID.h>
#include <msg/MsgActionUpdate.h>

Node_Impl::Node_Impl()
{
	m_pParentNode = NULL;
	m_vPosition = IMath::VEC3_ZERO;
	m_qRotation = IMath::ROT_ZERO;
	m_vScale = IMath::VEC3_ONE;

	m_pAction = NULL;

	m_matLocal = IMath::MAT4X4_IDENTITY;
	m_matFinal = IMath::MAT4X4_IDENTITY;
	m_bNeedUpdateMatrix = true;
}

Node_Impl::~Node_Impl()
{
	SAFE_RELEASE(m_pAction);
	FreeChildNodes();
	ClearAttachedObjects();
}

INode* Node_Impl::CreateChildNode()
{
	Node_Impl* pNode = new Node_Impl();
	pNode->m_pParentNode = this;
	m_vChildNodes.push_back(pNode);
	return pNode;
}

bool Node_Impl::RemoveChildNode(INode* pNode)
{
	for (TV_NODE::iterator it = m_vChildNodes.begin(); it != m_vChildNodes.end(); ++it)
	{
		if (pNode == (*it))
		{
			m_vChildNodes.erase(it);
			SAFE_DELETE(pNode);
			return true;
		}
	}

	return false;
}

INode* Node_Impl::GetChildNode(int nIndex)
{
	if (nIndex < 0 || nIndex >= (int)m_vChildNodes.size()) return NULL;
	return m_vChildNodes[nIndex];
}

int Node_Impl::GetNumChildNodes()
{
	return (int)m_vChildNodes.size();
}

INode* Node_Impl::GetParentNode()
{
	return m_pParentNode;
}

bool Node_Impl::AttachObject(IObject* pObject)
{
	// check pObject exist
	if (IsObjectExist(pObject)) return false;

	pObject->SetParent(this);
	m_vAttachedObjects.push_back(pObject);
	return true;
}

bool Node_Impl::DettachObject(IObject* pObject)
{
	for (TV_OBJECT::iterator it = m_vAttachedObjects.begin(); it != m_vAttachedObjects.end(); ++it)
	{
		if (pObject == (*it))
		{
			m_vAttachedObjects.erase(it);
			pObject->SetParent(NULL);
			return true;
		}
	}

	return false;
}

IObject* Node_Impl::GetAttachedObject(int nIndex)
{
	if (nIndex < 0 || nIndex >= (int)m_vAttachedObjects.size()) return NULL;
	return m_vAttachedObjects[nIndex];
}

int Node_Impl::GetNumAttachedObjects()
{
	return (int)m_vAttachedObjects.size();
}

void Node_Impl::SetPosition(const Vector3& vPos)
{
	m_vPosition = vPos;
	m_bNeedUpdateMatrix = true;
}

void Node_Impl::SetPosition(float x, float y, float z)
{
	m_vPosition.x = x;
	m_vPosition.y = y;
	m_vPosition.z = z;
	m_bNeedUpdateMatrix = true;
}

const Vector3& Node_Impl::GetPosition()
{
	return m_vPosition;
}

void Node_Impl::SetRotation(const Quaternion& qRot)
{
	m_qRotation = qRot;
	m_bNeedUpdateMatrix = true;
}

void Node_Impl::SetRotation(const Vector3& vNormal, float fRadian)
{
	m_qRotation = Quaternion(vNormal, fRadian);
	m_bNeedUpdateMatrix = true;
}

const Quaternion& Node_Impl::GetRotation()
{
	return m_qRotation;
}

void Node_Impl::SetScale(const Vector3& vScale)
{
	m_vScale = vScale;
	m_bNeedUpdateMatrix = true;
}

void Node_Impl::SetScale(float x, float y, float z)
{
	m_vScale.x = x;
	m_vScale.y = y;
	m_vScale.z = z;
	m_bNeedUpdateMatrix = true;
}

const Vector3& Node_Impl::GetScale()
{
	return m_vScale;
}

void Node_Impl::RunAction(IActionBase* pAction)
{
	SAFE_RELEASE(m_pAction);

	m_pAction = pAction;

	if (m_pAction)
	{
		m_pAction->ConnectEvent(MI_ACTION_UPDATE, this, (MSG_CALLBACK)&Node_Impl::OnActionUpdate);
		m_pAction->Start();
	}
}

const Matrix4x4& Node_Impl::GetLocalMatrix()
{
	return m_matLocal;
}

const Matrix4x4& Node_Impl::GetFinalMatrix()
{
	return m_matFinal;
}

void Node_Impl::UpdateMatrix(float dt, bool bForceUpdate /* = false */)
{
	if (m_bNeedUpdateMatrix || bForceUpdate)
	{
		m_bNeedUpdateMatrix = false;

		// setup local matrix
		Matrix4x4 matScale;
		IMath::BuildScaleMatrix(matScale, m_vScale);

		Matrix4x4 matRot;
		IMath::BuildRotateMatrix(matRot, m_qRotation);

		m_matLocal = matRot * matScale;
		m_matLocal.SetTranslate(m_vPosition);

		// setup final matrix
		if (m_pParentNode != NULL)
		{
			m_matFinal = m_matLocal * m_pParentNode->GetFinalMatrix();
		}
		else
		{
			m_matFinal = m_matLocal;
		}

		// tell children setup their matrix
		for (TV_NODE::iterator it = m_vChildNodes.begin(); it != m_vChildNodes.end(); ++it)
		{
			INode* pNode = (*it);
			pNode->UpdateMatrix(dt, true);
		}
	}
}

void Node_Impl::UpdateAction(float dt)
{
	if (m_pAction)
	{
		m_pAction->Update(dt);
	}

	// tell children update action
	for (TV_NODE::iterator it = m_vChildNodes.begin(); it != m_vChildNodes.end(); ++it)
	{
		INode* pNode = (*it);
		pNode->UpdateAction(dt);
	}
}

void Node_Impl::UpdateObjects(float dt)
{
	for (TV_OBJECT::iterator it = m_vAttachedObjects.begin(); it != m_vAttachedObjects.end(); ++it)
	{
		IObject* pObject = (*it);
		if (pObject->GetRtti()->IsDerived(IUpdateableObject::__RttiData()))
		{
			IUpdateableObject* pUpdateableObject = (IUpdateableObject*)pObject;
			pUpdateableObject->Update(dt);
		}
	}

	for (TV_NODE::iterator it = m_vChildNodes.begin(); it != m_vChildNodes.end(); ++it)
	{
		INode* pNode = (*it);
		pNode->UpdateObjects(dt);
	}
}

void Node_Impl::RenderObjects()
{
	for (TV_OBJECT::iterator it = m_vAttachedObjects.begin(); it != m_vAttachedObjects.end(); ++it)
	{
		IObject* pObject = (*it);
		if (pObject->GetRtti()->IsDerived(IRenderableObject::__RttiData()))
		{
			IRenderableObject* pRenderableObject = (IRenderableObject*)pObject;
			pRenderableObject->Render();
		}
	}

	for (TV_NODE::iterator it = m_vChildNodes.begin(); it != m_vChildNodes.end(); ++it)
	{
		INode* pNode = (*it);
		pNode->RenderObjects();
	}
}

void Node_Impl::FreeChildNodes()
{
	for (TV_NODE::iterator it = m_vChildNodes.begin(); it != m_vChildNodes.end(); ++it)
	{
		INode* pNode = (*it);
		SAFE_DELETE(pNode);
	}

	m_vChildNodes.clear();
}

void Node_Impl::ClearAttachedObjects()
{
	m_vAttachedObjects.clear();
}

bool Node_Impl::IsObjectExist(IObject* pObject)
{
	for (TV_OBJECT::iterator it = m_vAttachedObjects.begin(); it != m_vAttachedObjects.end(); ++it)
	{
		if (pObject == (*it)) return true;
	}

	return false;
}

bool Node_Impl::OnActionUpdate(IMsgBase* pMsg)
{
	MsgActionUpdate* pMsgActionUpdate = (MsgActionUpdate*)pMsg;
	switch (pMsgActionUpdate->GetUpdateType())
	{
	case AUT_SCALE:
		{
			SetScale(pMsgActionUpdate->GetScale());
		}
		break;
	case AUT_POSITION:
		{
			SetPosition(pMsgActionUpdate->GetPosition());
		}
		break;
	case AUT_ROTATION:
		{
			SetRotation(pMsgActionUpdate->GetRotation());
		}
		break;
	case AUT_STOPED:
		{
			SAFE_RELEASE(m_pAction);
		}
		break;
	}

	return true;
}
