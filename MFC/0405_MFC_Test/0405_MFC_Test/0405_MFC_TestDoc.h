
// 0405_MFC_TestDoc.h : interface of the CMy0405MFCTestDoc class
//


#pragma once


class CMy0405MFCTestDoc : public CDocument
{
protected: // create from serialization only
	CMy0405MFCTestDoc();
	DECLARE_DYNCREATE(CMy0405MFCTestDoc)

// Attributes
public:
	vector<CPoint>m_pointlist;
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMy0405MFCTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
