/*!
 * \file Core_Impl.h
 * \date 7-25-2011 10:11:02
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __CORE_IMPL_H__
#define __CORE_IMPL_H__

#include <ICore.h>

class Core_Impl : public ICore
{
public:
	DECLARE_RTTI(Core_Impl, ICore);

	Core_Impl();
	virtual ~Core_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual bool SetCurrentView(IViewNormal* pView);
	virtual IViewNormal* GetCurrentView();

	virtual void Update(float dt);
	virtual void Render();

	virtual void End();
	virtual bool IsRunning() const;

private:
	IViewNormal* m_pCurrentView;
	bool m_bRunning;

};
#endif // __CORE_IMPL_H__
