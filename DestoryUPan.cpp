// DestoryUPan.cpp: 实现文件
//

#include "stdafx.h"
#include "UPanController.h"
#include "DestoryUPan.h"
#include "afxdialogex.h"


// DestoryUPan 对话框

IMPLEMENT_DYNAMIC(DestoryUPan, CDialogEx)

DestoryUPan::DestoryUPan(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UPANCONTROLLER_DIALOG, pParent)
{

}

DestoryUPan::~DestoryUPan()
{
}

void DestoryUPan::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DestoryUPan, CDialogEx)
END_MESSAGE_MAP()


// DestoryUPan 消息处理程序
