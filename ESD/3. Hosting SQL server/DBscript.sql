USE [nameofdatabase]
GO
/****** Object:  Table [dbo].[BwAnaChgLog]    Script Date: 30-Aug-21 3:38:29 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[BwAnaChgLog](
	[ProjNodeId] [int] NOT NULL,
	[TagName] [varchar](32) NOT NULL,
	[LogDate] [varchar](12) NOT NULL,
	[LogTime] [varchar](12) NOT NULL,
	[LogMilliSecond] [int] NOT NULL,
	[LogValue] [numeric](18, 6) NULL,
	[Alarm] [int] NULL,
 CONSTRAINT [pk_AnaChgLog_1] PRIMARY KEY CLUSTERED 
(
	[ProjNodeId] ASC,
	[LogDate] ASC,
	[LogTime] ASC,
	[LogMilliSecond] ASC,
	[TagName] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-16', N'16:38:46', 4, CAST(2.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-16', N'16:39:35', 4, CAST(1.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-16', N'16:40:23', 4, CAST(2.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-16', N'17:16:47', 4, CAST(1.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-16', N'17:17:20', 4, CAST(4.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-16', N'17:17:27', 4, CAST(2.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-16', N'17:28:23', 4, CAST(2.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-16', N'17:29:01', 4, CAST(1.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-16', N'17:31:14', 4, CAST(3.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-16', N'17:31:41', 4, CAST(2.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-16', N'17:39:17', 4, CAST(2.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-16', N'17:40:38', 4, CAST(1.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-17', N'07:16:29', 4, CAST(2.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-17', N'07:39:44', 4, CAST(2.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-17', N'07:48:31', 4, CAST(1.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-17', N'07:48:53', 4, CAST(2.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-17', N'08:07:58', 4, CAST(1.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-17', N'08:08:31', 4, CAST(2.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-17', N'10:05:59', 4, CAST(1.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-17', N'10:22:31', 4, CAST(4.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-17', N'10:22:37', 4, CAST(2.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-17', N'10:24:10', 4, CAST(1.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-30', N'12:41:49', 4, CAST(2.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-30', N'12:43:44', 4, CAST(1.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-30', N'12:45:06', 4, CAST(2.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-30', N'12:53:06', 4, CAST(2.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-30', N'12:54:38', 4, CAST(2.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-30', N'13:14:52', 4, CAST(2.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-30', N'13:16:51', 4, CAST(3.000000 AS Numeric(18, 6)), NULL)
INSERT [dbo].[BwAnaChgLog] ([ProjNodeId], [TagName], [LogDate], [LogTime], [LogMilliSecond], [LogValue], [Alarm]) VALUES (7, N'L9_SMT_ESD_1_Op1_Stat ', N'2021-08-30', N'13:17:20', 4, CAST(1.000000 AS Numeric(18, 6)), NULL)
