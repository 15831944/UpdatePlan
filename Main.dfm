object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = #25972#29702#24179#38754#22270#25968#25454
  ClientHeight = 497
  ClientWidth = 835
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  WindowState = wsMaximized
  DesignSize = (
    835
    497)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 136
    Top = 386
    Width = 31
    Height = 13
    Anchors = [akLeft, akBottom]
    Caption = 'Label1'
  end
  object Label2: TLabel
    Left = 136
    Top = 437
    Width = 31
    Height = 13
    Anchors = [akLeft, akBottom]
    Caption = 'Label2'
  end
  object PlanDataAdvStringGrid: TAdvStringGrid
    Left = 0
    Top = 0
    Width = 835
    Height = 370
    Cursor = crDefault
    Align = alTop
    Anchors = [akLeft, akTop, akRight, akBottom]
    DrawingStyle = gdsClassic
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 0
    ActiveCellFont.Charset = DEFAULT_CHARSET
    ActiveCellFont.Color = clWindowText
    ActiveCellFont.Height = -11
    ActiveCellFont.Name = 'Tahoma'
    ActiveCellFont.Style = [fsBold]
    ControlLook.FixedGradientHoverFrom = clGray
    ControlLook.FixedGradientHoverTo = clWhite
    ControlLook.FixedGradientDownFrom = clGray
    ControlLook.FixedGradientDownTo = clSilver
    ControlLook.DropDownHeader.Font.Charset = DEFAULT_CHARSET
    ControlLook.DropDownHeader.Font.Color = clWindowText
    ControlLook.DropDownHeader.Font.Height = -11
    ControlLook.DropDownHeader.Font.Name = 'Tahoma'
    ControlLook.DropDownHeader.Font.Style = []
    ControlLook.DropDownHeader.Visible = True
    ControlLook.DropDownHeader.Buttons = <>
    ControlLook.DropDownFooter.Font.Charset = DEFAULT_CHARSET
    ControlLook.DropDownFooter.Font.Color = clWindowText
    ControlLook.DropDownFooter.Font.Height = -11
    ControlLook.DropDownFooter.Font.Name = 'Tahoma'
    ControlLook.DropDownFooter.Font.Style = []
    ControlLook.DropDownFooter.Visible = True
    ControlLook.DropDownFooter.Buttons = <>
    Filter = <>
    FilterDropDown.Font.Charset = DEFAULT_CHARSET
    FilterDropDown.Font.Color = clWindowText
    FilterDropDown.Font.Height = -11
    FilterDropDown.Font.Name = 'Tahoma'
    FilterDropDown.Font.Style = []
    FilterDropDownClear = '(All)'
    FixedRowHeight = 22
    FixedFont.Charset = DEFAULT_CHARSET
    FixedFont.Color = clWindowText
    FixedFont.Height = -11
    FixedFont.Name = 'Tahoma'
    FixedFont.Style = [fsBold]
    FloatFormat = '%.2f'
    PrintSettings.DateFormat = 'dd/mm/yyyy'
    PrintSettings.Font.Charset = DEFAULT_CHARSET
    PrintSettings.Font.Color = clWindowText
    PrintSettings.Font.Height = -11
    PrintSettings.Font.Name = 'Tahoma'
    PrintSettings.Font.Style = []
    PrintSettings.FixedFont.Charset = DEFAULT_CHARSET
    PrintSettings.FixedFont.Color = clWindowText
    PrintSettings.FixedFont.Height = -11
    PrintSettings.FixedFont.Name = 'Tahoma'
    PrintSettings.FixedFont.Style = []
    PrintSettings.HeaderFont.Charset = DEFAULT_CHARSET
    PrintSettings.HeaderFont.Color = clWindowText
    PrintSettings.HeaderFont.Height = -11
    PrintSettings.HeaderFont.Name = 'Tahoma'
    PrintSettings.HeaderFont.Style = []
    PrintSettings.FooterFont.Charset = DEFAULT_CHARSET
    PrintSettings.FooterFont.Color = clWindowText
    PrintSettings.FooterFont.Height = -11
    PrintSettings.FooterFont.Name = 'Tahoma'
    PrintSettings.FooterFont.Style = []
    PrintSettings.PageNumSep = '/'
    SearchFooter.FindNextCaption = 'Find &next'
    SearchFooter.FindPrevCaption = 'Find &previous'
    SearchFooter.Font.Charset = DEFAULT_CHARSET
    SearchFooter.Font.Color = clWindowText
    SearchFooter.Font.Height = -11
    SearchFooter.Font.Name = 'Tahoma'
    SearchFooter.Font.Style = []
    SearchFooter.HighLightCaption = 'Highlight'
    SearchFooter.HintClose = 'Close'
    SearchFooter.HintFindNext = 'Find next occurrence'
    SearchFooter.HintFindPrev = 'Find previous occurrence'
    SearchFooter.HintHighlight = 'Highlight occurrences'
    SearchFooter.MatchCaseCaption = 'Match case'
    Version = '5.8.7.0'
    ExplicitWidth = 780
    object Image1: TImage
      Left = 0
      Top = 0
      Width = 831
      Height = 533
      Align = alTop
      Anchors = [akLeft, akTop, akRight, akBottom]
      ExplicitWidth = 606
      ExplicitHeight = 363
    end
  end
  object OpenButton: TButton
    Left = 8
    Top = 405
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #25171#24320
    TabOrder = 1
    OnClick = OpenButtonClick
  end
  object CloseButton: TButton
    Left = 752
    Top = 456
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #20851#38381
    TabOrder = 2
    OnClick = CloseButtonClick
  end
  object DrawButton: TButton
    Left = 8
    Top = 456
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #32472#22270
    TabOrder = 3
    OnClick = DrawButtonClick
  end
  object DistinguishCrossesButton: TButton
    Left = 104
    Top = 405
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #35782#21035#36947#23700
    TabOrder = 4
    OnClick = DistinguishCrossesButtonClick
  end
  object DrawSwitchesButton: TButton
    Left = 201
    Top = 405
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #32472#21046#36947#23700
    TabOrder = 5
    OnClick = DrawSwitchesButtonClick
  end
  object ListBox1: TListBox
    Left = 294
    Top = 392
    Width = 121
    Height = 97
    Anchors = [akLeft, akBottom]
    ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 6
    OnClick = ListBox1Click
  end
  object DistinguishPathsButton: TButton
    Left = 104
    Top = 456
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #35782#21035#32447#36335
    TabOrder = 7
    OnClick = DistinguishPathsButtonClick
  end
  object DrawPathsButton: TButton
    Left = 201
    Top = 456
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #32472#21046#32447#36335
    TabOrder = 8
    OnClick = DrawPathsButtonClick
  end
  object ListBox2: TListBox
    Left = 434
    Top = 392
    Width = 121
    Height = 97
    Anchors = [akLeft, akBottom]
    ItemHeight = 13
    TabOrder = 9
    OnClick = ListBox2Click
  end
  object Button1: TButton
    Left = 752
    Top = 405
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #35774#32622#20301#32622
    TabOrder = 10
    OnClick = Button1Click
  end
  object ListBox3: TListBox
    Left = 576
    Top = 392
    Width = 161
    Height = 97
    Anchors = [akLeft, akRight, akBottom]
    ItemHeight = 13
    TabOrder = 11
  end
  object ExcelOpenDialog: TOpenDialog
    Filter = 'Excel'#25991#20214'(*.xls, *.xlsx)|*.xls;*xlsx|'#20840#37096#25991#20214'(*.*)|*.*'
    Left = 56
    Top = 328
  end
end
