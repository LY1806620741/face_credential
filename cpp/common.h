//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//�˴������Ϣ����ԭ�����ṩ������֤
//�κ����࣬��ʾ��ʾ�ģ�������������
//�����Ժ� / �������Ե�Ĭʾ��֤
//����Ŀ�ġ�
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//��Ȩ���У�c��΢�� ��˾����������Ȩ����
//
// This file contains some global variables that describe what our
// sample tile looks like.  For example, it defines what fields a tile has
// and which fields show in which states of LogonUI. This sample illustrates
// the use of each UI field type.
//���ļ�����һЩȫ�ֱ�������Щ����������
//��Ʒ��ש�����������磬���������������Щ�ֶ�
//��Щ�ֶ���ʾLogonUI����Щ״̬����ʾ��˵��
//ÿ��UI�ֶ����͵�ʹ�á�

#pragma once
#include "helpers.h"

// The indexes of each of the fields in our credential provider's tiles. Note that we're
// using each of the nine available field types here.
//ƾ���ṩ���������ÿ���ֶε�������ע������
//ʹ�ô˴����ֿ����ֶ������е�ÿһ�֡�
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
    SFI_NUM_FIELDS        = 10,  // ע�����������ֶΣ���������ֶα�š�����һ����ֵ���ֶΡ�
};

// The first value indicates when the tile is displayed (selected, not selected)
// the second indicates things like whether the field is enabled, whether it has key focus, etc.
//��һ��ֵָʾ��ʱ��ʾƽ�̣�ѡ����δѡ����
//�ڶ���ָʾ�ֶ��Ƿ������á��Ƿ���йؼ������
struct FIELD_STATE_PAIR
{
    CREDENTIAL_PROVIDER_FIELD_STATE cpfs;
    CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE cpfis;
};

// These two arrays are seperate because a credential provider might
// want to set up a credential with various combinations of field state pairs
// and field descriptors.
//�����������Ƿֿ��ģ���Ϊƾ���ṩ�������
//ϣ��ʹ���ֶ�״̬�Եĸ����������ƾ��
//�Լ��ֶ�������

// The field state value indicates whether the field is displayed
// in the selected tile, the deselected tile, or both.
// The Field interactive state indicates when
//�ֶ�״ֵָ̬ʾ�Ƿ���ʾ���ֶ�
//��ѡ����ƽ���У�ȡ��ѡ���ƽ�̣���ͬʱȡ��ѡ��������ƽ�̡�
//�ֶν���״ָ̬ʾ��ʱ
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
//���ڽ����͵�¼���ֶ���������
//��һ���ֶ����ֶε�������
//�ڶ������ֶε����͡�
//���������ֶε����ƣ������ǽ��������ֶ��е�ֵ��
static const CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR s_rgCredProvFieldDescriptors[] =
{
    { SFI_TILEIMAGE,         CPFT_TILE_IMAGE,    L"ͼƬ",                      CPFG_CREDENTIAL_PROVIDER_LOGO  },
    { SFI_LABEL,             CPFT_SMALL_TEXT,    L"������ʾ",                  CPFG_CREDENTIAL_PROVIDER_LABEL },
    { SFI_LARGE_TEXT,        CPFT_LARGE_TEXT,    L"����ƾ��"                                                  },
    { SFI_PASSWORD,          CPFT_PASSWORD_TEXT, L"�����ı�"                                                  },
    { SFI_SUBMIT_BUTTON,     CPFT_SUBMIT_BUTTON, L"�ύ"                                                      },
    { SFI_LAUNCHWINDOW_LINK, CPFT_COMMAND_LINK,  L"�򿪰�������"                                              },
    { SFI_HIDECONTROLS_LINK, CPFT_COMMAND_LINK,  L"��ʾ����������"                                            },
    { SFI_FULLNAME_TEXT,     CPFT_SMALL_TEXT,    L"ȫ��: "                                                    },
    { SFI_DISPLAYNAME_TEXT,  CPFT_SMALL_TEXT,    L"��ʾ��: "                                                  },
    { SFI_LOGONSTATUS_TEXT,  CPFT_SMALL_TEXT,    L"��¼״̬: "                                                },
};
