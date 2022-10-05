// SkinEdit.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SkinEdit.h"

// CSkinEdit

IMPLEMENT_DYNAMIC(CSkinEdit, CEdit)

CSkinEdit::CSkinEdit()
{
	m_hBmpDefault  = NULL;	
	m_bBkgColor	   = FALSE;	
	m_cfText	   = g_gbl.GetRGB( IDX_RGB_FONT_BLACK );
	m_cfBackGround = g_gbl.GetRGB( IDX_RGB_MAIN_BACKGROUND );

	m_nXPos       = 0;
	m_nYPos       = 0;
	m_nLIMIT_TYPE = DATA_TYPE::NONE;
	m_nLIMIT_SIZE = 0;

	memset( &m_sizeDefault, 0x00, sizeof(SIZE) );		
}

CSkinEdit::~CSkinEdit()
{
}


BEGIN_MESSAGE_MAP(CSkinEdit, CEdit)	
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR ()
	ON_WM_KEYDOWN   ()	
END_MESSAGE_MAP()

// CSkinEdit 메시지 처리기입니다.


BOOL CSkinEdit::INPUT_NUMBER( WPARAM wParam )
{
	// 숫자만입력 : 음수, 양수포함
	if(GetKeyState(VK_SHIFT)<0)
	    if(wParam == 9)
			return TRUE;

	if( GetKeyState( VK_SHIFT ) < 0 )
		return FALSE;

	if(wParam == VK_BACK || wParam == VK_LEFT || wParam == VK_UP || wParam == VK_RIGHT ||
	wParam == VK_DOWN || wParam == VK_DELETE || wParam == VK_HOME || wParam == VK_END)
	return TRUE;

	if(wParam != 0x30 && wParam != 0x31 && wParam != 0x32 && wParam != 0x33 &&
	wParam != 0x34 && wParam != 0x35 && wParam != 0x36 && wParam != 0x37 &&
	wParam != 0x38 && wParam != 0x39 && wParam != 0x31 && wParam != 0xbd && wParam !=9 &&
	wParam != VK_NUMPAD0 && wParam != VK_NUMPAD1 && wParam != VK_SUBTRACT &&  // 1.  추가부분 = wParam != VK_SUBTRACT)
	wParam != VK_NUMPAD2 && wParam != VK_NUMPAD3 && wParam != VK_NUMPAD4 && wParam != VK_NUMPAD5 &&
	wParam != VK_NUMPAD6 && wParam != VK_NUMPAD7 && wParam != VK_NUMPAD8 && wParam != VK_NUMPAD9 )
	{
		return FALSE;
	}
	else
	{
	    	CString strVAL = _T("");
			CString strCheck = _T("");
			CString strTemp = _T("");

			GetWindowText( strVAL );

			long long int nVal =  _ttoi64(strVAL);

			int nPa = (int)wParam - 0x30;

			int nStartChar = 0;
			int nEndChar = 0;
			GetSel(nStartChar,nEndChar);

			for(int n = 0; n< nEndChar;n++)
			{
				nPa = nPa * 10;
			}

			if(INT_MAX < nVal + nPa)
			{
				if(wParam != 0xbd || wParam != VK_SUBTRACT) // 2. 추가부분
					return FALSE;
			}
			
			if(INT_MIN >=  nVal- nPa)
				return FALSE;
			
			short nCount = 0;
			int nLength = strVAL.GetLength();
			strCheck = strVAL.Mid(nLength - 1);
					

			for(int n = 0; n < nLength ; n++)
			{
				strTemp = strVAL.GetAt(n);
				if(strTemp.Find(_T("-")) == 0)
					nCount++;
			}


			// 3. 추가부분 처음에 '-' 가 있고, 그 후에 -가 들어오면 막는 로직 수정
			if((strVAL.Left(1) == '-' && wParam == 0xbd || wParam == VK_SUBTRACT && nCount>0))
					return FALSE;
	}
	return TRUE ;
}

BOOL CSkinEdit::INPUT_FLOAT( WPARAM wParam )
{
	// 소숫점만 입력 : 음수, 양수포함
	if(GetKeyState(VK_SHIFT)<0)
	    if(wParam == 9)
			return TRUE;

	if( GetKeyState( VK_SHIFT ) < 0 )
		return FALSE;
	
	if(wParam != 0x30 && wParam != 0x31 && wParam != 0x32 && wParam != 0x33 &&
	   wParam != 0x34 && wParam != 0x35 && wParam != 0x36 && wParam != 0x37 &&
	   wParam != 0x38 && wParam != 0x39 && wParam != 0x31 && wParam != 0xBD && wParam != 0xBE &&
	   wParam != VK_BACK && wParam != VK_LEFT && wParam != VK_UP && wParam != VK_RIGHT && wParam !=9 &&
	   wParam != VK_DOWN && wParam != VK_DELETE && wParam != VK_NUMPAD0 && wParam != VK_NUMPAD1 &&
	   wParam != VK_NUMPAD2 && wParam != VK_NUMPAD3 && wParam != VK_NUMPAD4 && wParam != VK_NUMPAD5 &&
	   wParam != VK_NUMPAD6 && wParam != VK_NUMPAD7 && wParam != VK_NUMPAD8 && wParam != VK_NUMPAD9 &&
	   wParam != VK_HOME && wParam != VK_END && wParam != VK_SUBTRACT && wParam != VK_DECIMAL ) 
		{
			return FALSE;
		}
		else
		{
		    CString strVAL = _T("");
			CString strCheck = _T("");
			CString strTemp = _T("");

			GetWindowText( strVAL );
			short nCount = 0;
			short nPointCount = 0;
			int nLength = strVAL.GetLength();
			strCheck = strVAL.Mid(nLength - 1);

			for(int n = 0; n < nLength ; n++)
			{
				strTemp = strVAL.GetAt(n);
				if(strTemp.Find('-') >= 0)
					nCount++;
				if(strTemp.Find('.') >= 0)
					nPointCount ++;
			}
			if((strVAL.Left(1) == '0' && wParam == 0x30 && strVAL.GetAt(1) == '0' ))
			{
				return FALSE;
			}

			if((strVAL.Left(1) == '-' && wParam == 0xBD || wParam == VK_SUBTRACT && nCount>0)) 
				return FALSE;
			
			if((strVAL.Left(1) == '.' && wParam == 0xBE && nPointCount>0) || (strVAL.Left(1) != '.' && nLength == 0 && wParam == 0xBE) ||
			   (strVAL.Left(1) != '.' && nLength > 0 && wParam == 0xBE && nPointCount > 0))
				return FALSE;
			if((strVAL.Left(1) == '-' && nLength == 1 &&wParam == 0xBE)||(strVAL.Left(1) == '-' && nLength == 1 &&wParam == 0xBE))
				return FALSE;

			// 키패드 '.' 추가포함
			if((strVAL.Left(1) == '.' && wParam == VK_DECIMAL && nPointCount>0) || (strVAL.Left(1) != '.' && nLength == 0 && wParam == VK_DECIMAL) ||
			   (strVAL.Left(1) != '.' && nLength > 0 && wParam == VK_DECIMAL && nPointCount > 0))
				return FALSE;
			if((strVAL.Left(1) == '-' && nLength == 1 &&wParam == VK_DECIMAL)||(strVAL.Left(1) == '-' && nLength == 1 &&wParam == VK_DECIMAL))
				return FALSE;
	
		}
	return TRUE;
}

BOOL CSkinEdit::INPUT_CHAR( WPARAM wParam)
{
	return TRUE;
}


void CSkinEdit::SetBkColor( COLORREF cfBackGround )
{
	m_cfBackGround = cfBackGround;
	m_bBkgColor = TRUE;
}


void CSkinEdit::SetBitmapID( UINT uDefaultImage )
{
	// 각 비트맵의 사이즈 정보를 얻어온다.
	m_sizeDefault = g_gbl.GetBitmapSize( uDefaultImage );

	// 각 비트맵의 핸들을 얻어온다.
	m_hBmpDefault = g_gbl.GetBitmap( uDefaultImage );	
}


BOOL CSkinEdit::PreTranslateMessage( MSG* pMsg )
{
	if( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN )
	{
		if( GetStyle() & ES_MULTILINE )
		{
			if( GetFocus() )
			{
				int nLen = GetWindowTextLength();
				SetSel( nLen, nLen );
				ReplaceSel( _N("") );
			}
		}		
	}
	else if( pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_LBUTTONUP )
	{
		CRect rc;
		GetClientRect( &rc );
		InvalidateRect( rc );
	}
	else if ( pMsg->message == WM_KEYDOWN )
	{
		TCHAR szKey = (TCHAR)pMsg->wParam;

		switch ( m_nLIMIT_TYPE )
		{		
		// 문자열
		case CHAR:
		case VARCHAR:
		{			
			if( !INPUT_CHAR( pMsg->wParam ) )	return TRUE;			
			break;
		}

		// 정수
		case BIGINT:
		case INTEGER:
		case SMALLINT:
		{
			if( !INPUT_NUMBER( pMsg->wParam ) )		return TRUE;
			break;
		}

		// 실수
		case DOUBLE:
		case FLOAT:
		case NUMERIC:
		case REAL:
		{
			if( !INPUT_FLOAT( pMsg->wParam ) )		return TRUE;
			break;
		}

		case NONE:
		default:			
			break;
		}	
	}

	return CEdit::PreTranslateMessage( pMsg );
}


BOOL CSkinEdit::OnEnChange()
{
	switch ( m_nLIMIT_TYPE )
	{
	case CHAR:
	case VARCHAR:
		{
			if ( m_nLIMIT_SIZE <= 0 )
				return FALSE;

			CString strVAL = _T("");
			GetWindowText( strVAL );

			// 유니코드인 경우
			int nLength = WideCharToMultiByte( CP_ACP, 0, strVAL.GetBuffer(), strVAL.GetLength(), NULL, 0, NULL, NULL );

			if( nLength > m_nLIMIT_SIZE )
			{
				CString strOutText = strVAL.Left( strVAL.GetLength() - 1 );  
				SetWindowText( strOutText );

				SetSel( strOutText.GetLength(), strOutText.GetLength() );
			}
		}
		return FALSE;

	case NUMERIC:
	case REAL:
	case FLOAT:
	case DOUBLE:
		{
			CString strVAL = _T("");
			CString strOutText = _T("");  
			CString strTemp = _T("");
			GetWindowText( strVAL );
			
			double dbMax = DBL_MAX;
			double dbMin = -DBL_MAX;//DBL_MIN;
			double dbVal = _ttof(strVAL);
			
			int nCheck1 = strVAL.Find('.');
			int nCheck2 = strVAL.Find('-');
			int nCheckCount = 0;

			int nStartChar = 0;
			int nEndChar = 0;
			GetSel(nStartChar,nEndChar);

			if((nCheck1 >= 0 || nCheck2 >= 0) || (strVAL.Left(2) == _T("00")))
			{
				if(strVAL.Left(1) != '-' && nCheck2 >= 0)
				{
					strVAL.Remove('-');
					SetWindowText(strVAL);
					SetSel(nStartChar - 1, nEndChar - 1 );
					return FALSE;
				}
				if( (strVAL.Left(1) == '.' && nCheck1 >= 0) ||
					(strVAL.Find(_T("-.")) >= 0))
				{
					strVAL.Remove('.');
					SetWindowText(strVAL);

					SetSel(nStartChar - 1, nEndChar - 1 );
					return FALSE;
				}

				if(strVAL.Left(2) == _T("00"))
				{
					strVAL.Delete(nEndChar - 1);
					SetWindowText( strVAL );
					SetSel(nStartChar -1, nEndChar -1);
					return FALSE;
				}

				if(strVAL.Left(3) == _T("-00"))
				{
					strVAL.Delete(nEndChar - 1);
					SetWindowText( strVAL );
					SetSel(nStartChar -1, nEndChar -1);
					return FALSE;
				}
				if(strVAL.Left(2) == _T("-0"))
				{
					if(strVAL.Left(3)!= _T("-0.") && strVAL.GetLength() > 2)
					{
						strVAL.Delete(nEndChar - 1);
						SetWindowText( strVAL );
						SetSel(nStartChar -1, nEndChar -1);
						return FALSE;
					}
				}
			}

			if(strVAL.Left(1) == _T("0"))
			{
				if(strVAL.GetAt(1) != '.' && strVAL.GetLength() > 1)
				{
					strVAL.Delete(nEndChar - 1);
					SetWindowText( strVAL );
					SetSel(nStartChar -1, nEndChar -1);
					return FALSE;
				}
			}

			if((dbMax < dbVal || dbMin > dbVal) && dbVal != 0.0)
			{
					strVAL.Delete(nEndChar - 1);
					SetWindowText( strVAL );
					SetSel(nStartChar -1, nEndChar -1);
					return FALSE;
			}
		}
		break;

	case SMALLINT:
		{
			CString strVAL = _T("");
			CString strOutText = _T("");
	
			GetWindowText( strVAL );

			
			int nStartChar = 0;
			int nEndChar = 0;
			GetSel(nStartChar,nEndChar);
			
			if(strVAL.Find('-') >= 0)
			{
				
				if(strVAL.Left(1) != '-')
				{
					strVAL.Remove('-');
					SetWindowText(strVAL);
					SetSel(nStartChar - 1, nEndChar - 1 );
					

					return TRUE;
				}
			}

			long long int nVal =  _ttoi64(strVAL);

			//int 최대보다 클때
			if(SHRT_MAX < nVal)
			{
				if(strVAL.GetLength() > nEndChar)
				{
					strVAL.Delete(nEndChar - 1);
					SetWindowText( strVAL );
					SetSel(nStartChar -1, nEndChar -1);
					return FALSE;
				}
				strVAL.Delete(strVAL.GetLength() -1 );
				SetWindowText( strVAL );
				SetSel(nStartChar -1, nEndChar -1);
				return FALSE;				
			}
			
			if(SHRT_MIN > nVal)
			{
				if(strVAL.Left(1) != '-' &&  nEndChar > 1)
				{
					strVAL.Delete(nEndChar - 1);
					SetWindowText( strVAL );
					SetSel(nStartChar -1, nEndChar -1);
					return FALSE;
				}
				strVAL.Delete(nEndChar - 1);
				SetWindowText( strVAL );
				SetSel(nStartChar -1, nEndChar -1);
				return FALSE;
			}

			if(strVAL.Left(2) == _T("-0") )
			{
				strVAL.Delete(nEndChar - 1);
				SetWindowText( strVAL );
				SetSel(nStartChar -1, nEndChar -1);
				return FALSE;
			}


			if( strVAL.Left(2) == "00")
			{
				strVAL.Delete(nEndChar - 1);
				SetWindowText( strVAL );
				SetSel(nStartChar -1, nEndChar -1);
				return FALSE;
			} // 9. 추가부분 (처음에 00이면 0하나 삭제 로직)

			if( strVAL.Left(1) == "0") 
			{
				for ( int i = 1; i<10; i++)  // 8. 추가부분 (처음이 01~09값이면 뒤에 값 삭제 로직)
				{
					 strOutText.Format(_T("0%d"),i);
				
					if (  strVAL.Left(2) == strOutText )
					{
						strVAL.Delete(nEndChar - 1);
						SetWindowText( strVAL );
						SetSel(nStartChar , nEndChar );
						return FALSE;
					}
				}
				
			} 		
		}
		break;

	case INTEGER:
		{
			CString strVAL = _T("");
			CString strOutText = _T("");
	
			GetWindowText( strVAL );
			
			int nStartChar = 0;
			int nEndChar = 0;
			GetSel(nStartChar,nEndChar);
			
			if(strVAL.Find('-') >= 0)
			{
				
				if(strVAL.Left(1) != '-')
				{
					strVAL.Remove('-');
					SetWindowText(strVAL);
					SetSel(nStartChar - 1, nEndChar - 1 );
					

					return TRUE;
				}
			}

			long long int nVal =  _ttoi64(strVAL);

			//int 최대보다 클때
			if(INT_MAX < nVal)
			{
				if(strVAL.GetLength() > nEndChar)
				{
					strVAL.Delete(nEndChar - 1);
					SetWindowText( strVAL );
					SetSel(nStartChar -1, nEndChar -1);
					return FALSE;
				}
				strVAL.Delete(strVAL.GetLength() -1 );
				SetWindowText( strVAL );
				SetSel(nStartChar -1, nEndChar -1);
				return FALSE;				
			}
			
			if(INT_MIN > nVal)
			{
				if(strVAL.Left(1) != '-' &&  nEndChar > 1)
				{
					strVAL.Delete(nEndChar - 1);
					SetWindowText( strVAL );
					SetSel(nStartChar -1, nEndChar -1);
					return FALSE;
				}
				strVAL.Delete(nEndChar - 1);
				SetWindowText( strVAL );
				SetSel(nStartChar -1, nEndChar -1);
				return FALSE;
			}

			if(strVAL.Left(2) == _T("-0") )
			{
				strVAL.Delete(nEndChar - 1);
				SetWindowText( strVAL );
				SetSel(nStartChar -1, nEndChar -1);
				return FALSE;
			}


				if( strVAL.Left(2) == "00")
			{
				strVAL.Delete(nEndChar - 1);
				SetWindowText( strVAL );
				SetSel(nStartChar -1, nEndChar -1);
				return FALSE;
			} // 7. 추가부분 (처음에 00이면 0하나 삭제 로직)

			if( strVAL.Left(1) == "0") 
			{
				for ( int i = 1; i<10; i++) // 6. 추가부분 (처음이 01~09값이면 뒤에 값 삭제 로직)
				{
					 strOutText.Format(_T("0%d"),i);
				
					if (  strVAL.Left(2) == strOutText )
					{
						strVAL.Delete(nEndChar - 1);
						SetWindowText( strVAL );
						SetSel(nStartChar , nEndChar );
						return FALSE;
					}
				}
				
			}			
		}
		
		break;
	case BIGINT:
		break;
	}

	return FALSE;
}


BOOL CSkinEdit::OnEraseBkgnd( CDC* pDC )
{	
	CDC MemDC;
	MemDC.CreateCompatibleDC( pDC );

	CBitmap *pBitmap    = NULL;
	CBitmap *pOldBitmap = NULL;
	
	if( m_hBmpDefault )
	{	
		pBitmap = CBitmap::FromHandle( m_hBmpDefault );
		pOldBitmap = MemDC.SelectObject( pBitmap );

		pDC->BitBlt( m_nXPos, m_nYPos, m_sizeDefault.cx, m_sizeDefault.cy, &MemDC, 0, 0, SRCCOPY );
		MemDC.SelectObject( pOldBitmap );
	}
	//Bitmap이 Setting되지 않고 Background 색상이 Setting 되었으면 색상 삽입
	else if( m_bBkgColor )
	{
		CRect rect;
		GetClientRect( &rect );

		CBrush pBrush;
		pBrush.CreateSolidBrush( m_cfBackGround );		
		pDC->FillRect( &rect, &pBrush );		
	}

	return TRUE;
}


BOOL CSkinEdit::OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message )
{
	CPoint pntCursor;
	GetCursorPos( &pntCursor );
	ScreenToClient( &pntCursor );

	CRect rect;
	GetWindowRect( &rect );
	
	//if mouse is not in the edit area then show arrow cursor	
	if( rect.PtInRect( pntCursor ) )
	{
		SetCursor( AfxGetApp()->LoadStandardCursor( MAKEINTRESOURCE( IDC_IBEAM ) ) );
		return TRUE;
	}

	return CEdit::OnSetCursor( pWnd, nHitTest, message );
}


void CSkinEdit::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{	
	CEdit::OnKeyDown( nChar, nRepCnt, nFlags );

	CRect rc;
	GetClientRect( &rc );
	InvalidateRect( rc );
}