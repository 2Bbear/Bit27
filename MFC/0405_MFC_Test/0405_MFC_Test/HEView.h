#pragma once


// HEView view

class HEView : public CHtmlEditView
{
	DECLARE_DYNCREATE(HEView)

protected:
	HEView();           // protected constructor used by dynamic creation
	virtual ~HEView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


