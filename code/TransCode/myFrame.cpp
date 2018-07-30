// myFrame.cpp : 实现文件
//
#include "stdafx.h"
#include "TransCode.h"
#include "myFrame.h"
#include "myLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// myFrame 对话框




myFrame::myFrame(CWnd* pParent /*=NULL*/)
: CDialog(myFrame::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void myFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SrcSelect, m_srcSelect);
	DDX_Control(pDX, IDC_DestSelect, m_destSelect);
	DDX_Control(pDX, IDC_SrcEdit, m_srcEdit);
	DDX_Control(pDX, IDC_DestEdit, m_destEdit);
	DDX_Control(pDX, IDC_Rate, m_rate);
	
}

BEGIN_MESSAGE_MAP(myFrame, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SrcBroseBn, &myFrame::OnBnClickedSrcBrose)
	ON_BN_CLICKED(IDC_DestBroseBn, &myFrame::OnBnClickedDestBrose)
	ON_BN_CLICKED(IDC_CancleBn, &myFrame::OnBnClickedCancelTrans)
	ON_BN_CLICKED(IDCANCEL, &myFrame::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_TransBn, &myFrame::OnBnClickedTransbn)
	ON_CBN_SELCHANGE(IDC_SrcSelect, &myFrame::OnCbnSrcSelect)
	ON_CBN_SELCHANGE(IDC_DestSelect, &myFrame::OnCbnDestSelect)
	ON_WM_TIMER()

END_MESSAGE_MAP()


// myFrame 消息处理程序

BOOL myFrame::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_myFlag=0;
	m_srcSelect.AddString("UTF-8");
	m_srcSelect.AddString("Unicode");;
	m_destSelect.AddString("UTF-8");
	m_destSelect.AddString("Unicode");

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void myFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void myFrame::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR myFrame::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void myFrame::OnBnClickedSrcBrose()
{

	TCHAR path[MAX_PATH] = {0};   
	CString str;
	OPENFILENAME of= {0};   
	of.lStructSize = sizeof(of);   
	of.hwndOwner = m_hWnd;   
	of.lpstrFilter = _T("txt文件(*.txt)\0*.txt\0"); 
	of.lpstrFile = path; 
	of.nMaxFile = sizeof(path)/sizeof(*path);   
	of.nFilterIndex = 0;   
	of.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER ;
	BOOL bSel = GetOpenFileName(&of);   

	str.Format(path);
	m_srcEdit.SetWindowText(str);
	m_src=str;
}

void myFrame::OnBnClickedDestBrose()
{
	char path[MAX_PATH];
	CString str;

	ZeroMemory(path, sizeof(path));   
	BROWSEINFO bi;   
	bi.hwndOwner = m_hWnd;  
	bi.pidlRoot = NULL;   
	bi.pszDisplayName = path;   
	bi.lpszTitle = "选择目录："; 
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;  
	bi.lpfn = NULL;   
	bi.lParam = 0;   
	bi.iImage = 0;   
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);   
	if(lp && SHGetPathFromIDList(lp, path))   
	{
		str.Format(path);
		m_destEdit.SetWindowText(str);
		m_dest=str;
	}
}


void myFrame::OnBnClickedCancelTrans()
{
	if (m_myFlag==1)
	{
		AfxMessageBox("取消");
		LOG4CPLUS_INFO(logger,"取消");
		if (m_fun->m_thdOper!= NULL)
		{
			m_fun->terminateThd();
		}
		m_myFlag=0;
	}
	
}

void myFrame::OnBnClickedCancel()
{
	OnCancel();
}


void myFrame::OnBnClickedTransbn()
{
	SetTimer(1, 1000, NULL); 
	m_myFlag=1;
	if (m_src.empty()||m_srcCode.empty()||m_dest.empty()||m_destCode.empty())
	{
		LOG4CPLUS_WARN(logger,"路径名或编码格式未填写");
		AfxMessageBox("路径名或编码格式未填写");
	}
	else{
		m_srcPath=m_src;
		m_fileName = m_srcPath.substr(m_srcPath.find_last_of("\\") + 1);
		m_destPath=m_dest+"trans_"+m_fileName;
		if (m_srcCode==m_destCode)
		{	
			LOG4CPLUS_WARN(logger,"源文件与目标文件编码相同");
			AfxMessageBox("源文件与目标文件编码相同");
		}
		else{
			m_fun = new function(m_srcPath,m_srcCode,m_destPath,m_destCode) ;
			if(!m_fun->transAll())
			{
				m_lastErrorInfo =m_fun->getLastErrInfo();
				LOG4CPLUS_ERROR(logger,m_lastErrorInfo);
				AfxMessageBox( ("转码失败:"+m_lastErrorInfo).c_str());
			}
				
		}
	}
}


void myFrame::OnCbnSrcSelect()
{
	int index=((CComboBox*)GetDlgItem(IDC_SrcSelect))->GetCurSel();
	CString str;
	((CComboBox*)GetDlgItem(IDC_SrcSelect))->GetLBText(index,str);
	m_srcCode=str;
}


void myFrame::OnCbnDestSelect()
{
	int index=((CComboBox*)GetDlgItem(IDC_DestSelect))->GetCurSel();
	CString str;
	((CComboBox*)GetDlgItem(IDC_DestSelect))->GetLBText(index,str);
	m_destCode=str;
}

void myFrame::OnTimer(UINT_PTR nIDEvent)
{
		int rate = m_fun->getRate();
		stringstream stream;  
		stream<<rate;
		CString s = CString((stream.str() + (string)"%").c_str());
		m_rate.SetWindowText(s);
		UpdateWindow();
		
		if (rate==100)
		{
			AfxMessageBox("转码成功");
			KillTimer(1);
			if (m_fun->m_thdOper!= NULL)
			{
				m_fun->terminateThd();
			}
			m_myFlag=0;
		}

		CDialog::OnTimer(nIDEvent);
}
