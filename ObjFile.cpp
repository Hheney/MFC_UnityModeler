#include "pch.h"
#include "ObjFile.h"

ObjFile::ObjFile(void)
{
	m_pVtx3 = nullptr;
	m_nVtx3 = 0;
}

ObjFile::~ObjFile()
{
	QuitVtx3Ptr();
}

void ObjFile::GetSizeObj(int& nVertex, int& nLine, int& nFace, const CString& sPathFile)
{
	using namespace std;
	nVertex = nLine = nFace = 0;
	wifstream file(sPathFile, ios::_Nocreate);
	while (1)
	{
		StmEatWhite(file);
		if (file.eof())	break;
		TCHAR ch = file.get();
		if (ch == 'v' || ch == 'V')	nVertex++;
		else if (ch == 'l' || ch == 'L')	nLine++;
		else if (ch == 'f' || ch == 'F')	nFace++;
		else StmEatLine(file);	// unknown format
	}
}

void ObjFile::LoadObj(const CString& sPathFile)
{
	using namespace std;
	int nMaxVtx, nMaxLine, nMaxFace;
	GetSizeObj(nMaxVtx, nMaxLine, nMaxFace, sPathFile);

	if (nMaxVtx == 0 || nMaxFace == 0)
	{
		QuitVtx3Ptr();
		return;
	}

	Vector3* pVtx = nullptr;
	Point2* pLine = nullptr;
	Point3* pFace = nullptr;

	if (nMaxVtx) pVtx = new Vector3[nMaxVtx];
	if (nMaxLine) pLine = new Point2[nMaxLine];
	if (nMaxFace) pFace = new Point3[nMaxFace];

	LONG64 nVtx, nLine, nFace;
	nVtx = nLine = nFace = 0;
	wifstream file(sPathFile, ios::_Nocreate);
	while (1)
	{
		StmEatWhite(file);
		if (file.eof())	break;
		TCHAR ch = file.get();
		if (ch == 'v' || ch == 'V')	// vertex
		{
			GLfloat pos;
			file >> pos;	GLfloat x = pos;
			file >> pos;	GLfloat y = pos;
			file >> pos;	GLfloat z = pos;
			pVtx[nVtx] = Vector3(x, y, z);
			nVtx++;
		}
		else if (ch == 'l' || ch == 'L')	// line
		{
			int nNode;
			file >> nNode;	int x = nNode;
			file >> nNode;	int y = nNode;
			pLine[nLine] = Point2(x, y);
			nLine++;
		}
		else if (ch == 'f' || ch == 'F')	// face
		{
			int nNode;
			file >> nNode;	int x = nNode;
			file >> nNode;	int y = nNode;
			file >> nNode;	int z = nNode;
			pFace[nFace] = Point3(x, y, z);
			nFace++;
		}
		else	StmEatLine(file);	// unknown format
	}

	if (m_pVtx3) delete[] m_pVtx3;
	m_pVtx3 = new Vertex3[nMaxFace];
	m_nVtx3 = nMaxFace;
	for (int i = 0; i < nMaxFace; i++)
	{
		Vertex3 vtx3;
		Point3 node = pFace[i];
		vtx3.pt1 = pVtx[node.x - 1];
		vtx3.pt2 = pVtx[node.y - 1];
		vtx3.pt3 = pVtx[node.z - 1];
		m_pVtx3[i] = vtx3;
	}

	if (pVtx) delete[] pVtx;
	if (pLine) delete[] pLine;
	if (pFace) delete[] pFace;
}

void ObjFile::PrintVtx3Msg(void) const
{
	CString sMsg;
	const PVertex3 ptr = GetVtx3Ptr();
	for (int i = 0; i < GetVtx3Size(); i++)
	{
		CString str;
		Vertex3 vtx3 = ptr[i];
		str.Format(_T("[%d face]\n"), i);
		sMsg += str;
		str.Format(_T("pt1: (%g, %g, %g)\n"), vtx3.pt1.x, vtx3.pt1.y, vtx3.pt1.z);
		sMsg += str;
		str.Format(_T("pt2: (%g, %g, %g)\n"), vtx3.pt2.x, vtx3.pt2.y, vtx3.pt2.z);
		sMsg += str;
		str.Format(_T("pt1: (%g, %g, %g)\n"), vtx3.pt3.x, vtx3.pt3.y, vtx3.pt3.z);
		sMsg += str;
	}
	AfxMessageBox(sMsg);
}

void ObjFile::QuitVtx3Ptr(void)
{
	if (m_pVtx3)
	{
		delete[] m_pVtx3;
		m_pVtx3 = nullptr;
		m_nVtx3 = 0;
	}
}

void ObjFile::StmEatWhite(std::wistream& stream)
{
	TCHAR ch;
	while ((ch = stream.peek()) != (TCHAR)EOF && (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')) stream.ignore();
}

void ObjFile::StmEatLine(std::wistream& stream)
{
	while (1)
	{
		if (stream.eof())	break;
		TCHAR ch = stream.get();
		if (ch == '\n') break;
		else if (ch == '\r')
		{
			if (stream.peek() == '\n') stream.ignore();
			break;
		}
	}
}
