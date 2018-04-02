
// 0402_MFC_sooDoc.cpp : CMy0402_MFC_sooDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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


// CMy0402_MFC_sooDoc ����/�Ҹ�

CMy0402_MFC_sooDoc::CMy0402_MFC_sooDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	m_BrushColor = RGB(255,0,0);

}

CMy0402_MFC_sooDoc::~CMy0402_MFC_sooDoc()
{
}

BOOL CMy0402_MFC_sooDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.
	m_ShapeList.clear();

	//�θ𿡼� �̹� OnDraw�� ȣ��ǰ��ִ�.
	//�׷��� invalidate�� �� �ʿ䰡 ����.

	return TRUE;
}




// CMy0402_MFC_sooDoc serialization

void CMy0402_MFC_sooDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
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
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
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

// ����� �׸��� �����մϴ�.
void CMy0402_MFC_sooDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void CMy0402_MFC_sooDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CMy0402_MFC_sooDoc ����

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


// CMy0402_MFC_sooDoc ���


void CMy0402_MFC_sooDoc::OnAfxIdcColorBlue()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CMy0402_MFC_sooDoc::OnColorRed()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_BrushColor = RGB(255,0,0);
	POSITION p = GetFirstViewPosition();
	CView *pview = GetNextView(p);
	pview->Invalidate();
}


void CMy0402_MFC_sooDoc::OnColorBlue()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_BrushColor = RGB(0, 0, 255);
	POSITION p = GetFirstViewPosition();
	CView *pview = GetNextView(p);
	pview->Invalidate();
}


void CMy0402_MFC_sooDoc::OnColorGreen()
{
	
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_BrushColor = RGB(0, 255, 0);
	POSITION p = GetFirstViewPosition();
	CView *pview = GetNextView(p);
	pview->Invalidate();
}


void CMy0402_MFC_sooDoc::OnColorJjj()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

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
