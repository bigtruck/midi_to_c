
// MIDI2CDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CMIDI2CDlg �Ի���
class CMIDI2CDlg : public CDialogEx
{
// ����
public:
	CMIDI2CDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MIDI2C_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	LVITEM g_lvItem;
	int g_nItem;
	afx_msg void OnBnClickedBuscanfile();
	afx_msg void OnBnClickedBucreate();
	afx_msg void OnBnClickedBuopenpath();
	void mFindFile(CString dir);
	CListCtrl m_CtrlList;
	afx_msg void OnBnClickedBuaddfile();
	afx_msg void OnBnClickedBuclearlist();
};
