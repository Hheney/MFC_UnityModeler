#pragma once

#include <fstream>
#include "Vector3.h"

struct Vertex3
{
	Vector3 pt1;
	Vector3 pt2;
	Vector3 pt3;
};

typedef Vertex3* PVertex3;

/* 사용 예시
ObjFile objFile;
objFile.LoadObj(_T("./gnd.obj"));
const PVertex3 ptr = objFile.GetArPtr(); // ptr 배열 원소가 삼각형의 3점
*/

class ObjFile
{
public:
	ObjFile(void);
	~ObjFile();

	const PVertex3 GetVtx3Ptr(void) const { return m_pVtx3; }
	int GetVtx3Size(void) const { return m_nVtx3; }
	void GetSizeObj(int& nVertex, int& nLine, int& nFace,
		const CString& sPathFile);
	void LoadObj(const CString& sPathFile);
	void PrintVtx3Msg(void) const;

protected:
	Vertex3* m_pVtx3;
	int m_nVtx3;

	void QuitVtx3Ptr(void);
	void StmEatWhite(std::wistream& stream);
	void StmEatLine(std::wistream& stream);
};

