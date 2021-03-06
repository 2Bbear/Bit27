
// 0404_MFC_MemberManagerDoc.cpp : implementation of the CMy0404MFCMemberManagerDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "0404_MFC_MemberManager.h"
#endif

#include "0404_MFC_MemberManagerDoc.h"

#include <propkey.h>
#include"0404_MFC_MemberManagerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy0404MFCMemberManagerDoc

IMPLEMENT_DYNCREATE(CMy0404MFCMemberManagerDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy0404MFCMemberManagerDoc, CDocument)
END_MESSAGE_MAP()


// CMy0404MFCMemberManagerDoc construction/destruction

CMy0404MFCMemberManagerDoc::CMy0404MFCMemberManagerDoc()
{
	// TODO: add one-time construction code here

}

CMy0404MFCMemberManagerDoc::~CMy0404MFCMemberManagerDoc()
{
}

BOOL CMy0404MFCMemberManagerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMy0404MFCMemberManagerDoc serialization

void CMy0404MFCMemberManagerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		int size = (int)m_MemberList.size();
		ar << size;
		for (int i =0;i<(int)m_MemberList.size();i++)
		{
			ar << m_MemberList[i].name;
			ar << m_MemberList[i].phone;
			ar << m_MemberList[i].age;
			ar << m_MemberList[i].gender;
			ar << m_MemberList[i].date;
		}
	}
	else
	{
		// TODO: add loading code here
		int size;
		ar >> size;
		for (int i=0;i<size;i++)
		{
			MEMBER temp;
			ar >> temp.name;
			ar >> temp.phone;
			ar >> temp.age;
			ar >> temp.gender;
			ar >> temp.date;
			m_MemberList.push_back(temp);
		}
		//Main Dlg List control Update
		m_mainDlg->UpdateData();
		m_mainDlg->printMemberList();
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMy0404MFCMemberManagerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMy0404MFCMemberManagerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMy0404MFCMemberManagerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMy0404MFCMemberManagerDoc diagnostics

#ifdef _DEBUG
void CMy0404MFCMemberManagerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy0404MFCMemberManagerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy0404MFCMemberManagerDoc commands
