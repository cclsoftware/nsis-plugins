!ifndef __nsResize_NSH__
!define __nsResize_NSH__

!macro __nsResize_AddParent Id X Y W H
  GetDlgItem $R0 $HWNDPARENT ${Id}
  nsResize::Add $R0 ${X} ${Y} ${W} ${H}
!macroend

!macro __nsResize_AddChild Id X Y W H
  GetDlgItem $R1 $R0 ${Id}
  nsResize::Add $R1 ${X} ${Y} ${W} ${H}
!macroend

!macro _nsResize_Header AddWidth AddHeight

  !ifdef MUI_HEADERIMAGE
    nsResize::Add $mui.Header.Image 0 0 -16u -5u
    !ifndef MUI_HEADERIMAGE_RIGHT
      ${If} $(^RTL) == 1
        nsResize::Add $mui.Header.Text 0 0 -${AddWidth} 0
        nsResize::Add $mui.Header.SubText 0 0 -${AddWidth} 0
      ${Else}
        nsResize::Add $mui.Header.Text ${AddWidth} 0 -${AddWidth} 0
        nsResize::Add $mui.Header.SubText ${AddWidth} 0 -${AddWidth} 0
      ${EndIf}
    !else
      ${If} $(^RTL) == 1
        nsResize::Add $mui.Header.Text ${AddWidth} 0 -${AddWidth} 0
        nsResize::Add $mui.Header.SubText ${AddWidth} 0 -${AddWidth} 0
      ${Else}
        nsResize::Add $mui.Header.Text 0 0 -${AddWidth} 0
        nsResize::Add $mui.Header.SubText 0 0 -${AddWidth} 0
      ${EndIf}
    !endif
  !endif

!macroend
!define nsResize_Header `!insertmacro _nsResize_Header`

!macro _nsResize_Window AddWidth AddHeight

  !insertmacro _nsResize_Header ${AddWidth} ${AddHeight}
  Push $R0
  !ifndef __nsResize_HalfSizeVars_Declared
    !define __nsResize_HalfSizeVars_Declared
    Var /GLOBAL _nsResize_HalfWidth
    Var /GLOBAL _nsResize_HalfHeight
  !endif
  IntOp $_nsResize_HalfWidth ${AddWidth} / 2
  IntOp $_nsResize_HalfHeight ${AddHeight} / 2
  nsResize::Add $HWNDPARENT -$_nsResize_HalfWidth -$_nsResize_HalfHeight ${AddWidth} ${AddHeight}
  ${If} $(^RTL) == 1
    !insertmacro __nsResize_AddParent 3 0 ${AddHeight} 0 0
    !insertmacro __nsResize_AddParent 1 0 ${AddHeight} 0 0
    !insertmacro __nsResize_AddParent 2 0 ${AddHeight} 0 0
  ${Else}
    !insertmacro __nsResize_AddParent 3 ${AddWidth} ${AddHeight} 0 0
    !insertmacro __nsResize_AddParent 1 ${AddWidth} ${AddHeight} 0 0
    !insertmacro __nsResize_AddParent 2 ${AddWidth} ${AddHeight} 0 0
    !insertmacro __nsResize_AddParent 1039 ${AddWidth} 0 0 0
  ${EndIf}
  !insertmacro __nsResize_AddParent 1018 0 0 ${AddWidth} ${AddHeight}
  !insertmacro __nsResize_AddParent 1044 0 0 ${AddWidth} ${AddHeight}
  !insertmacro __nsResize_AddParent 1035 0 ${AddHeight} ${AddWidth} 0
  !insertmacro __nsResize_AddParent 1036 0 -5u ${AddWidth} 0
  !insertmacro __nsResize_AddParent 1045 0 ${AddHeight} ${AddWidth} 0
  !insertmacro __nsResize_AddParent 1256 0 ${AddHeight} ${AddWidth} 0
  !insertmacro __nsResize_AddParent 1028 0 ${AddHeight} ${AddWidth} 0
  !insertmacro __nsResize_AddParent 1034 0 0 ${AddWidth} -5u
  !insertmacro __nsResize_AddParent 1037 0 -3u ${AddWidth} 0
  !insertmacro __nsResize_AddParent 1038 0 -5u ${AddWidth} 0
  Pop $R0

!macroend
!define nsResize_Window `!insertmacro _nsResize_Window`

!macro _nsResize_WelcomePage AddWidth AddHeight

  ${If} $(^RTL) == 1
    nsResize::Add $mui.WelcomePage.Image 17u 0 -17u ${AddHeight}
    nsResize::Add $mui.WelcomePage.Title -${AddWidth} 0 0 0
    nsResize::Add $mui.WelcomePage.Text -${AddWidth} 0 0 ${AddHeight}
  ${Else}
    nsResize::Add $mui.WelcomePage.Image 0 0 -17u ${AddHeight}
    nsResize::Add $mui.WelcomePage.Title ${AddWidth} 0 0 0
    nsResize::Add $mui.WelcomePage.Text ${AddWidth} 0 0 ${AddHeight}
  ${EndIf}

!macroend
!define nsResize_WelcomePage `!insertmacro _nsResize_WelcomePage`

!macro _nsResize_LicensePage AddWidth AddHeight

  Push $R0
  Push $R1
  FindWindow $R0 `#32770` `` $HWNDPARENT
  nsResize::Add $R0 0 0 ${AddWidth} ${AddHeight}
  !insertmacro __nsResize_AddChild 1040 0 0 ${AddWidth} 0
  !insertmacro __nsResize_AddChild 1000 0 0 ${AddWidth} ${AddHeight}
  !insertmacro __nsResize_AddChild 1006 0 ${AddHeight} ${AddWidth} 0
  !insertmacro __nsResize_AddChild 1034 0 ${AddHeight} ${AddWidth} 0
  !insertmacro __nsResize_AddChild 1035 0 ${AddHeight} ${AddWidth} 0
  Pop $R1
  Pop $R0

!macroend
!define nsResize_LicensePage `!insertmacro _nsResize_LicensePage`

!macro _nsResize_DirectoryPage AddWidth AddHeight

  Push $R0
  Push $R1
  FindWindow $R0 `#32770` `` $HWNDPARENT
  nsResize::Add $R0 0 0 ${AddWidth} ${AddHeight}
  !insertmacro __nsResize_AddChild 1019 0 0 ${AddWidth} 0
  ${If} $(^RTL) == 1
    !insertmacro __nsResize_AddChild 1024 ${AddWidth} 0 0 0
    !insertmacro __nsResize_AddChild 1023 ${AddWidth} 0 0 0
  ${Else}
    !insertmacro __nsResize_AddChild 1001 ${AddWidth} 0 0 0
    !insertmacro __nsResize_AddChild 1008 ${AddWidth} 0 0 0
  ${EndIf}
  !insertmacro __nsResize_AddChild 1006 0 0 ${AddWidth} 0
  !insertmacro __nsResize_AddChild 1020 0 0 ${AddWidth} 0
  Pop $R1
  Pop $R0

!macroend
!define nsResize_DirectoryPage `!insertmacro _nsResize_DirectoryPage`

!macro _nsResize_ComponentsPage AddWidth AddHeight

  Push $R0
  Push $R1
  FindWindow $R0 `#32770` `` $HWNDPARENT
  nsResize::Add $R0 0 0 ${AddWidth} ${AddHeight}
  !insertmacro __nsResize_AddChild 1017 0 0 ${AddWidth} ${AddHeight}
  ${If} $(^RTL) == 1
    !insertmacro __nsResize_AddChild 1022 ${AddWidth} 0 0 ${AddHeight}
    !insertmacro __nsResize_AddChild 1021 ${AddWidth} 0 0 0
    !insertmacro __nsResize_AddChild 1023 ${AddWidth} ${AddHeight} 0 0
  ${Else}
    !insertmacro __nsResize_AddChild 1022 0 0 0 ${AddHeight}
    !insertmacro __nsResize_AddChild 1023 0 ${AddHeight} 0 0
  ${EndIf}
  !insertmacro __nsResize_AddChild 1006 0 0 ${AddWidth} 0
  !insertmacro __nsResize_AddChild 1032 0 0 ${AddWidth} ${AddHeight}
  !ifndef MUI_COMPONENTSPAGE_NODESC
    !ifdef MUI_COMPONENTSPAGE_SMALLDESC
      !insertmacro __nsResize_AddChild 1042 0 ${AddHeight} ${AddWidth} 0
      !insertmacro __nsResize_AddChild 1043 0 ${AddHeight} ${AddWidth} 0
    !else
      !insertmacro __nsResize_AddChild 1042 ${AddWidth} 0 0 ${AddHeight}
      !insertmacro __nsResize_AddChild 1043 ${AddWidth} 0 0 ${AddHeight}
    !endif
  !endif
  Pop $R1
  Pop $R0

!macroend
!define nsResize_ComponentsPage `!insertmacro _nsResize_ComponentsPage`

!macro _nsResize_InstFilesPage AddWidth AddHeight

  Push $R0
  Push $R1
  FindWindow $R0 `#32770` `` $HWNDPARENT
  nsResize::Add $R0 0 0 ${AddWidth} ${AddHeight}
  !insertmacro __nsResize_AddChild 1004 0 0 ${AddWidth} 0
  !insertmacro __nsResize_AddChild 1006 0 0 ${AddWidth} 0
  !insertmacro __nsResize_AddChild 1016 0 0 ${AddWidth} ${AddHeight}
  Pop $R1
  Pop $R0

!macroend
!define nsResize_InstFilesPage `!insertmacro _nsResize_InstFilesPage`

!macro _nsResize_FinishPage AddWidth AddHeight

  ${If} $(^RTL) == 1
    nsResize::Add $mui.FinishPage.Image 17u 0 -17u ${AddHeight}
    nsResize::Add $mui.FinishPage.Title -${AddWidth} 0 0 0
    nsResize::Add $mui.FinishPage.Text -${AddWidth} 0 0 ${AddHeight}
  ${Else}
    nsResize::Add $mui.FinishPage.Image 0 0 -17u ${AddHeight}
    nsResize::Add $mui.FinishPage.Title ${AddWidth} 0 0 0
    nsResize::Add $mui.FinishPage.Text ${AddWidth} 0 0 ${AddHeight}
  ${EndIf}
  !ifdef MUI_FINISHPAGE_RUN_VARIABLES
    nsResize::Add $mui.FinishPage.Run 0 ${AddHeight} 0 0
  !endif
  !ifdef MUI_FINISHPAGE_SHOREADME_VARAIBLES ;not a typo!
    nsResize::Add $mui.FinishPage.ShowReadme 0 ${AddHeight} 0 0
  !endif
  !ifdef MUI_FINISHPAGE_LINK
    nsResize::Add $mui.FinishPage.Link 0 ${AddHeight} 0 0
  !endif
  !ifdef MUI_FINISHPAGE_REBOOT_VARIABLES
    nsResize::Add $mui.FinishPage.RebootNow 0 ${AddHeight} 0 0
    nsResize::Add $mui.FinishPage.RebootLater 0 ${AddHeight} 0 0
  !endif

!macroend
!define nsResize_FinishPage `!insertmacro _nsResize_FinishPage`

!macro _nsResize_ConfirmPage AddWidth AddHeight

  Push $R0
  Push $R1
  FindWindow $R0 `#32770` `` $HWNDPARENT
  nsResize::Add $R0 0 0 ${AddWidth} ${AddHeight}
  ${If} $(^RTL) == 1
    !insertmacro __nsResize_AddChild 1029 ${AddWidth} 0 0 0
  ${EndIf}
  !insertmacro __nsResize_AddChild 1000 0 0 ${AddWidth} 0
  !insertmacro __nsResize_AddChild 1006 0 0 ${AddWidth} 0
  Pop $R1
  Pop $R0

!macroend
!define nsResize_ConfirmPage `!insertmacro _nsResize_ConfirmPage`

!endif