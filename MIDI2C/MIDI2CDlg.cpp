
// MIDI2CDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MIDI2C.h"
#include "MIDI2CDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define OUT_FILE_NAME	"drum_midi_event.h"

#define OUT_FILE_HEAD	"#ifndef __DRUM_MIDI_EVENT_H\r\n#define __DRUM_MIDI_EVENT_H\r\n"
#define OUT_FILE_END	"};\r\n\r\n#endif\r\n"

#define MIDI_FILE_DATA_INDEX_ARRAY	"const unsigned char *drum_midiFile[DRUM_CONFIG_RHYTHM_TYPE_MAX]=\r\n{"

#define MIDI_MAX_NUMBER_MACRO_NAME	"#define DRUM_CONFIG_RHYTHM_TYPE_MAX	"


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

														// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMIDI2CDlg 对话框



CMIDI2CDlg::CMIDI2CDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MIDI2C_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMIDI2CDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTFILE, m_CtrlList);
}

BEGIN_MESSAGE_MAP(CMIDI2CDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUSCANFILE, &CMIDI2CDlg::OnBnClickedBuscanfile)
	ON_BN_CLICKED(IDC_BUCREATE, &CMIDI2CDlg::OnBnClickedBucreate)
	ON_BN_CLICKED(IDC_BUOPENPATH, &CMIDI2CDlg::OnBnClickedBuopenpath)
	ON_BN_CLICKED(IDC_BUADDFILE, &CMIDI2CDlg::OnBnClickedBuaddfile)
	ON_BN_CLICKED(IDC_BUCLEARLIST, &CMIDI2CDlg::OnBnClickedBuclearlist)
END_MESSAGE_MAP()


// CMIDI2CDlg 消息处理程序

BOOL CMIDI2CDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

									//ShowWindow(SW_MAXIMIZE);
	ShowWindow(SW_SHOWNORMAL);

	// TODO: 在此添加额外的初始化代码

	LVCOLUMN lvColumn;

	m_CtrlList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_TWOCLICKACTIVATE);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;


	lvColumn.cx = 50;
	lvColumn.pszText = TEXT("序号");
	m_CtrlList.InsertColumn(0, &lvColumn);

	lvColumn.cx = 100;
	lvColumn.pszText = TEXT("文件名");
	m_CtrlList.InsertColumn(1, &lvColumn);

	lvColumn.cx = 500;
	lvColumn.pszText = TEXT("文件路径");
	m_CtrlList.InsertColumn(2, &lvColumn);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMIDI2CDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMIDI2CDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMIDI2CDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{

	switch (uMsg)
	{
	case BFFM_INITIALIZED:
		::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
		break;
		//case BFFM_SELCHANGED:
		//		TCHAR szPath[MAX_PATH];
		//		SHGetPathFromIDList(PCIDLIST_ABSOLUTE(lParam), szPath);
		//		CString strPath = szPath ;
		//		CString ext = strPath.Right(4) ;
		//		if ( ext == ".bin")
		//			SendMessage(hwnd, BFFM_ENABLEOK, 0, 1);
		//		else
		//			SendMessage(hwnd, BFFM_ENABLEOK, 0, 0);
		//	break ;
	}
	return 0;
}



void CMIDI2CDlg::mFindFile(CString dir)
{
	if (dir.IsEmpty())
	{
		MessageBox(_T("路径不能为空 "), _T("出错"), MB_OK | MB_ICONWARNING);
		return;
	}

	CFileFind ff;
	BOOL bWork = ff.FindFile(dir + "\\*.*");
	while (bWork)
	{
		bWork = ff.FindNextFile();
		if (ff.IsDots())
		{
			continue;
		}
		else if (ff.IsDirectory())
		{
			CString DirPath = ff.GetFilePath();
			mFindFile(DirPath);
		}
		else
		{
			CString FileName = ff.GetFileName();
			//int len = FileName.GetLength() - ff.GetFileTitle().GetLength();
			//CString ext = FileName.Right(len);
			CString fPath = ff.GetFilePath();
			CFile cf;
			cf.Open(fPath, CFile::modeRead | CFile::typeBinary | CFile::shareDenyWrite);
			UINT32 head;
			cf.Read((UINT8 *)&head, 4);
			cf.Close();
			//if (ext == ".snd")
			if (head == 0x6468544D)//"MThd"
			{
				//	添加文件信息到列表
				
#ifdef UNICODE
				WCHAR buff[20];
				WCHAR *fn;
#else
				char buff[20];
				char *fn;
#endif
				g_lvItem.mask = LVIF_TEXT;
				g_lvItem.iItem = m_CtrlList.GetItemCount();
				g_lvItem.iSubItem = 0;
				wsprintf(buff, _T("%u"), g_lvItem.iItem);
				g_lvItem.pszText = buff;						//	序号
				g_nItem = m_CtrlList.InsertItem(&g_lvItem);

				CString str = FileName;
				str = str.Left(str.GetLength() - 4);
				//int len = str.Find(" - 01 - 合成器 - AD Drums Master", 0);
				//if (len >= 0)
				//{
				//	str.Delete(len, str.GetLength() - len);
				//}
				str.Replace(_T(" "), _T("_"));
#ifdef UNICODE
				fn = (WCHAR *)str.GetBuffer(str.GetLength());
#else
				fn = (char *)str.GetBuffer(str.GetLength());
#endif
				m_CtrlList.SetItemText(g_nItem, 1, fn);			//	文件名
#ifdef UNICODE
				fn = (WCHAR *)fPath.GetBuffer(fPath.GetLength());
#else
				fn = (char *)fPath.GetBuffer(fPath.GetLength());
#endif
				m_CtrlList.SetItemText(g_nItem, 2, fn);			//	文件路径

				CString FullPath = dir + _T("\\") + FileName;
				mFindFile(FullPath + _T("\n"));	//	递归调用
			}
		}
	}
	ff.Close();
}


void CMIDI2CDlg::OnBnClickedBuscanfile()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit *m_EDPath;
	CString path;
	m_EDPath = (CEdit *)GetDlgItem(IDC_EDFOLDER);
	m_EDPath->GetWindowText(path);
	if (path.IsEmpty())
	{
		MessageBox(_T("路径不能为空"), _T(" "), MB_OK | MB_ICONWARNING);
		return;
	}
	mFindFile(path);
	path.Empty();
	path.Format(_T("共%d个文件"), m_CtrlList.GetItemCount());
	GetDlgItem(IDC_STATIC)->SetWindowText(path);
}


void CMIDI2CDlg::OnBnClickedBuopenpath()
{
	// TODO: 在此添加控件通知处理程序代码
	//char def[]="C:\\" ;
	PIDLIST_ABSOLUTE pIDLIST;			//函数返回的值存在这里  
	BROWSEINFO brsInfo;
#ifdef UNICODE
	WCHAR dirPath[MAX_PATH];			//接收选择目录的字符数组  
#else
	char dirPath[MAX_PATH];			//接收选择目录的字符数组  
#endif
	CString curDir;

	GetModuleFileName(NULL, dirPath, MAX_PATH);
	_tcsrchr(dirPath, _T('\\'))[1] = 0;
	curDir = dirPath;

	brsInfo.hwndOwner = this->m_hWnd;	//拥有者窗口  
	brsInfo.pidlRoot = NULL;			//根目录为桌面  
	brsInfo.pszDisplayName = dirPath;	//返回的被选择的路径  
	brsInfo.lpszTitle = _T("请选择目录");	//对话框标题  
	brsInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_DONTGOBELOWDOMAIN | BIF_NEWDIALOGSTYLE; //不显示网络路径  
	brsInfo.lpfn = BrowseCallbackProc;				//回调
	brsInfo.lParam = (LPARAM)(LPCTSTR)curDir.GetBuffer(curDir.GetLength());				//默认路径

																						// 初始化COM组件，用完后记得释放  
	CoInitialize(NULL);
	pIDLIST = SHBrowseForFolder(&brsInfo);
	if (pIDLIST)
	{
		//	得到完整路径  
		SHGetPathFromIDList(pIDLIST, dirPath);
		CEdit *m_EDPath;
		m_EDPath = (CEdit *)GetDlgItem(IDC_EDFOLDER);
		m_EDPath->SetWindowText(dirPath);
		//mFindFile(dirPath);
		//wsprintf(dirPath, "共 %u 个文件", m_CtrlList.GetItemCount());
		//m_StaticText.SetWindowText(dirPath);
	}
	CoUninitialize();
	// 释放IDLIST
	CoTaskMemFree((LPVOID)pIDLIST);

}

//const char c_head[] = "#include <stdio.h>\r\nint main(void)\r\n{\r\n\r\n}\r\n";
#define	STR_TAB			_T("\t\t")
#define STR_TAB_SIZE	(sizeof(STR_TAB))

#define STR_LINEFEED	_T("\r\n")
#define STR_LINEFEED_SIZE	(sizeof(STR_LINEFEED) - 1)

void CMIDI2CDlg::OnBnClickedBucreate()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	UCHAR rdBuff[1024];
	UINT32 MThd, Bytes;
	UINT16 synType, chNum, deltaTime,eventCount;
	BOOL bres;
	BOOL bChunkEnd,bNotes;
	UINT32 MTrk, len, count,speed4;
	ULONGLONG curPost,timePost,enevtPost;
	UINT8 lastEvent;
	UINT32 tick, byteLen;
	UINT8 byte, eventMark, eventType, eventByteLen;
	UINT16 timeSignature;

	int i, j;
	int line;
	int	totalLine = m_CtrlList.GetItemCount();

	if (totalLine == 0)
	{
		MessageBox(_T("没有文件需要生成 "), _T("出错"), MB_OK | MB_ICONWARNING);
		return;
	}

	CFile outFile, midiFile;
	CString strOutFile,strMidiName,strMidiData,strArrayPointer;
	strOutFile.Empty();
	strArrayPointer.Empty();
	for (line = 0; line < totalLine; line++)	//	写音乐数据
	{
		strMidiData.Empty();
		strMidiName.Empty();
		str.Empty();
		str = m_CtrlList.GetItemText(line, 2);	//	读取文件路径
		bres = midiFile.Open(str, CFile::modeRead | CFile::typeBinary);
		if (bres)
		{
			midiFile.Read((UINT8 *)&MThd, 4);
			midiFile.Read((UINT8 *)&Bytes, 4);
			if (0x6468544D == MThd && 0x06000000 == Bytes)//"MThd",00 00 00 06
			{
				bNotes = 0;
				midiFile.Read(rdBuff, 6);
				synType = ((UINT16)rdBuff[0] << 8) | (UINT16)rdBuff[1];
				chNum = ((UINT16)rdBuff[2] << 8) | (UINT16)rdBuff[3];
				deltaTime = ((UINT16)rdBuff[4] << 8) | (UINT16)rdBuff[5];
				eventCount = 0;
				while (1)
				{
					midiFile.Read((UINT8 *)&MTrk, 4);
					midiFile.Read(rdBuff, 4);
					len = ((UINT32)rdBuff[0] << 24) | ((UINT32)rdBuff[1] << 16) | ((UINT32)rdBuff[2] << 8) | ((UINT32)rdBuff[3] << 0);//当前轨道字节长度
					curPost = midiFile.GetPosition();
					if (0x6B72544D == MTrk)
					{
						count = 0;
						bChunkEnd = 0;
						while (!bChunkEnd)//解析一个块
						{
							//读时值
							count += midiFile.Read(&byte, 1);
							for (i = 0; (byte > 0x7F) && (i < 5); i++)//时值的表示可能有多个字节
							{
								rdBuff[i] = byte & 0x7F;
								count += midiFile.Read(&byte, 1);
							}
							rdBuff[i] = byte & 0x7F;
							tick = rdBuff[i];
							for (j = i - 1; (j >= 0) && (i > 0); j--)
							{
								tick |= ((UINT32)rdBuff[j]) << (7 * (i - j));
							}
							//读事件标志
							count += midiFile.Read(&eventMark, 1);
							if (0 == (eventMark & 0x80))//可能省略了事件标记
							{
								eventMark = lastEvent;
								midiFile.Seek(-1, CFile::current);
							}
							lastEvent = eventMark;
							if (((eventMark & 0xF0) == 0x80) || ((eventMark & 0xF0) == 0x90))//松开音符，按下音符
							{
								if (!bNotes)
								{
									str.Empty();
									str = "// tick低位,tick高位,事件,键值,力度\r\n";
									strMidiData += str;
									bNotes = 1;
								}
								count += midiFile.Read(rdBuff, 2);
								str.Empty();
								str.Format(_T("0x%02X, 0x%02X, 0x%02X, %d, %d,"), (UINT8)tick, (UINT8)(tick >> 8), eventMark, rdBuff[0], rdBuff[1]);
								str += STR_LINEFEED;
								strMidiData += str;

								eventCount++;
							}
							else if ((eventMark & 0xF0) == 0xA0)//触后音符
							{
								count += midiFile.Read(rdBuff, 2);
								//str.Empty();
								//str.Format(_T("// 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X,"), (UINT8)tick, (UINT8)(tick >> 8), eventMark, rdBuff[0], rdBuff[1]);
								//str += STR_LINEFEED;
								//strMidiData += str;
							}
							else if ((eventMark & 0xF0) == 0xB0)//控制器
							{
								count += midiFile.Read(rdBuff, 2);
								//str.Empty();
								//str.Format(_T("// 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X,"), (UINT8)tick, (UINT8)(tick >> 8), eventMark, rdBuff[0], rdBuff[1]);
								//str += STR_LINEFEED;
								//strMidiData += str;

							}
							else if ((eventMark & 0xF0) == 0xC0)//改变乐器
							{
								count += midiFile.Read(rdBuff, 1);
								//str.Empty();
								//str.Format(_T("// 0x%02X, 0x%02X, 0x%02X, 0x%02X,"), (UINT8)tick, (UINT8)(tick >> 8), eventMark, rdBuff[0]);
								//str += STR_LINEFEED;
								//strMidiData += str;
							}
							else if ((eventMark & 0xF0) == 0xD0)//触后通道
							{
								count += midiFile.Read(rdBuff, 1);
								//str.Empty();
								//str.Format(_T("// 0x%02X, 0x%02X, 0x%02X,"), (UINT8)tick, (UINT8)(tick >> 8), eventMark, rdBuff[0]);
								//str += STR_LINEFEED;
								//strMidiData += str;
							}
							else if ((eventMark & 0xF0) == 0xE0)//滑音
							{
								count += midiFile.Read(rdBuff, 2);
								//str.Empty();
								//str.Format(_T("// 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X,"), (UINT8)tick, (UINT8)(tick >> 8), eventMark, rdBuff[0], rdBuff[0]);
								//str += STR_LINEFEED;
								//strMidiData += str;
							}
							else if (eventMark == 0xF0)//系统码
							{
								//读数据长度

								count += midiFile.Read(&byte, 1);
								for (i = 0; (byte > 0x7F) && (i < 5); i++)//可能有多个字节
								{
									rdBuff[i] = byte & 0x7F;
									count += midiFile.Read(&byte, 1);
								}
								rdBuff[i] = byte & 0x7F;
								byteLen = rdBuff[i];
								for (j = i - 1; (j >= 0) && (i > 0); j--)
								{
									byteLen |= ((UINT32)rdBuff[j]) << (7 * (i - j));
								}
								count += midiFile.Read(rdBuff, byteLen);
							}
							else if (eventMark == 0xFF)
							{
								count += midiFile.Read(&eventType, 1);
								switch (eventType)
								{
								case 0x00://设置轨道，长度2字节
									count += midiFile.Read(rdBuff, 2);
									break;
								case 0x01://文本信息，长度可变
										  //break;
								case 0x02://歌曲版权，长度可变
										  //break;
								case 0x03://第一次出现表示歌曲主标题，第二次出现表示副标题，长度可变
										  //break;
								case 0x04://乐器名称，长度可变
										  //break;
								case 0x05://歌词，长度可变
										  //break;
								case 0x06://标记，长度可变
										  //break;
								case 0x07://开始点，长度可变
										  //读数据长度
									count += midiFile.Read(&byte, 1);
									for (i = 0; (byte > 0x7F) && (i < 5); i++)//可能有多个字节
									{
										rdBuff[i] = byte & 0x7F;
										count += midiFile.Read(&byte, 1);
									}
									rdBuff[i] = byte & 0x7F;
									byteLen = rdBuff[i];
									for (j = i - 1; (j >= 0) && (i > 0); j--)
									{
										byteLen |= ((UINT32)rdBuff[j]) << (7 * (i - j));
									}
									count += midiFile.Read(rdBuff, byteLen);
									//str.Empty();
									//str.Format(_T("// 0x%02X, 0x%02X, 0x%02X, 0x%02X, // "), (UINT8)tick, (UINT8)(tick >> 8), eventMark, eventType);
									//strMidiData += str;
									//rdBuff[byte] = 0;
									//str.Empty();
									//str.Format(_T("%s"), rdBuff);
									//str += STR_LINEFEED;
									//strMidiData += str;
									break;
								case 0x2F://音轨结束标记，长度0字节
									bChunkEnd = 1;
									count += midiFile.Read(rdBuff, 1);
									break;
								case 0x51://速度，四分音符的微秒数，长度3字节
									count += midiFile.Read(&byte, 1);//长度
									count += midiFile.Read(rdBuff, byte & 0x7F);
									speed4 = ((UINT32)rdBuff[0] << 16) | ((UINT32)rdBuff[1] << 8) | ((UINT32)rdBuff[2] << 0);
									//str.Empty();
									//str.Format(_T("// 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X,"), (UINT8)tick, (UINT8)(tick >> 8), eventMark, eventType, rdBuff[0], rdBuff[1], rdBuff[2]);
									//str += STR_LINEFEED;
									//strMidiData += str;
									break;
								case 0x58://节拍，长度4字节
									count += midiFile.Read(&byte, 1);//长度
									count += midiFile.Read(rdBuff, byte & 0x7F);
									//str.Empty();
									//str.Format(_T("// 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X,"), (UINT8)tick, (UINT8)(tick >> 8), eventMark, eventType, rdBuff[0], rdBuff[1], rdBuff[2], rdBuff[3]);
									//str += STR_LINEFEED;
									//strMidiData += str;
									timeSignature = rdBuff[0];
									timeSignature <<= 8;
									timeSignature |= rdBuff[1];
									break;
								case 0x59://调号，长度2字节
									count += midiFile.Read(&byte, 1);//长度
									count += midiFile.Read(rdBuff, byte & 0x7F);
									break;
								case 0x7F://音序信息，长度可变
									count += midiFile.Read(&byte, 1);//长度
									count += midiFile.Read(rdBuff, byte & 0x7F);
									break;
								default:
									break;
								}
							}
						}
					}
					if (midiFile.GetPosition() >= midiFile.GetLength())
					{
						strMidiName.Empty();//清空字符串
						str.Empty();

						str = m_CtrlList.GetItemText(line, 1);	//文件名
						CString str2;
						//str2.Format(_T("extern const unsigned char MidiEvent_%s[%d][5];\r\n"), str.GetBuffer(), eventCount + 2);
						//strArrayName += str2;
						str2.Empty();
						str2.Format(_T("&MidiEvent_%s[0][0],\r\n"),str.GetBuffer());
						strArrayPointer += str2;
						strMidiName.Format(_T("const unsigned char MidiEvent_%s[%d][5]=\r\n{\r\n"),str.GetBuffer(),eventCount + 2);
						str.Empty();
						str.Format(_T("//前2个字节是一个四分音符tick数，后3个字节是一个四分音符的微秒数，低字节在前\r\n0x%02x, 0x%02x, 0x%02X, 0x%02X, 0x%02X,\r\n"), (UINT8)deltaTime, (UINT8)(deltaTime >> 8), (UINT8)speed4, (UINT8)(speed4 >> 8), (UINT8)(speed4 >> 16));
						strMidiName += str;
						str.Empty();
						str.Format(_T("//前2个字节事件数量，第3字节是节拍分子，第4字节是节拍分母\r\n0x%02x, 0x%02x, 0x%02x, 0x%02x,    0,\r\n"), (UINT8)eventCount, (UINT8)(eventCount >> 8),(UINT8)(timeSignature>>8), (UINT8)(timeSignature & 0xFF));
						strMidiName += str;
						strOutFile += strMidiName + strMidiData + _T("};\r\n\r\n");
						break;//到达文件结尾
					}
					else
					{
						midiFile.Seek(curPost + len, CFile::begin);
					}
				}
			}
		}
		else
		{
			MessageBox(_T("无法打开文件\r\n") + str, _T("出错"), MB_OK | MB_ICONWARNING);
		}
		midiFile.Close();
	}
	outFile.Open(_T(OUT_FILE_NAME), CFile::modeCreate | CFile::modeWrite);
	//outFile.Write(STR_LINEFEED, STR_LINEFEED_SIZE);
	//outFile.Write(STR_LINEFEED, STR_LINEFEED_SIZE);
	outFile.Write(OUT_FILE_HEAD, sizeof(OUT_FILE_HEAD) - 1);
	//outFile.Write(STR_LINEFEED, STR_LINEFEED_SIZE);
	//outFile.Write(strArrayName.GetBuffer(), strArrayName.GetLength());
	//midi信息
	outFile.Write(STR_LINEFEED, STR_LINEFEED_SIZE);
	outFile.Write(STR_LINEFEED, STR_LINEFEED_SIZE);
	outFile.Write(strOutFile.GetBuffer(), strOutFile.GetLength());

	//midi文件数量宏定义
	outFile.Write(_T(MIDI_MAX_NUMBER_MACRO_NAME), sizeof(MIDI_MAX_NUMBER_MACRO_NAME) - 1);
	str.Empty();
	str.Format("%d", totalLine);
	outFile.Write(str.GetBuffer(), str.GetLength());
	outFile.Write(STR_LINEFEED, STR_LINEFEED_SIZE);
	outFile.Write(STR_LINEFEED, STR_LINEFEED_SIZE);

	//midi数组索引
	outFile.Write(_T(MIDI_FILE_DATA_INDEX_ARRAY), sizeof(MIDI_FILE_DATA_INDEX_ARRAY) - 1);
	outFile.Write(STR_LINEFEED, STR_LINEFEED_SIZE);
	outFile.Write(strArrayPointer.GetBuffer(), strArrayPointer.GetLength());

	outFile.Write(OUT_FILE_END, sizeof(OUT_FILE_END)-1);
	outFile.Close();
	str.Empty();
	strOutFile.Empty();
	//strArrayName.Empty();
	strMidiData.Empty();
	strMidiName.Empty();
	//system("start MidiEvent.c");
	
	//GetDlgItem(IDC_STATIC)->SetWindowText("创建成功");
	//if (MessageBox("创建完成，是否退出？", "完成", MB_YESNO | MB_ICONQUESTION) == IDYES)
	//{
	//	SendMessage(WM_CLOSE);
	//	//PostQuitMessage(0);
	//}
}



void CMIDI2CDlg::OnBnClickedBuaddfile()
{
	// TODO: 在此添加控件通知处理程序代码

	CString fPath = _T("");

	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.mid)|*.mid|All Files (*.*)|*.*||"), NULL);

	if (dlgFile.DoModal())
	{
		fPath = dlgFile.GetPathName();
		if (!fPath.IsEmpty())
		{

			CFile cf;
			cf.Open(fPath, CFile::modeRead | CFile::typeBinary);
			CString FileName = cf.GetFileName();
			UINT32 head;
			cf.Read((UINT8 *)&head, 4);
			cf.Close();
			//if (ext == ".snd")
			if (head == 0x6468544D)//"MThd"
			{
				//	添加文件信息到列表
				
#ifdef UNICODE
				WCHAR buff[20];
				WCHAR *fn;
#else
				char buff[20];
				char *fn;
#endif // UNICODE

				
				g_lvItem.mask = LVIF_TEXT;
				g_lvItem.iItem = m_CtrlList.GetItemCount();
				g_lvItem.iSubItem = 0;
				wsprintf(buff, _T("%u"), g_lvItem.iItem);
				g_lvItem.pszText = buff;						//	序号
				int itemNo;
				itemNo = m_CtrlList.InsertItem(&g_lvItem);

				CString str = FileName;
				str = str.Left(str.GetLength() - 4);
				//int len = str.Find(" - 01 - 合成器 - AD Drums Master", 0);
				//if (len >= 0)
				//{
				//	str.Delete(len, str.GetLength() - len);
				//}
				str.Replace(_T(" "), _T("_"));
#ifdef UNICODE
				fn = (WCHAR *)str.GetBuffer(str.GetLength());
#else
				fn = (char *)str.GetBuffer(str.GetLength());
#endif
				m_CtrlList.SetItemText(itemNo, 1, fn);			//	文件名
#ifdef UNICODE
				fn = (WCHAR *)fPath.GetBuffer(fPath.GetLength());
#else
				fn = (char *)fPath.GetBuffer(fPath.GetLength());
#endif
				m_CtrlList.SetItemText(itemNo, 2, fn);			//	文件路径
				str.Empty();
				str.Format(_T("共%d个文件"), m_CtrlList.GetItemCount());
				GetDlgItem(IDC_STATIC)->SetWindowText(str);
			}
		}
	}
}


void CMIDI2CDlg::OnBnClickedBuclearlist()
{
	// TODO: 在此添加控件通知处理程序代码

	m_CtrlList.DeleteAllItems();
	GetDlgItem(IDC_STATIC)->SetWindowText(_T("已清空"));
}

