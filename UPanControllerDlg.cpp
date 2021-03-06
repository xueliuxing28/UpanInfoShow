
// UPanControllerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "UPanController.h"
#include "UPanControllerDlg.h"
#include "afxdialogex.h"
#include"dbt.h"
//#include "ioapiset.h"
#include"winioctl.h"
#include "DestoryUPan.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
enum
{
	DiskSize_B = 0,
	DiskSize_K = 1,
	DiskSize_M = 2,
	DiskSize_G = 3,
	DiskSize_T = 4,
};
enum
{
	GDI_VOLUMENAME = 0,
	GDI_VOLUMESERIALNUMBER = 1,
	GDI_VOLUMEFILESYSTEM = 2,
	GDI_VOLUMETYPE = 3,
	GDI_VOLUMESIZE = 4,
	GDI_VOLUMEFREESIZE = 5,
};

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
CString GetDiskSize(ULONGLONG nSize, int nType);
CString GetDriverInfomation(BYTE bAlpha, int iGTI_TYPE);
CString GetDiskSize(ULONGLONG nSize, int nType)
{
	CString tmp;
	if (nType == DiskSize_B)
	{
		ULONGLONG nG, nM, nK, nB, nKB, nMKB, nT, nGMKB;
		nT = 0;
		//nT = nSize/(ULONGLONG)(1024*1024*1024*1024);
		//nGMKB =  nSize%(ULONGLONG)(1024*1024*1024*1024);
		nG = nSize / (ULONGLONG)(1000 * 1000 * 1000);
		nMKB = nSize % (ULONGLONG)(1000 * 1000 * 1000);
		nM = nMKB / (ULONGLONG)(1000 * 1000);
		nKB = nMKB % (ULONGLONG)(1000 * 1000);
		nK = nKB / (ULONGLONG)(1000);
		nB = nKB % (ULONGLONG)(1000);

		if ((int)nT != 0)
		{
			tmp.Format(L"%d,%03d,%03d,%03d,%03d B", (int)nT, (int)nG, (int)nM, (int)nK, (int)nB);
		}
		else if ((int)nT == 0 && (int)nG != 0)
		{
			tmp.Format(L"%d,%03d,%03d,%03d B", (int)nG, (int)nM, (int)nK, (int)nB);
		}
		else if ((int)nT == 0 && (int)nG == 0 && (int)nM != 0)
		{
			tmp.Format(L"%d,%03d,%03d B", (int)nM, (int)nK, (int)nB);
		}
		else if ((int)nT == 0 && (int)nG == 0 && (int)nM == 0 && (int)nK != 0)
		{
			tmp.Format(L"%d,%03d B", (int)nK, (int)nB);
		}
		else if ((int)nT == 0 && (int)nG == 0 && (int)nM == 0 && (int)nK == 0 && (int)nB != 0)
		{
			tmp.Format(L"%d B", (int)nB);
		}
		else
		{
			tmp.Format(L"0 B");
		}
	}
	else if (nType == DiskSize_K)
	{
		ULONGLONG nG, nM, nK, nB, nKB, nMKB, nT, nGMKB;
		nT = 0;
		//nT = nSize/(ULONGLONG)(1024*1024*1024*1024);
		//nGMKB =  nSize%(ULONGLONG)(1024*1024*1024*1024);
		nG = nSize / (ULONGLONG)(1000 * 1000 * 1024);
		nMKB = nSize % (ULONGLONG)(1000 * 1000 * 1024);
		nM = nMKB / (ULONGLONG)(1000 * 1024);
		nKB = nMKB % (ULONGLONG)(1000 * 1024);
		nK = nKB / (ULONGLONG)(1024);
		nB = nKB % (ULONGLONG)(1024);

		if ((int)nT != 0)
		{
			tmp.Format(L"%d,%03d,%03d,%03d.%02d K", (int)nT, (int)nG, (int)nM, (int)nK, (int)(((float)(int)nB) / 10.24));
		}
		else if ((int)nT == 0 && (int)nG != 0)
		{
			tmp.Format(L"%d,%03d,%03d.%02d K", (int)nG, (int)nM, (int)nK, (int)(((float)(int)nB) / 10.24));
		}
		else if ((int)nT == 0 && (int)nG == 0 && (int)nM != 0)
		{
			tmp.Format(L"%d,%03d.%02d K", (int)nM, (int)nK, (int)(((float)(int)nB) / 10.24));
		}
		else if ((int)nT == 0 && (int)nG == 0 && (int)nM == 0 && (int)nK != 0)
		{
			tmp.Format(L"%d.%02d K", (int)nK, (int)(((float)(int)nB) / 10.24));
		}
		else if ((int)nT == 0 && (int)nG == 0 && (int)nM == 0 && (int)nK == 0 && (int)nB != 0)
		{
			tmp.Format(L"0.%02d K", (int)(((float)(int)nB) / 10.24));
		}
		else
		{
			tmp.Format(L"0.0 K");
		}
	}
	else if (nType == DiskSize_M)
	{
		ULONGLONG nG, nM, nK, nB, nKB, nMKB, nT, nGMKB;
		nT = 0;
		//nT = nSize/(ULONGLONG)(1024*1024*1024*1024);
		//nGMKB =  nSize%(ULONGLONG)(1024*1024*1024*1024);
		nG = nSize / (ULONGLONG)(1000 * 1024 * 1024);
		nMKB = nSize % (ULONGLONG)(1000 * 1024 * 1024);
		nM = nMKB / (ULONGLONG)(1024 * 1024);
		nKB = nMKB % (ULONGLONG)(1024 * 1024);
		nK = nKB / (ULONGLONG)(1024);
		nB = nKB % (ULONGLONG)(1024);

		if ((int)nT != 0)
		{
			tmp.Format(L"%d,%03d,%03d.%02d M", (int)nT, (int)nG, (int)nM, (int)(((float)(int)nK) / 10.24));
		}
		else if ((int)nT == 0 && (int)nG != 0)
		{
			tmp.Format(L"%d,%03d.%02d M", (int)nG, (int)nM, (int)(((float)(int)nK) / 10.24));
		}
		else if ((int)nT == 0 && (int)nG == 0 && (int)nM != 0)
		{
			tmp.Format(L"%d.%02d M", (int)nM, (int)(((float)(int)nK) / 10.24));
		}
		else if ((int)nT == 0 && (int)nG == 0 && (int)nM == 0 && (int)nK != 0)
		{
			tmp.Format(L"0.%02d M", (int)(((float)(int)nK) / 10.24));
		}
		else
		{
			tmp.Format(L"0.0 K");
		}
	}
	else if (nType == DiskSize_G)
	{
		ULONGLONG nG, nM, nK, nB, nKB, nMKB, nT, nGMKB;
		nT = 0;
		//nT = nSize/(ULONGLONG)(1024*1024*1024*1024);
		//nGMKB =  nSize%(ULONGLONG)(1024*1024*1024*1024);
		nG = nSize / (ULONGLONG)(1024 * 1024 * 1024);
		nMKB = nSize % (ULONGLONG)(1024 * 1024 * 1024);
		nM = nMKB / (ULONGLONG)(1024 * 1024);
		nKB = nMKB % (ULONGLONG)(1024 * 1024);
		nK = nKB / (ULONGLONG)(1024);
		nB = nKB % (ULONGLONG)(1024);

		if ((int)nT != 0)
		{
			tmp.Format(L"%d,%03d.%02d G", (int)nT, (int)nG, (int)(((float)(int)nM) / 10.24));
		}
		else if ((int)nT == 0 && (int)nG != 0)
		{
			tmp.Format(L"%d.%02d G", (int)nG, (int)(((float)(int)nM) / 10.24));
		}
		else if ((int)nT == 0 && (int)nG == 0 && (int)nM != 0)
		{
			tmp.Format(L"0.%02d G", (int)(((float)(int)nM) / 10.24));
		}
		else
		{
			tmp.Format(L"0.0 G");
		}
	}
	else if (nType == DiskSize_T)
	{
		ULONGLONG nG, nM, nK, nB, nKB, nMKB, nT, nGMKB;
		nT = 0;
		//nT = nSize/(ULONGLONG)(1024*1024*1024*1024);
		//nGMKB =  nSize%(ULONGLONG)(1024*1024*1024*1024);
		nG = nSize / (ULONGLONG)(1024 * 1024 * 1024);
		nMKB = nSize % (ULONGLONG)(1024 * 1024 * 1024);
		nM = nMKB / (ULONGLONG)(1024 * 1024);
		nKB = nMKB % (ULONGLONG)(1024 * 1024);
		nK = nKB / (ULONGLONG)(1024);
		nB = nKB % (ULONGLONG)(1024);

		if ((int)nT != 0)
		{
			tmp.Format(L"%d.%03d T", (int)nT, (int)nG);
		}
		else if ((int)nT == 0 && (int)nG != 0)
		{
			tmp.Format(L"0.%03d G", (int)nG);
		}
		else
		{
			tmp.Format(L"0.0 G");
		}
	}
	return tmp;
}

CString GetDriverInfomation(BYTE bAlpha, int iGTI_TYPE)
{
	CString strResult = _T("");

	if (!::IsCharAlpha((TCHAR)bAlpha))
	{
		strResult = _T("驱动器参数无效!");
		return strResult;
	}
	else
	{
		/**********获取驱动器名字、序列号和文件系统部分**********/
		CString strRootPathName;
		strRootPathName.Format(_T("%c:\\"), bAlpha);
		LPCTSTR lpRootPathName = strRootPathName;
		LPTSTR lpVolumeNameBuffer = new wchar_t[_MAX_FNAME];
		DWORD nVolumeNameSize = _MAX_FNAME;
		DWORD nVolumeSerialNumber = 0;//便于驱动器无效时做判断
		DWORD nMaximumComponentLength;
		DWORD nFileSystemFlags;
		LPTSTR lpFileSystemNameBuffer = new wchar_t[20];//文件系统(NTFS,FAT)多大有定义好的宏吗
		DWORD nFileSystemNameSize = 20;
		GetVolumeInformation(
			lpRootPathName,
			lpVolumeNameBuffer,
			nVolumeNameSize,
			&nVolumeSerialNumber,
			&nMaximumComponentLength,
			&nFileSystemFlags,
			lpFileSystemNameBuffer,
			nFileSystemNameSize);

		/**********获取驱动器类型部分**********/
		CString strDriveType;

		/**********获取驱动器总大小和剩余大小部分**********/
		LPCTSTR lpDirectoryName = new wchar_t[2];
		lpDirectoryName = (LPCTSTR)strRootPathName.Mid(0, 2);
		_ULARGE_INTEGER FreeBytesAvailable, TotalNumberOfBytes, TotalNumberOfFreeBytes;

		__int64 iVolumeSize = 0, iVolumeFreeSize = 0;

		GetDiskFreeSpaceEx(strRootPathName.Mid(0, 2), &FreeBytesAvailable, &TotalNumberOfBytes, &TotalNumberOfFreeBytes);
		iVolumeSize = TotalNumberOfBytes.QuadPart / 1024 / 1024;
		iVolumeFreeSize = FreeBytesAvailable.QuadPart / 1024 / 1024;

		/**********根据参数得出对应的驱动器信息**********/
		switch (iGTI_TYPE)
		{
		case GDI_VOLUMENAME:
			if (lpVolumeNameBuffer != NULL)
				strResult.Format(_T("驱动器 %c 的名字为:%s."), bAlpha, lpVolumeNameBuffer);
			else
				strResult.Format(_T("驱动器 %c 的名字为:%s."), bAlpha, lpVolumeNameBuffer);
			//strResult.Format(_T("获取驱动器名字失败!"));
			break;
		case GDI_VOLUMESERIALNUMBER:
			if (nVolumeSerialNumber != 0)
				strResult.Format(_T("驱动器 %c 的序列号为:%X."), bAlpha, nVolumeSerialNumber);
			else
				strResult.Format(_T("获取驱动器序列号失败!"));
			break;
		case GDI_VOLUMEFILESYSTEM:
			if (lpFileSystemNameBuffer != NULL)
				strResult.Format(_T("驱动器 %c 的文件系统为:%s."), bAlpha, lpFileSystemNameBuffer);
			else
				strResult.Format(_T("获取驱动器文件系统失败!"));
			break;
		case GDI_VOLUMESIZE:
			if (iVolumeSize != 0)
				strResult.Format(_T("驱动器 %c 的总大小为:%.2fGB."), bAlpha, (float)iVolumeSize / 1024);
			else
				strResult.Format(_T("获取驱动器总大小失败!"));
			break;
		case GDI_VOLUMEFREESIZE:
			if (iVolumeFreeSize != 0)
				strResult.Format(_T("驱动器 %c 的剩余大小为:%.2fGB."), bAlpha, (float)iVolumeFreeSize / 1024);
			else
				strResult.Format(_T("获取驱动器剩余大小失败!"));
			break;
		case GDI_VOLUMETYPE:
			switch (GetDriveType(lpRootPathName))
			{
			case DRIVE_UNKNOWN:
				strDriveType = _T("Unknown Type!");
				break;
			case DRIVE_NO_ROOT_DIR:
				strResult = _T("获取驱动器类型时参数设置错误!");
				return strResult;
			case DRIVE_REMOVABLE:
				strDriveType = _T("Removable Disk");
				break;
			case DRIVE_FIXED:
				strDriveType = _T("Hard Disk");
				break;
			case DRIVE_REMOTE:
				strDriveType = _T("Remote Device");
				break;
			case DRIVE_CDROM:
				strDriveType = _T("CD");
				break;
			case DRIVE_RAMDISK:
				strDriveType = _T("RAM");
				break;
			default:
				strResult = _T("Unknown Mistake!");
				return strResult;
			}
			strResult.Format(_T("Driver %c Of Type:%s."), bAlpha, strDriveType);
			break;
		default:
			strResult = _T("获取驱动器信息时参数设置错误!");
			break;
		}

	}

	/**********返回所要求的驱动器的信息**********/
	return strResult;
}
TCHAR FirstDriveFromMask(ULONG unitmask)
{
	char i;
	for (i = 0; i < 26; ++i)
	{
		if (unitmask & 0x1)//看该驱动器的状态是否发生了变化  
			break;
		unitmask = unitmask >> 1;
	}
	return (i + 'A');
}
bool CUPanControllerDlg::RemoveUSB(CString csDisk)
{
	HANDLE hDevice; // handle to the drive to be examined 
	BOOL bResult; // results flag 
	DWORD junk; // discard results 
	DWORD dwError;
	CString csVolume;
	int nPos = csDisk.Find('\\');//csDisk like "H:\"
	if (-1 != nPos)
	{
		csDisk = csDisk.Left(nPos);
	}
	csVolume.Format(L"\\\\.\\%s", csDisk);
	// Open the volume 
	hDevice = CreateFile(csVolume, // drive to open 
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, // share mode 
		NULL, // default security attributes 
		OPEN_EXISTING, // disposition 
		0, // file attributes 
		NULL); // don't copy any file's attributes 

	if (hDevice == INVALID_HANDLE_VALUE) // can't open the drive 
	{
		dwError = GetLastError();
		return FALSE;
	}

	//Dismount the volume 
	bResult = DeviceIoControl(
		hDevice, // handle to volume 
		IOCTL_STORAGE_EJECT_MEDIA, //eject USB
		NULL, // lpInBuffer 
		0, // nInBufferSize 
		NULL, // lpOutBuffer 
		0, // nOutBufferSize 
		&junk, // discard count of bytes returned 
		(LPOVERLAPPED)NULL); // synchronous I/O 
	if (!bResult) // IOCTL failed 
	{
		dwError = GetLastError();
	}

	// Close the volume handle 
	bResult = CloseHandle(hDevice);
	if (!bResult)
	{
		dwError = GetLastError();
	}

	return FALSE;

}

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


// CUPanControllerDlg 对话框
LRESULT CUPanControllerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	switch (message)
	{
		//WM_DEVICECHANGE，系统硬件改变发出的系统消息
	case WM_DEVICECHANGE:
	{
		PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
		switch (wParam)
		{
		case WM_DEVICECHANGE:
			break;
		case DBT_DEVICEARRIVAL://DBT_DEVICEARRIVAL，设备检测结束，并且可以使用
		{
			if (lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)//逻辑卷
			{
				PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
				switch (lpdbv->dbcv_flags)
				{
				case 0:                //U盘
				{
					CString decDriver;
					decDriver = FirstDriveFromMask(lpdbv->dbcv_unitmask);
					DWORD sizeStruct = lpdbv->dbcv_size;
// 					if (a==1)
// 						{
// 							CString strDisk;
// 							strDisk.Format(L"%c:\\", FirstDriveFromMask(lpdbv->dbcv_unitmask));
// 							RemoveUSB(strDisk);
// 							AfxMessageBox(strDisk);
// 						}
					ULARGE_INTEGER FreeAv, TotalBytes, FreeBytes;
					if (GetDiskFreeSpaceEx(decDriver + L":\\", &FreeAv, &TotalBytes, &FreeBytes))
					{
						CString strTotalBytes = GetDiskSize(TotalBytes.QuadPart, DiskSize_B);
						CString strFreeBytes = GetDiskSize(FreeBytes.QuadPart, DiskSize_B);
						CString strFreeAV = GetDiskSize(TotalBytes.QuadPart - FreeAv.QuadPart, DiskSize_B);
						CString strTG = GetDiskSize(TotalBytes.QuadPart, DiskSize_G);
						CString strFG = GetDiskSize(FreeBytes.QuadPart, DiskSize_G);
						CString strYG = GetDiskSize(TotalBytes.QuadPart - FreeAv.QuadPart, DiskSize_G);
						CString strname = GetDriverInfomation(decDriver.GetAt(0), GDI_VOLUMENAME);
						CString strSeries = GetDriverInfomation(decDriver.GetAt(0), GDI_VOLUMESERIALNUMBER);
						CString strfilsystem = GetDriverInfomation(decDriver.GetAt(0), GDI_VOLUMEFILESYSTEM);
						CString strAllInfo;
						strAllInfo.Format(L"驱动器:[%s] \n容量：%s (%s)\n已用空间：%s (%s)\n可用空间: %s (%s)\n%s\n%s\n%s",
							decDriver + L":\\", strTotalBytes, strTG, strFreeAV, strYG, strFreeBytes, strFG, strname, strSeries, strfilsystem
						);/* 单位为G */
						AfxMessageBox(strAllInfo);
					}
					/*CString tmp;
					tmp.Format(L"检测到U盘:[%s]插入! %ld bytes\n",decDriver.GetBuffer(0),sizeStruct);
					AfxMessageBox(tmp);*/
				}
				break;
				case DBTF_MEDIA:    //光盘
					CString tmp;
					tmp.Format(L"检测到光盘:[%c]插入!\n", FirstDriveFromMask(lpdbv->dbcv_unitmask));
					AfxMessageBox(tmp);
					break;
				}
			}
		}
		break;
		case DBT_DEVICEREMOVECOMPLETE://DBT_DEVICEREMOVECOMPLETE,设备卸载或者拔出
		{
			if (lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)//逻辑卷
			{
				PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
				switch (lpdbv->dbcv_flags)
				{
				case 0:                //U盘
				{
					CString decDriver;
					decDriver = FirstDriveFromMask(lpdbv->dbcv_unitmask);
					CString tmp;
					tmp.Format(L"检测到U盘:[%s]拔出!\n", decDriver.GetBuffer(0));
					AfxMessageBox(tmp);
				}
				break;
				case DBTF_MEDIA:    //光盘

					break;
				}
			}
		}
		break;
		}
	}
	break;
	}
	return CDialogEx::DefWindowProc(message, wParam, lParam);
}


CUPanControllerDlg::CUPanControllerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UPANCONTROLLER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUPanControllerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUPanControllerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CUPanControllerDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CUPanControllerDlg 消息处理程序

BOOL CUPanControllerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUPanControllerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUPanControllerDlg::OnPaint()
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
HCURSOR CUPanControllerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUPanControllerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}
