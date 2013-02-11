// cdib.h
// new version for WIN32

class CDib : public CObject
{
   enum Alloc
   {
      noAlloc,
      crtAlloc
   }
   ; // applies to BITMAPINFOHEADER

   DECLARE_SERIAL(CDib)

public:
   LPVOID  m_lpvColorTable;
   HBITMAP m_hBitmap;
   LPBYTE  m_lpImage;  // starting address of DIB bits
   LPBITMAPINFOHEADER m_lpBMIH; // buffer containing the BITMAPINFOHEADER
   LPBITMAPINFOHEADER m_lpBMIH2; // buffer containing the BITMAPINFOHEADER
   RGBQUAD rgbTransparent;
   RGBQUAD rgbWhite;
   RGBQUAD rgbBlack;

private:
   HGLOBAL m_hGlobal; // for external windows we need to free
   // could be allocated by this class or
   //  allocated externally
   Alloc m_nBmihAlloc;
   Alloc m_nImageAlloc;
   DWORD m_dwSizeImage; // of bits -- not BITMAPINFOHEADER
   //  or BITMAPFILEHEADER
   int m_nColorTableEntries;

   HANDLE m_hFile;
   HANDLE m_hMap;
   LPVOID m_lpvFile;
   HPALETTE m_hPalette;

public:
   CDib();
   CDib(CSize size, int nBitCount);  // builds BITMAPINFOHEADER
   ~CDib();
   int GetSizeImage()
   {
      return m_dwSizeImage;
   }
   int GetSizeHeader()
   {
      return sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorTableEntries;
   }
   CSize GetDimensions();
   int GetPixelIndex(int x, int y);
   BOOL SetPixelIndex(int x, int y, int iPixel, BOOL bSkip);
   BOOL Draw(CDC* pDC, CPoint origin); // until we implement CreateDibSection
   BOOL DrawPartial(CDC* pDC, CPoint dest, CPoint source, CSize size); // until we implement CreateDibSection
   BOOL DrawTransparent(CDC* pDC, CPoint origin, CSize size); // until we implement CreateDibSection
   HBITMAP CreateSection(CDC* pDC = NULL);
   UINT UsePalette(CDC* pDC, BOOL bBackground = FALSE);
   BOOL MakePalette();
   BOOL SetSystemPalette(CDC* pDC);
   BOOL Compress(CDC* pDC, BOOL bCompress = TRUE); // FALSE means decompress
   BOOL DdbToDib(CDC* pDC, HBITMAP hBitamp);
   HBITMAP CreateBitmap(CDC* pDC);
   BOOL Read(CFile* pFile);
   BOOL Write(CFile* pFile);
   void Serialize(CArchive& ar);
   void Empty();
   BOOL IsEmpty();

private:
   void ComputePaletteSize(int nBitCount);
   void ComputeMetrics();
}
;
