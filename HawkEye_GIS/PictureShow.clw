; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPictureShowView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PictureShow.h"
LastPage=0

ClassCount=6
Class1=CPictureShowApp
Class2=CPictureShowDoc
Class3=CPictureShowView
Class4=CMainFrame

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_ABOUTBOX (English (U.S.))
Resource4=IDR_MAINFRAME (English (U.S.))
Class6=CAssociationsDlg
Resource5=IDR_FULLSCREEN
Resource6=IDD_ASSOCIATIONS

[CLS:CPictureShowApp]
Type=0
HeaderFile=PictureShow.h
ImplementationFile=PictureShow.cpp
Filter=N
LastObject=CPictureShowApp

[CLS:CPictureShowDoc]
Type=0
HeaderFile=PictureShowDoc.h
ImplementationFile=PictureShowDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CPictureShowDoc

[CLS:CPictureShowView]
Type=0
HeaderFile=PictureShowView.h
ImplementationFile=PictureShowView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=ID_APP_ABOUT


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_VIEW_TOOLBAR
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=PictureShow.cpp
ImplementationFile=PictureShow.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
CommandCount=16
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command16=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=14
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE


[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE_AS
Command3=ID_FILE_PRINT
Command4=ID_APP_ABOUT
Command5=ID_BUTTON_FULLSCREEN
Command6=ID_BUTTON_FITTOSCREEN
Command7=ID_BUTTON_DIMINISH
Command8=ID_BUTTON_MAGNIFY
Command9=ID_BUTTON_PREV
Command10=ID_BUTTON_NEXT
CommandCount=10

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE_AS
Command3=ID_FILE_PRINT
Command4=ID_FILE_PRINT_PREVIEW
Command5=ID_FILE_PRINT_SETUP
Command6=ID_APP_EXIT
Command7=ID_VIEW_TOOLBAR
Command8=ID_VIEW_STATUS_BAR
Command9=ID_OPTIONS_FULLSCREEN
Command10=ID_OPTIONS_NEXTPICTURE
Command11=ID_OPTIONS_PREVIOUSPICTURE
Command12=ID_OPTIONS_ASSOCIATEFILEEXTENTIONS
Command13=ID_OPTIONS_FITBORDERSTOPICTURE
Command14=ID_OPTIONS_FITTOSCREEN
Command15=ID_APP_ABOUT
Command16=ID_HELP_HOMEPAGE
CommandCount=16

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_OPTIONS_ASSOCIATEFILEEXTENTIONS
Command2=ID_OPTIONS_FITBORDERSTOPICTURE
Command3=ID_EDIT_COPY
Command4=ID_OPTIONS_FULLSCREEN
Command5=ID_FILE_OPEN
Command6=ID_FILE_PRINT
Command7=ID_FILE_SAVE_AS
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_NEXT_PANE
Command12=ID_PREV_PANE
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_CUT
Command16=ID_EDIT_UNDO
CommandCount=16

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=12
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308481
Control3=IDC_STATIC,static,1342308353
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342312449
Control6=IDC_STATIC,static,1342177283
Control7=IDC_STATIC,static,1342177283
Control8=IDC_STATIC,static,1342177283
Control9=IDC_STATIC,static,1342177283
Control10=IDC_STATIC,static,1342177283
Control11=IDC_STATIC,static,1342177283
Control12=IDC_STATIC,static,1342177283

[DLG:IDD_ASSOCIATIONS]
Type=1
Class=CAssociationsDlg
ControlCount=14
Control1=IDC_CHECK_ALL,button,1342242819
Control2=IDC_CHECK_BMP,button,1342242819
Control3=IDC_CHECK_DIB,button,1342242819
Control4=IDC_CHECK_EMF,button,1342242819
Control5=IDC_CHECK_GIF,button,1342242819
Control6=IDC_CHECK_ICO,button,1342242819
Control7=IDC_CHECK_JPG,button,1342242819
Control8=IDC_CHECK_WMF,button,1342242819
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_BUTTON_ASSOCIATE,button,1342242816
Control12=IDCANCEL,button,1342242816
Control13=IDC_STATIC,button,1342177287
Control14=IDC_BUTTON_CLEAR,button,1342242816

[CLS:CAssociationsDlg]
Type=0
HeaderFile=AssociationsDlg.h
ImplementationFile=AssociationsDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAssociationsDlg
VirtualFilter=dWC

[TB:IDR_FULLSCREEN]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE_AS
Command3=ID_FILE_PRINT
Command4=ID_APP_ABOUT
Command5=ID_BUTTON_FULLSCREEN_FLOAT
Command6=ID_BUTTON_FITTOSCREEN
Command7=ID_BUTTON_DIMINISH
Command8=ID_BUTTON_MAGNIFY
Command9=ID_BUTTON_PREV
Command10=ID_BUTTON_NEXT
CommandCount=10

