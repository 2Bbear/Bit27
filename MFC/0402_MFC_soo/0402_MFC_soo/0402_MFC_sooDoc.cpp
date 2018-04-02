
// 0402_MFC_sooDoc.cpp : CMy0402_MFC_sooDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "0402_MFC_soo.h"
#endif

#include "0402_MFC_sooDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy0402_MFC_sooDoc

IMPLEMENT_DYNCREATE(CMy0402_MFC_sooDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy0402_MFC_sooDoc, CDocument)
	ON_COMMAND(AFX_IDC_COLOR_BLUE, &CMy0402_MFC_sooDoc::OnAfxIdcColorBlue)
	ON_COMMAND(ID_COLOR_RED, &CMy0402_MFC_sooDoc::OnColorRed)
	ON_COMMAND(ID_COLOR_BLUE, &CMy0402_MFC_sooDoc::OnColorBlue)
	ON_COMMAND(ID_COLOR_GREEN, &CMy0402_MFC_sooDoc::OnColorGreen)
	ON_COMMAND(ID_COLOR_JJJ, &CMy0402_MFC_sooDoc::OnColorJjj)
END_MESSAGE_MAP()


// CMy0402_MFC_sooDoc 생성/소멸

CMy0402_MFC_sooDoc::CMy0402_MFC_sooDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	m_BrushColor = RGB(255,0,0);

}

CMy0402_MFC_sooDoc::~CMy0402_MFC_sooDoc()
{
}

BOOL CMy0402_MFC_sooDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.
	m_ShapeList.clear();

	//부모에서 이미 OnDraw가 호출되고있다.
	//그래서 invalidate를 할 필요가 없다.

	return TRUE;
}




// CMy0402_MFC_sooDoc serialization

void CMy0402_MFC_sooDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		int size = (int)m_ShapeList.size();
		ar << size;
		ar << m_BrushColor;
		for (int i = 0; i<(int)m_ShapeList.size(); i++)
		{
			CPoint pt = m_ShapeList[i];
			ar << pt.x;
			ar << pt.y;
		}
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		m_ShapeList.clear();
		int size;
		ar >> size;
		ar >> m_BrushColor;
		for (int i = 0; i<size; i++)
		{
			CPoint pt;
			ar >> pt.x;
			ar >> pt.y;
			m_ShapeList.push_back(pt);
		}
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMy0402_MFC_sooDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
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

// 검색 처리기를 지원합니다.
void CMy0402_MFC_sooDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMy0402_MFC_sooDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMy0402_MFC_sooDoc 진단

#ifdef _DEBUG
void CMy0402_MFC_sooDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy0402_MFC_sooDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy0402_MFC_sooDoc 명령


void CMy0402_MFC_sooDoc::OnAfxIdcColorBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMy0402_MFC_sooDoc::OnColorRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_BrushColor = RGB(255,0,0);
	POSITION p = GetFirstViewPosition();
	CView *pview = GetNextView(p);
	pview->Invalidate();
}


void CMy0402_MFC_sooDoc::OnColorBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_BrushColor = RGB(0, 0, 255);
	POSITION p = GetFirstViewPosition();
	CView *pview = GetNextView(p);
	pview->Invalidate();
}


void CMy0402_MFC_sooDoc::OnColorGreen()
{
	
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_BrushColor = RGB(0, 255, 0);
	POSITION p = GetFirstViewPosition();
	CView *pview = GetNextView(p);
	pview->Invalidate();
}


void CMy0402_MFC_sooDoc::OnColorJjj()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	COLORREF color = m_BrushColor;
	CColorDialog dlg(color);
	if (dlg.DoModal() == IDOK)
	{
		m_BrushColor = dlg.GetColor();
	}
	POSITION p = GetFirstViewPosition();
	CView *pview = GetNextView(p);
	pview->Invalidate();
}
