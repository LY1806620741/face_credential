//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//此代码和信息按“原样”提供，不保证
//任何种类，明示或暗示的，包括但不限于
//适销性和 / 或适用性的默示保证
//特殊目的。
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//版权所有（c）微软 公司。保留所有权利。
//
// This file contains some global variables that describe what our
// sample tile looks like.  For example, it defines what fields a tile has
// and which fields show in which states of LogonUI. This sample illustrates
// the use of each UI field type.
//此文件包含一些全局变量，这些变量描述了
//样品瓷砖看起来像。例如，它定义磁贴具有哪些字段
//哪些字段显示LogonUI的哪些状态。此示例说明
//每个UI字段类型的使用。

#pragma once
#include "helpers.h"

// The indexes of each of the fields in our credential provider's tiles. Note that we're
// using each of the nine available field types here.
//凭据提供程序磁贴中每个字段的索引。注意我们
//使用此处九种可用字段类型中的每一种。
enum SAMPLE_FIELD_ID
{
    SFI_TILEIMAGE         = 0,
    SFI_LABEL             = 1,
    SFI_LARGE_TEXT        = 2,
    SFI_PASSWORD          = 3,
    SFI_SUBMIT_BUTTON     = 4,
    SFI_LAUNCHWINDOW_LINK = 5,
    SFI_HIDECONTROLS_LINK = 6,
    SFI_FULLNAME_TEXT     = 7,
    SFI_DISPLAYNAME_TEXT  = 8,
    SFI_LOGONSTATUS_TEXT  = 9,   // Note: if new fields are added, keep NUM_FIELDS last.  This is used as a count of the number of fields
    SFI_NUM_FIELDS        = 10,  // 注：如果添加新字段，则保留最后字段编号。这是一个数值的字段。
};

// The first value indicates when the tile is displayed (selected, not selected)
// the second indicates things like whether the field is enabled, whether it has key focus, etc.
//第一个值指示何时显示平铺（选定，未选定）
//第二个指示字段是否已启用、是否具有关键焦点等
struct FIELD_STATE_PAIR
{
    CREDENTIAL_PROVIDER_FIELD_STATE cpfs;
    CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE cpfis;
};

// These two arrays are seperate because a credential provider might
// want to set up a credential with various combinations of field state pairs
// and field descriptors.
//这两个数组是分开的，因为凭据提供程序可能
//希望使用字段状态对的各种组合设置凭据
//以及字段描述符

// The field state value indicates whether the field is displayed
// in the selected tile, the deselected tile, or both.
// The Field interactive state indicates when
//字段状态值指示是否显示该字段
//在选定的平铺中，取消选择的平铺，或同时取消选择这两个平铺。
//字段交互状态指示何时
static const FIELD_STATE_PAIR s_rgFieldStatePairs[] =
{
    { CPFS_DISPLAY_IN_BOTH,            CPFIS_NONE    },    // SFI_TILEIMAGE
    { CPFS_HIDDEN,                     CPFIS_NONE    },    // SFI_LABEL
    { CPFS_DISPLAY_IN_BOTH,            CPFIS_NONE    },    // SFI_LARGE_TEXT
    { CPFS_DISPLAY_IN_SELECTED_TILE,   CPFIS_FOCUSED },    // SFI_PASSWORD
    { CPFS_DISPLAY_IN_SELECTED_TILE,   CPFIS_NONE    },    // SFI_SUBMIT_BUTTON
    { CPFS_DISPLAY_IN_SELECTED_TILE,   CPFIS_NONE    },    // SFI_LAUNCHWINDOW_LINK
    { CPFS_DISPLAY_IN_SELECTED_TILE,   CPFIS_NONE    },    // SFI_HIDECONTROLS_LINK
    { CPFS_HIDDEN,                     CPFIS_NONE    },    // SFI_FULLNAME_TEXT
    { CPFS_HIDDEN,                     CPFIS_NONE    },    // SFI_DISPLAYNAME_TEXT
    { CPFS_HIDDEN,                     CPFIS_NONE    },    // SFI_LOGONSTATUS_TEXT
};

// Field descriptors for unlock and logon.
// The first field is the index of the field.
// The second is the type of the field.
// The third is the name of the field, NOT the value which will appear in the field.
//用于解锁和登录的字段描述符。
//第一个字段是字段的索引。
//第二个是字段的类型。
//第三个是字段的名称，而不是将出现在字段中的值。
static const CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR s_rgCredProvFieldDescriptors[] =
{
    { SFI_TILEIMAGE,         CPFT_TILE_IMAGE,    L"图片",                      CPFG_CREDENTIAL_PROVIDER_LOGO  },
    { SFI_LABEL,             CPFT_SMALL_TEXT,    L"工具提示",                  CPFG_CREDENTIAL_PROVIDER_LABEL },
    { SFI_LARGE_TEXT,        CPFT_LARGE_TEXT,    L"人脸凭据"                                                  },
    { SFI_PASSWORD,          CPFT_PASSWORD_TEXT, L"密码文本"                                                  },
    { SFI_SUBMIT_BUTTON,     CPFT_SUBMIT_BUTTON, L"提交"                                                      },
    { SFI_LAUNCHWINDOW_LINK, CPFT_COMMAND_LINK,  L"打开帮助窗口"                                              },
    { SFI_HIDECONTROLS_LINK, CPFT_COMMAND_LINK,  L"显示其他控制器"                                            },
    { SFI_FULLNAME_TEXT,     CPFT_SMALL_TEXT,    L"全名: "                                                    },
    { SFI_DISPLAYNAME_TEXT,  CPFT_SMALL_TEXT,    L"显示名: "                                                  },
    { SFI_LOGONSTATUS_TEXT,  CPFT_SMALL_TEXT,    L"登录状态: "                                                },
};
