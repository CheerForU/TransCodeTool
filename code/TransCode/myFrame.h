// myFrame.h : 头文件
//
#pragma once
#include "function.h"
#include "Resource.h"
#include "myLog.h"
using namespace std;
// myFrame 对话框
class myFrame : public CDialog
{
	// 构造
public:
	myFrame(CWnd* pParent = NULL);	// 标准构造函数

	// 对话框数据
	enum { IDD = IDD_TRANSCODE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSrcBrose();
	afx_msg void OnBnClickedDestBrose();
	afx_msg void OnBnClickedCancelTrans();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedTransbn();
	afx_msg void OnCbnSrcSelect();
	afx_msg void OnCbnDestSelect();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CComboBox m_srcSelect;
	CComboBox m_destSelect;
	string m_src;
	string m_srcPath;
	string m_dest;
	string m_destPath;
	string m_fileName;
	string m_srcCode;
	string m_destCode;
	CEdit m_srcEdit;
	CEdit m_destEdit;
	CStatic m_rate;
	function *m_fun;
	int m_myFlag;
	string m_lastErrorInfo;
};