
// 0404_MFC_MemberManagerDoc.h : interface of the CMy0404MFCMemberManagerDoc class
//


#pragma once

class CMy0404MFCMemberManagerView;

class CMy0404MFCMemberManagerDoc : public CDocument
{
protected: // create from serialization only
	CMy0404MFCMemberManagerDoc();
	DECLARE_DYNCREATE(CMy0404MFCMemberManagerDoc)

// Attributes
public:
	//Member List
	vector<MEMBER> m_MemberList;
	//MainDlg
	CMy0404MFCMemberManagerView * m_mainDlg;
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
	virtual ~CMy0404MFCMemberManagerDoc();
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
