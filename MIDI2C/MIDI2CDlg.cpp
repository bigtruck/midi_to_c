
// MIDI2CDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

														// ʵ��
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


// CMIDI2CDlg �Ի���



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


// CMIDI2CDlg ��Ϣ�������

BOOL CMIDI2CDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

									//ShowWindow(SW_MAXIMIZE);
	ShowWindow(SW_SHOWNORMAL);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	LVCOLUMN lvColumn;

	m_CtrlList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_TWOCLICKACTIVATE);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;


	lvColumn.cx = 50;
	lvColumn.pszText = TEXT("���");
	m_CtrlList.InsertColumn(0, &lvColumn);

	lvColumn.cx = 100;
	lvColumn.pszText = TEXT("�ļ���");
	m_CtrlList.InsertColumn(1, &lvColumn);

	lvColumn.cx = 500;
	lvColumn.pszText = TEXT("�ļ�·��");
	m_CtrlList.InsertColumn(2, &lvColumn);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMIDI2CDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		MessageBox(_T("·������Ϊ�� "), _T("����"), MB_OK | MB_ICONWARNING);
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
				//	����ļ���Ϣ���б�
				
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
				g_lvItem.pszText = buff;						//	���
				g_nItem = m_CtrlList.InsertItem(&g_lvItem);

				CString str = FileName;
				str = str.Left(str.GetLength() - 4);
				//int len = str.Find(" - 01 - �ϳ��� - AD Drums Master", 0);
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
				m_CtrlList.SetItemText(g_nItem, 1, fn);			//	�ļ���
#ifdef UNICODE
				fn = (WCHAR *)fPath.GetBuffer(fPath.GetLength());
#else
				fn = (char *)fPath.GetBuffer(fPath.GetLength());
#endif
				m_CtrlList.SetItemText(g_nItem, 2, fn);			//	�ļ�·��

				CString FullPath = dir + _T("\\") + FileName;
				mFindFile(FullPath + _T("\n"));	//	�ݹ����
			}
		}
	}
	ff.Close();
}


void CMIDI2CDlg::OnBnClickedBuscanfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEdit *m_EDPath;
	CString path;
	m_EDPath = (CEdit *)GetDlgItem(IDC_EDFOLDER);
	m_EDPath->GetWindowText(path);
	if (path.IsEmpty())
	{
		MessageBox(_T("·������Ϊ��"), _T(" "), MB_OK | MB_ICONWARNING);
		return;
	}
	mFindFile(path);
	path.Empty();
	path.Format(_T("��%d���ļ�"), m_CtrlList.GetItemCount());
	GetDlgItem(IDC_STATIC)->SetWindowText(path);
}


void CMIDI2CDlg::OnBnClickedBuopenpath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//char def[]="C:\\" ;
	PIDLIST_ABSOLUTE pIDLIST;			//�������ص�ֵ��������  
	BROWSEINFO brsInfo;
#ifdef UNICODE
	WCHAR dirPath[MAX_PATH];			//����ѡ��Ŀ¼���ַ�����  
#else
	char dirPath[MAX_PATH];			//����ѡ��Ŀ¼���ַ�����  
#endif
	CString curDir;

	GetModuleFileName(NULL, dirPath, MAX_PATH);
	_tcsrchr(dirPath, _T('\\'))[1] = 0;
	curDir = dirPath;

	brsInfo.hwndOwner = this->m_hWnd;	//ӵ���ߴ���  
	brsInfo.pidlRoot = NULL;			//��Ŀ¼Ϊ����  
	brsInfo.pszDisplayName = dirPath;	//���صı�ѡ���·��  
	brsInfo.lpszTitle = _T("��ѡ��Ŀ¼");	//�Ի������  
	brsInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_DONTGOBELOWDOMAIN | BIF_NEWDIALOGSTYLE; //����ʾ����·��  
	brsInfo.lpfn = BrowseCallbackProc;				//�ص�
	brsInfo.lParam = (LPARAM)(LPCTSTR)curDir.GetBuffer(curDir.GetLength());				//Ĭ��·��

																						// ��ʼ��COM����������ǵ��ͷ�  
	CoInitialize(NULL);
	pIDLIST = SHBrowseForFolder(&brsInfo);
	if (pIDLIST)
	{
		//	�õ�����·��  
		SHGetPathFromIDList(pIDLIST, dirPath);
		CEdit *m_EDPath;
		m_EDPath = (CEdit *)GetDlgItem(IDC_EDFOLDER);
		m_EDPath->SetWindowText(dirPath);
		//mFindFile(dirPath);
		//wsprintf(dirPath, "�� %u ���ļ�", m_CtrlList.GetItemCount());
		//m_StaticText.SetWindowText(dirPath);
	}
	CoUninitialize();
	// �ͷ�IDLIST
	CoTaskMemFree((LPVOID)pIDLIST);

}

//const char c_head[] = "#include <stdio.h>\r\nint main(void)\r\n{\r\n\r\n}\r\n";
#define	STR_TAB			_T("\t\t")
#define STR_TAB_SIZE	(sizeof(STR_TAB))

#define STR_LINEFEED	_T("\r\n")
#define STR_LINEFEED_SIZE	(sizeof(STR_LINEFEED) - 1)

void CMIDI2CDlg::OnBnClickedBucreate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox(_T("û���ļ���Ҫ���� "), _T("����"), MB_OK | MB_ICONWARNING);
		return;
	}

	CFile outFile, midiFile;
	CString strOutFile,strMidiName,strMidiData,strArrayPointer;
	strOutFile.Empty();
	strArrayPointer.Empty();
	for (line = 0; line < totalLine; line++)	//	д��������
	{
		strMidiData.Empty();
		strMidiName.Empty();
		str.Empty();
		str = m_CtrlList.GetItemText(line, 2);	//	��ȡ�ļ�·��
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
					len = ((UINT32)rdBuff[0] << 24) | ((UINT32)rdBuff[1] << 16) | ((UINT32)rdBuff[2] << 8) | ((UINT32)rdBuff[3] << 0);//��ǰ����ֽڳ���
					curPost = midiFile.GetPosition();
					if (0x6B72544D == MTrk)
					{
						count = 0;
						bChunkEnd = 0;
						while (!bChunkEnd)//����һ����
						{
							//��ʱֵ
							count += midiFile.Read(&byte, 1);
							for (i = 0; (byte > 0x7F) && (i < 5); i++)//ʱֵ�ı�ʾ�����ж���ֽ�
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
							//���¼���־
							count += midiFile.Read(&eventMark, 1);
							if (0 == (eventMark & 0x80))//����ʡ�����¼����
							{
								eventMark = lastEvent;
								midiFile.Seek(-1, CFile::current);
							}
							lastEvent = eventMark;
							if (((eventMark & 0xF0) == 0x80) || ((eventMark & 0xF0) == 0x90))//�ɿ���������������
							{
								if (!bNotes)
								{
									str.Empty();
									str = "// tick��λ,tick��λ,�¼�,��ֵ,����\r\n";
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
							else if ((eventMark & 0xF0) == 0xA0)//��������
							{
								count += midiFile.Read(rdBuff, 2);
								//str.Empty();
								//str.Format(_T("// 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X,"), (UINT8)tick, (UINT8)(tick >> 8), eventMark, rdBuff[0], rdBuff[1]);
								//str += STR_LINEFEED;
								//strMidiData += str;
							}
							else if ((eventMark & 0xF0) == 0xB0)//������
							{
								count += midiFile.Read(rdBuff, 2);
								//str.Empty();
								//str.Format(_T("// 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X,"), (UINT8)tick, (UINT8)(tick >> 8), eventMark, rdBuff[0], rdBuff[1]);
								//str += STR_LINEFEED;
								//strMidiData += str;

							}
							else if ((eventMark & 0xF0) == 0xC0)//�ı�����
							{
								count += midiFile.Read(rdBuff, 1);
								//str.Empty();
								//str.Format(_T("// 0x%02X, 0x%02X, 0x%02X, 0x%02X,"), (UINT8)tick, (UINT8)(tick >> 8), eventMark, rdBuff[0]);
								//str += STR_LINEFEED;
								//strMidiData += str;
							}
							else if ((eventMark & 0xF0) == 0xD0)//����ͨ��
							{
								count += midiFile.Read(rdBuff, 1);
								//str.Empty();
								//str.Format(_T("// 0x%02X, 0x%02X, 0x%02X,"), (UINT8)tick, (UINT8)(tick >> 8), eventMark, rdBuff[0]);
								//str += STR_LINEFEED;
								//strMidiData += str;
							}
							else if ((eventMark & 0xF0) == 0xE0)//����
							{
								count += midiFile.Read(rdBuff, 2);
								//str.Empty();
								//str.Format(_T("// 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X,"), (UINT8)tick, (UINT8)(tick >> 8), eventMark, rdBuff[0], rdBuff[0]);
								//str += STR_LINEFEED;
								//strMidiData += str;
							}
							else if (eventMark == 0xF0)//ϵͳ��
							{
								//�����ݳ���

								count += midiFile.Read(&byte, 1);
								for (i = 0; (byte > 0x7F) && (i < 5); i++)//�����ж���ֽ�
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
								case 0x00://���ù��������2�ֽ�
									count += midiFile.Read(rdBuff, 2);
									break;
								case 0x01://�ı���Ϣ�����ȿɱ�
										  //break;
								case 0x02://������Ȩ�����ȿɱ�
										  //break;
								case 0x03://��һ�γ��ֱ�ʾ���������⣬�ڶ��γ��ֱ�ʾ�����⣬���ȿɱ�
										  //break;
								case 0x04://�������ƣ����ȿɱ�
										  //break;
								case 0x05://��ʣ����ȿɱ�
										  //break;
								case 0x06://��ǣ����ȿɱ�
										  //break;
								case 0x07://��ʼ�㣬���ȿɱ�
										  //�����ݳ���
									count += midiFile.Read(&byte, 1);
									for (i = 0; (byte > 0x7F) && (i < 5); i++)//�����ж���ֽ�
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
								case 0x2F://���������ǣ�����0�ֽ�
									bChunkEnd = 1;
									count += midiFile.Read(rdBuff, 1);
									break;
								case 0x51://�ٶȣ��ķ�������΢����������3�ֽ�
									count += midiFile.Read(&byte, 1);//����
									count += midiFile.Read(rdBuff, byte & 0x7F);
									speed4 = ((UINT32)rdBuff[0] << 16) | ((UINT32)rdBuff[1] << 8) | ((UINT32)rdBuff[2] << 0);
									//str.Empty();
									//str.Format(_T("// 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X,"), (UINT8)tick, (UINT8)(tick >> 8), eventMark, eventType, rdBuff[0], rdBuff[1], rdBuff[2]);
									//str += STR_LINEFEED;
									//strMidiData += str;
									break;
								case 0x58://���ģ�����4�ֽ�
									count += midiFile.Read(&byte, 1);//����
									count += midiFile.Read(rdBuff, byte & 0x7F);
									//str.Empty();
									//str.Format(_T("// 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X,"), (UINT8)tick, (UINT8)(tick >> 8), eventMark, eventType, rdBuff[0], rdBuff[1], rdBuff[2], rdBuff[3]);
									//str += STR_LINEFEED;
									//strMidiData += str;
									timeSignature = rdBuff[0];
									timeSignature <<= 8;
									timeSignature |= rdBuff[1];
									break;
								case 0x59://���ţ�����2�ֽ�
									count += midiFile.Read(&byte, 1);//����
									count += midiFile.Read(rdBuff, byte & 0x7F);
									break;
								case 0x7F://������Ϣ�����ȿɱ�
									count += midiFile.Read(&byte, 1);//����
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
						strMidiName.Empty();//����ַ���
						str.Empty();

						str = m_CtrlList.GetItemText(line, 1);	//�ļ���
						CString str2;
						//str2.Format(_T("extern const unsigned char MidiEvent_%s[%d][5];\r\n"), str.GetBuffer(), eventCount + 2);
						//strArrayName += str2;
						str2.Empty();
						str2.Format(_T("&MidiEvent_%s[0][0],\r\n"),str.GetBuffer());
						strArrayPointer += str2;
						strMidiName.Format(_T("const unsigned char MidiEvent_%s[%d][5]=\r\n{\r\n"),str.GetBuffer(),eventCount + 2);
						str.Empty();
						str.Format(_T("//ǰ2���ֽ���һ���ķ�����tick������3���ֽ���һ���ķ�������΢���������ֽ���ǰ\r\n0x%02x, 0x%02x, 0x%02X, 0x%02X, 0x%02X,\r\n"), (UINT8)deltaTime, (UINT8)(deltaTime >> 8), (UINT8)speed4, (UINT8)(speed4 >> 8), (UINT8)(speed4 >> 16));
						strMidiName += str;
						str.Empty();
						str.Format(_T("//ǰ2���ֽ��¼���������3�ֽ��ǽ��ķ��ӣ���4�ֽ��ǽ��ķ�ĸ\r\n0x%02x, 0x%02x, 0x%02x, 0x%02x,    0,\r\n"), (UINT8)eventCount, (UINT8)(eventCount >> 8),(UINT8)(timeSignature>>8), (UINT8)(timeSignature & 0xFF));
						strMidiName += str;
						strOutFile += strMidiName + strMidiData + _T("};\r\n\r\n");
						break;//�����ļ���β
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
			MessageBox(_T("�޷����ļ�\r\n") + str, _T("����"), MB_OK | MB_ICONWARNING);
		}
		midiFile.Close();
	}
	outFile.Open(_T(OUT_FILE_NAME), CFile::modeCreate | CFile::modeWrite);
	//outFile.Write(STR_LINEFEED, STR_LINEFEED_SIZE);
	//outFile.Write(STR_LINEFEED, STR_LINEFEED_SIZE);
	outFile.Write(OUT_FILE_HEAD, sizeof(OUT_FILE_HEAD) - 1);
	//outFile.Write(STR_LINEFEED, STR_LINEFEED_SIZE);
	//outFile.Write(strArrayName.GetBuffer(), strArrayName.GetLength());
	//midi��Ϣ
	outFile.Write(STR_LINEFEED, STR_LINEFEED_SIZE);
	outFile.Write(STR_LINEFEED, STR_LINEFEED_SIZE);
	outFile.Write(strOutFile.GetBuffer(), strOutFile.GetLength());

	//midi�ļ������궨��
	outFile.Write(_T(MIDI_MAX_NUMBER_MACRO_NAME), sizeof(MIDI_MAX_NUMBER_MACRO_NAME) - 1);
	str.Empty();
	str.Format("%d", totalLine);
	outFile.Write(str.GetBuffer(), str.GetLength());
	outFile.Write(STR_LINEFEED, STR_LINEFEED_SIZE);
	outFile.Write(STR_LINEFEED, STR_LINEFEED_SIZE);

	//midi��������
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
	
	//GetDlgItem(IDC_STATIC)->SetWindowText("�����ɹ�");
	//if (MessageBox("������ɣ��Ƿ��˳���", "���", MB_YESNO | MB_ICONQUESTION) == IDYES)
	//{
	//	SendMessage(WM_CLOSE);
	//	//PostQuitMessage(0);
	//}
}



void CMIDI2CDlg::OnBnClickedBuaddfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
				//	����ļ���Ϣ���б�
				
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
				g_lvItem.pszText = buff;						//	���
				int itemNo;
				itemNo = m_CtrlList.InsertItem(&g_lvItem);

				CString str = FileName;
				str = str.Left(str.GetLength() - 4);
				//int len = str.Find(" - 01 - �ϳ��� - AD Drums Master", 0);
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
				m_CtrlList.SetItemText(itemNo, 1, fn);			//	�ļ���
#ifdef UNICODE
				fn = (WCHAR *)fPath.GetBuffer(fPath.GetLength());
#else
				fn = (char *)fPath.GetBuffer(fPath.GetLength());
#endif
				m_CtrlList.SetItemText(itemNo, 2, fn);			//	�ļ�·��
				str.Empty();
				str.Format(_T("��%d���ļ�"), m_CtrlList.GetItemCount());
				GetDlgItem(IDC_STATIC)->SetWindowText(str);
			}
		}
	}
}


void CMIDI2CDlg::OnBnClickedBuclearlist()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_CtrlList.DeleteAllItems();
	GetDlgItem(IDC_STATIC)->SetWindowText(_T("�����"));
}

