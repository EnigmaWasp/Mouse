object Form1: TForm1
  Left = 267
  Top = 128
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Голодающая мышь'
  ClientHeight = 300
  ClientWidth = 450
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 335
    Top = 60
    Width = 72
    Height = 16
    Caption = 'Жизней:3'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 310
    Top = 75
    Width = 121
    Height = 23
    Alignment = taCenter
    AutoSize = False
    Caption = 'Очки:0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -20
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Timer1: TTimer
    Interval = 10
    OnTimer = Timer1Timer
  end
end
