
// UPanControllerDlg.h: 头文件
//

#pragma once


// CUPanControllerDlg 对话框
class CUPanControllerDlg : public CDialogEx
{
// 构造
public:
	CUPanControllerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPANCONTROLLER_DIALOG };
#endif

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
	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	bool RemoveUSB(CString csDisk);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
