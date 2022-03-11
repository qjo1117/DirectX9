#pragma once


#include "CWindow.h"


class CApp :
    public CWindow
{

protected:
	virtual bool	Begin() override;
	virtual bool	Update() override;
	virtual bool	Render() override;
	virtual bool	End() override;


private:
	shared_ptr<class Device> m_pDevice;
};

