#include "stdafx.h"

IMPLEMENT_SERIAL(CDib, CObject, 0);

CDib::CDib()
{
   m_hFile = NULL;
   m_hBitmap = NULL;
   m_hPalette = NULL;
   m_lpBMIH = NULL;
   m_lpBMIH2 = NULL;
   m_lpImage = NULL;

   rgbTransparent.rgbRed = 128; // puke green
   rgbTransparent.rgbGreen = 128;
   rgbTransparent.rgbBlue = 0;
   rgbTransparent.rgbReserved = 0;

   rgbWhite.rgbRed = 255;
   rgbWhite.rgbGreen = 255;
   rgbWhite.rgbBlue = 255;
   rgbWhite.rgbReserved = 0;

   rgbBlack.rgbRed = 0;
   rgbBlack.rgbGreen = 0;
   rgbBlack.rgbBlue = 0;
   rgbBlack.rgbReserved = 0;

   Empty();
}

CDib::CDib(CSize size, int nBitCount)
{
   m_hFile = NULL;
   m_hBitmap = NULL;
   m_hPalette = NULL;
   m_lpBMIH = NULL;
   m_lpBMIH2 = NULL;
   m_lpImage = NULL;

   rgbTransparent.rgbRed = 128; // puke green
   rgbTransparent.rgbGreen = 128;
   rgbTransparent.rgbBlue = 0;
   rgbTransparent.rgbReserved = 0;

   rgbWhite.rgbRed = 255;
   rgbWhite.rgbGreen = 255;
   rgbWhite.rgbBlue = 255;
   rgbWhite.rgbReserved = 0;

   rgbBlack.rgbRed = 0;
   rgbBlack.rgbGreen = 0;
   rgbBlack.rgbBlue = 0;
   rgbBlack.rgbReserved = 0;

   Empty();

   ComputePaletteSize(nBitCount);
   m_lpBMIH = (LPBITMAPINFOHEADER) new char[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorTableEntries];

   m_lpBMIH->biSize = sizeof(BITMAPINFOHEADER);
   m_lpBMIH->biWidth = size.cx;
   m_lpBMIH->biHeight = size.cy;
   m_lpBMIH->biPlanes = 1;
   m_lpBMIH->biBitCount = (WORD) nBitCount;
   m_lpBMIH->biCompression = BI_RGB;
   m_lpBMIH->biSizeImage = 0;
   m_lpBMIH->biXPelsPerMeter = 0;
   m_lpBMIH->biYPelsPerMeter = 0;
   m_lpBMIH->biClrUsed = m_nColorTableEntries;
   m_lpBMIH->biClrImportant = m_nColorTableEntries;

   ComputeMetrics();

   memset(m_lpvColorTable, 0, sizeof(RGBQUAD) * m_nColorTableEntries);
}

CDib::~CDib()
{
   Empty();
}

CSize CDib::GetDimensions()
{
   if (m_lpBMIH == NULL) return CSize(0, 0);

   return CSize((int) m_lpBMIH->biWidth, (int) m_lpBMIH->biHeight);
}

UINT CDib::UsePalette(CDC* pDC, BOOL bBackground /* = FALSE */)
{
   if (m_hPalette == NULL) return 0;

   HDC hdc = pDC->GetSafeHdc();
   ::SelectPalette(hdc, m_hPalette, bBackground);

   return ::RealizePalette(hdc);
}

BOOL CDib::IsEmpty()
{
//getting "Unhandled exception at 0x00454436 in Mmlogic.exe: 0xC0000005: Access violation reading location 0xe59f98f8."
   if (m_lpBMIH == NULL) return TRUE;

   return FALSE;
}

BOOL CDib::Draw(CDC* pDC, CPoint dest)
{
   if (m_lpBMIH == NULL) return FALSE;

   //   if (m_hPalette != NULL)
   //      {
   //      ::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);
   //      }

   if (GDI_ERROR == ::StretchDIBits(pDC->GetSafeHdc(), dest.x, dest.y, m_lpBMIH->biWidth, m_lpBMIH->biHeight, 0, 0, m_lpBMIH->biWidth, m_lpBMIH->biHeight, m_lpImage, (LPBITMAPINFO) m_lpBMIH, DIB_RGB_COLORS, SRCCOPY))
   {
      return FALSE;
   }

   return TRUE;
}

BOOL CDib::DrawPartial(CDC* pDC, CPoint dest, CPoint source, CSize size)
{
   if (m_lpBMIH == NULL) return FALSE;

   if (GDI_ERROR == ::StretchDIBits(pDC->GetSafeHdc(), dest.x, dest.y, size.cx, size.cy, source.x, source.y, size.cx, size.cy, m_lpImage, (LPBITMAPINFO) m_lpBMIH, DIB_RGB_COLORS, SRCCOPY))
   {
      return FALSE;
   }

   return TRUE;
}

BOOL CDib::DrawTransparent(CDC* pDC, CPoint origin, CSize size)
{
   if (m_lpBMIH == NULL) return FALSE;

   if (m_lpBMIH2 == NULL)
   {
      m_lpBMIH2 = (LPBITMAPINFOHEADER) new char[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorTableEntries];
   }

   memcpy(m_lpBMIH2, m_lpBMIH, sizeof(BITMAPINFOHEADER));

   // backup color table and mung the orignal to build a mask

   for (int i=0;i<16;i++)
   {
      if (*(DWORD *) &((LPBITMAPINFO) m_lpBMIH)->bmiColors[i] == *(DWORD *) &rgbTransparent)
      {
         ((LPBITMAPINFO) m_lpBMIH2)->bmiColors[i] = rgbWhite;
      }
      else
      {
         ((LPBITMAPINFO) m_lpBMIH2)->bmiColors[i] = rgbBlack;
      }
   }

   // Draw Mask

   if (GDI_ERROR == ::StretchDIBits(pDC->GetSafeHdc(), origin.x, origin.y, size.cx, size.cy, 0, 0, m_lpBMIH->biWidth, m_lpBMIH->biHeight, m_lpImage, (LPBITMAPINFO) m_lpBMIH2, DIB_RGB_COLORS, SRCAND))
   {
      return FALSE;
   }

   // Now modify color table to properly overlay the image

   for (i=0;i<16;i++)
   {
      if (*(DWORD *) &((LPBITMAPINFO) m_lpBMIH2)->bmiColors[i] == *(DWORD *) &rgbWhite)
      {
         ((LPBITMAPINFO) m_lpBMIH2)->bmiColors[i] = rgbBlack;
      }
      else
      {
         ((LPBITMAPINFO) m_lpBMIH2)->bmiColors[i] = ((LPBITMAPINFO) m_lpBMIH)->bmiColors[i];
      }
   }

   // draw overlay

   if (GDI_ERROR == ::StretchDIBits(pDC->GetSafeHdc(), origin.x, origin.y, size.cx, size.cy, 0, 0, m_lpBMIH->biWidth, m_lpBMIH->biHeight, m_lpImage, (LPBITMAPINFO) m_lpBMIH2, DIB_RGB_COLORS, SRCPAINT))
   {
      return FALSE;
   }

   return TRUE;
}

HBITMAP CDib::CreateSection(CDC* pDC)
{
   if (m_lpBMIH == NULL) return NULL;
   if (m_lpImage != NULL) return NULL; // can only do this if image doesn't exist

   m_hBitmap = ::CreateDIBSection(pDC->GetSafeHdc(), (LPBITMAPINFO) m_lpBMIH, DIB_RGB_COLORS, (LPVOID*) &m_lpImage, NULL, 0);

   ASSERT(m_lpImage != NULL);

   return m_hBitmap;
}

BOOL CDib::MakePalette()
{
   // makes a logical palette (m_hPalette) from the DIB's color table
   // this palette will be selected and realized prior to drawing the DIB
   if(m_nColorTableEntries == 0) return FALSE;

   if(m_hPalette != NULL)
   {
      ::DeleteObject(m_hPalette);
      m_hPalette = NULL;
   }
   //   TRACE("CDib::MakePalette -- m_nColorTableEntries = %d\n", m_nColorTableEntries);
   LPLOGPALETTE pLogPal = (LPLOGPALETTE) new char[2 * sizeof(WORD) + m_nColorTableEntries * sizeof(PALETTEENTRY)];
   pLogPal->palVersion = 0x300;
   pLogPal->palNumEntries = (WORD) m_nColorTableEntries;
   LPRGBQUAD pDibQuad = (LPRGBQUAD) m_lpvColorTable;

   for(int i = 0; i < m_nColorTableEntries; i++)
   {
      pLogPal->palPalEntry[i].peRed = pDibQuad->rgbRed;
      pLogPal->palPalEntry[i].peGreen = pDibQuad->rgbGreen;
      pLogPal->palPalEntry[i].peBlue = pDibQuad->rgbBlue;
      pLogPal->palPalEntry[i].peFlags = 0;
      pDibQuad++;
   }

   m_hPalette = ::CreatePalette(pLogPal);
   delete pLogPal;

   return TRUE;
}

BOOL CDib::SetSystemPalette(CDC* pDC)
{
   // if the DIB doesn't have a color table, we can use the system palette
   if(m_nColorTableEntries != 0) return FALSE;

   // not sure if this is needed
   if(m_hPalette != NULL)
   {
      ::DeleteObject(m_hPalette);
      m_hPalette = NULL;
   }

   HDC hDC = pDC->GetSafeHdc();
   if(!(::GetDeviceCaps(hDC, RASTERCAPS) & RC_PALETTE)) return FALSE;

   int nSysColors = ::GetDeviceCaps(hDC, NUMCOLORS);
   int nPalEntries = ::GetDeviceCaps(hDC, SIZEPALETTE);

   ASSERT(nPalEntries <= 256);

   int nEntries = (nPalEntries == 0) ? nSysColors : nPalEntries;
   LPLOGPALETTE pLogPal = (LPLOGPALETTE) new char[2 * sizeof(WORD) + nEntries * sizeof(PALETTEENTRY)];
   pLogPal->palVersion = 0x300;
   pLogPal->palNumEntries = (WORD) nEntries;
   ::GetSystemPaletteEntries(hDC, 0, nEntries, (LPPALETTEENTRY) ((LPBYTE) pLogPal + 2 * sizeof(WORD)));
   m_hPalette = ::CreatePalette(pLogPal);

   delete pLogPal;
   return TRUE;
}

HBITMAP CDib::CreateBitmap(CDC* pDC)
{
   if (m_dwSizeImage == 0) return NULL;
   HBITMAP hBitmap = ::CreateDIBitmap(pDC->GetSafeHdc(), m_lpBMIH, CBM_INIT, m_lpImage, (LPBITMAPINFO) m_lpBMIH, DIB_RGB_COLORS);

   ASSERT(hBitmap);

   return hBitmap;
}

BOOL CDib::DdbToDib(CDC* pDC, HBITMAP hBitmap /* = TRUE */)
{
   // 1. makes a new DIB from GDI bitmap
   // 2. cleans up the original DIB
   // 3. puts the new DIB in the object

   if((m_lpBMIH->biBitCount != 4) && (m_lpBMIH->biBitCount != 8)) return FALSE;

   // compression supported only for 4 bpp and 8 bpp DIBs
   //if(m_hBitmap) return FALSE; // can't compress a DIB Section!

   TRACE("Compress: original palette size = %d\n", m_nColorTableEntries);
   HDC hdc = pDC->GetSafeHdc();
   HPALETTE hOldPalette = ::SelectPalette(hdc, m_hPalette, FALSE);

   int nSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorTableEntries;
   LPBITMAPINFOHEADER lpBMIH = (LPBITMAPINFOHEADER) new char[nSize];
   memcpy(lpBMIH, m_lpBMIH, nSize);  // new header

   lpBMIH->biCompression = BI_RGB;

   // calls GetDIBits with null data pointer to get size of compressed DIB
   if(!::GetDIBits(pDC->GetSafeHdc(), hBitmap, 0, (UINT) lpBMIH->biHeight, NULL, (LPBITMAPINFO) lpBMIH, DIB_RGB_COLORS))
   {
      AfxMessageBox("Unable to compress this DIB");
      // probably a problem with the color table
      delete [] lpBMIH;
      ::SelectPalette(hdc, hOldPalette, FALSE);

      return FALSE;
   }

   if (lpBMIH->biSizeImage == 0)
   {
      AfxMessageBox("Driver can't do compression");
      delete [] lpBMIH;
      ::SelectPalette(hdc, hOldPalette, FALSE);

      return FALSE;
   }
   else
   {
      m_dwSizeImage = lpBMIH->biSizeImage;
   }

   // second GetDIBits call to make DIB
   LPBYTE lpImage = (LPBYTE) new char[m_dwSizeImage];
   VERIFY(::GetDIBits(pDC->GetSafeHdc(), hBitmap, 0, (UINT) lpBMIH->biHeight, lpImage, (LPBITMAPINFO) lpBMIH, DIB_RGB_COLORS));
   TRACE("dib successfully created - height = %d\n", lpBMIH->biHeight);

   Empty();

   m_lpBMIH = lpBMIH;
   m_lpImage = lpImage;

   ComputePaletteSize(m_lpBMIH->biBitCount);
   ComputeMetrics();
   MakePalette();
   ::SelectPalette(hdc, hOldPalette, FALSE);

   return TRUE;
}

BOOL CDib::Read(CFile* pFile)
{
   // 1. read file header to get size of info hdr + color table
   // 2. read info hdr (to get image size) and color table
   // 3. read image
   // can't use bfSize in file header
   int nCount;
   int nSize;
   BITMAPFILEHEADER bmfh;

   Empty();

   TRY
   {
      nCount = pFile->Read((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));

      if(nCount != sizeof(BITMAPFILEHEADER))
      {
         AfxMessageBox("Error reading bitmap file header");
         return FALSE;
      }

      if(bmfh.bfType != 0x4d42)
      {
         AfxMessageBox("Invalid bitmap file");
         return FALSE;
      }

      nSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
      m_lpBMIH = (LPBITMAPINFOHEADER) new char[nSize];
      nCount = pFile->Read(m_lpBMIH, nSize); // info hdr & color table
      ComputeMetrics();
      m_lpImage = (LPBYTE) new char[m_dwSizeImage];
      nCount = pFile->Read(m_lpImage, m_dwSizeImage); // image only
   }

   CATCH (CException, e)
   {
      AfxMessageBox("Error Reading Bitmap");
      return FALSE;
   }
   END_CATCH

      ComputePaletteSize(m_lpBMIH->biBitCount);
   MakePalette();

   return TRUE;
}

BOOL CDib::Write(CFile* pFile)
{
   BITMAPFILEHEADER bmfh;

   bmfh.bfType = 0x4d42;  // 'BM'
   int nSize =  sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorTableEntries +  m_dwSizeImage;
   bmfh.bfSize = nSize + sizeof(BITMAPFILEHEADER);
   // meaning of bfSize open to interpretation (bytes, words, dwords?) -- we won't use it
   bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
   bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorTableEntries;

   TRY
   {
      pFile->Write((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));
      pFile->Write((LPVOID) m_lpBMIH, nSize);
   }
   CATCH (CException, e)
   {
      AfxMessageBox("write error");
      return FALSE;
   }
   END_CATCH

      return TRUE;
}

void CDib::Serialize(CArchive& ar)
{
   ar.Flush();
   if(ar.IsStoring())
   {
      Write(ar.GetFile());
   }
   else
   {
      Read(ar.GetFile());
   }
}

// helper functions
void CDib::ComputePaletteSize(int nBitCount)
{
   if((m_lpBMIH == NULL) || (m_lpBMIH->biClrUsed == 0))
   {
      switch(nBitCount)
      {
      case 1:
         m_nColorTableEntries = 2;
         break;
      case 4:
         m_nColorTableEntries = 16;
         break;
      case 8:
         m_nColorTableEntries = 256;
         break;
      case 16:
      case 24:
      case 32:
         m_nColorTableEntries = 0;
         break;
      default:
         ASSERT(FALSE);
      }
   }
   else
   {
      m_nColorTableEntries = m_lpBMIH->biClrUsed;
   }

   ASSERT(m_nColorTableEntries <= 256);
}

void CDib::ComputeMetrics()
{
   m_dwSizeImage = m_lpBMIH->biSizeImage;

   if(m_dwSizeImage == 0)
   {
      DWORD dwBytes = ((DWORD) m_lpBMIH->biWidth * m_lpBMIH->biBitCount) / 32;
      if(((DWORD) m_lpBMIH->biWidth * m_lpBMIH->biBitCount) % 32)
      {
         dwBytes++;
      }
      dwBytes *= 4;
      m_dwSizeImage = dwBytes * m_lpBMIH->biHeight; // no compression
   }

   m_lpvColorTable = (LPBYTE) m_lpBMIH + sizeof(BITMAPINFOHEADER);
}

void CDib::Empty()
{
   // this is supposed to clean up whatever is in the DIB

   if(m_lpBMIH)
   {
      delete [] m_lpBMIH;
      m_lpBMIH = NULL;
   }

   if(m_lpBMIH2)
   {
      delete [] m_lpBMIH2;
      m_lpBMIH2 = NULL;
   }

   if(m_lpImage)
   {
      delete [] m_lpImage;
      m_lpImage = NULL;
   }

   if(m_hPalette)
   {
      ::DeleteObject(m_hPalette);
      m_hPalette = NULL;
   }

   if(m_hBitmap)
   {
      ::DeleteObject(m_hBitmap);
      m_hBitmap = NULL;
   }

   m_lpvColorTable = NULL;
   m_nColorTableEntries = 0;
   m_dwSizeImage = 0;
   m_lpvFile = NULL;
   m_hMap = NULL;
   m_hFile = NULL;
}

int CDib::GetPixelIndex(int x, int y)
{
   if(m_lpBMIH == NULL) return -1;

   int iPixel;
   int cx = m_lpBMIH->biWidth;
   int cy = m_lpBMIH->biHeight;

   if ((x < 0) || (x > cx) || (y < 0) || (y > cy)) return -1;

   if ((cx % 2) != 0) cx++;
   if ((cx % 8) != 0)
   {
      cx = cx + 8 - (cx % 8);
   }

   LPBYTE pByte = m_lpImage + (((cy - (y+1)) * (cx/2)) + (x/2));

   if ((x % 2) == 1)
   {
      iPixel = (int) *pByte & 0xF;
   }
   else
   {
      iPixel = (int) *pByte >> 4;
   }

   return iPixel;
}

BOOL CDib::SetPixelIndex(int x, int y, int iPixel, BOOL bSkip)
{
   if(m_lpBMIH == NULL) return FALSE;

   int cx = m_lpBMIH->biWidth;
   int cy = m_lpBMIH->biHeight;

   if ((x < 0) || (x > cx) || (y < 0) || (y > cy)) return FALSE;

   if (bSkip) return TRUE;

   if ((cx % 2) != 0) cx++;
   if ((cx % 8) != 0)
   {
      cx = cx + 8 - (cx % 8);
   }

   LPBYTE pByte = m_lpImage + (((cy - (y+1)) * (cx/2)) + (x/2));

   if ((x % 2) == 1)
   {
      *pByte &= 0xF0;
      *pByte |= iPixel & 0x0F;
   }
   else
   {
      *pByte &= 0x0F;
      *pByte |= (iPixel << 4) & 0xF0;
   }

   return TRUE;
}
