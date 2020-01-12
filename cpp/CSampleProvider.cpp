//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// CSampleProvider implements ICredentialProvider, which is the main
// interface that logonUI uses to decide which tiles to display.
// In this sample, we will display one tile that uses each of the nine
// available UI controls.
//CSampleProvider实现ICredentialProvider，它是
//logonUI用来决定要显示哪些平铺的接口。
//在这个示例中，我们将显示一个磁贴，它使用九个磁贴中的每一个
//可用的用户界面控件。

#include <initguid.h>
#include "CSampleProvider.h"
#include "CSampleCredential.h"
#include "guid.h"

CSampleProvider::CSampleProvider():
    _cRef(1),
    _pCredential(nullptr),
    _pCredProviderUserArray(nullptr)
{
    DllAddRef();
}

CSampleProvider::~CSampleProvider()
{
    if (_pCredential != nullptr)
    {
        _pCredential->Release();
        _pCredential = nullptr;
    }
    if (_pCredProviderUserArray != nullptr)
    {
        _pCredProviderUserArray->Release();
        _pCredProviderUserArray = nullptr;
    }

    DllRelease();
}

// SetUsageScenario is the provider's cue that it's going to be asked for tiles
// in a subsequent call.
//SetUsageScenario是提供者的提示，它将被要求瓷砖
//在随后的通话中。
HRESULT CSampleProvider::SetUsageScenario(
    CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
    DWORD /*dwFlags*/)
{
    HRESULT hr;

    // Decide which scenarios to support here. Returning E_NOTIMPL simply tells the caller
    // that we're not designed for that scenario.
	//决定在这里支持哪些场景。返回E_NOTIMPL只是告诉呼叫者
	//我们不是为那个场景而设计的。
    switch (cpus)
    {
    case CPUS_LOGON:
    case CPUS_UNLOCK_WORKSTATION:
        // The reason why we need _fRecreateEnumeratedCredentials is because ICredentialProviderSetUserArray::SetUserArray() is called after ICredentialProvider::SetUsageScenario(),
        // while we need the ICredentialProviderUserArray during enumeration in ICredentialProvider::GetCredentialCount()
		//我们之所以需要fRecreateEnumeratedCredentials，是因为ICredentialProviderSetUserArray：：SetUserArray（）是在ICredentialProvider：：SetUsageScenario（）之后调用的，
        //在ICredentialProvider：：GetCredentialCount（）中枚举期间需要ICredentialProviderUserArray
        _cpus = cpus;
        _fRecreateEnumeratedCredentials = true;
        hr = S_OK;
        break;

    case CPUS_CHANGE_PASSWORD:
    case CPUS_CREDUI:
        hr = E_NOTIMPL;
        break;

    default:
        hr = E_INVALIDARG;
        break;
    }

    return hr;
}

// SetSerialization takes the kind of buffer that you would normally return to LogonUI for
// an authentication attempt.  It's the opposite of ICredentialProviderCredential::GetSerialization.
// GetSerialization is implement by a credential and serializes that credential.  Instead,
// SetSerialization takes the serialization and uses it to create a tile.
//
// SetSerialization is called for two main scenarios.  The first scenario is in the credui case
// where it is prepopulating a tile with credentials that the user chose to store in the OS.
// The second situation is in a remote logon case where the remote client may wish to
// prepopulate a tile with a username, or in some cases, completely populate the tile and
// use it to logon without showing any UI.
//
// If you wish to see an example of SetSerialization, please see either the SampleCredentialProvider
// sample or the SampleCredUICredentialProvider sample.  [The logonUI team says, "The original sample that
// this was built on top of didn't have SetSerialization.  And when we decided SetSerialization was
// important enough to have in the sample, it ended up being a non-trivial amount of work to integrate
// it into the main sample.  We felt it was more important to get these samples out to you quickly than to
// hold them in order to do the work to integrate the SetSerialization changes from SampleCredentialProvider
// into this sample.]
//SetSerialization接受通常返回LogonUI的缓冲区类型
//身份验证尝试。它与ICredentialProviderCredential：：GetSerialization相反。
//GetSerialization由凭据实现，并序列化该凭据。相反，
//SetSerialization接受序列化并使用它创建平铺。
//
//在两种主要情况下调用SetSerialization。第一种情况是在credui案中
//使用用户选择存储在操作系统中的凭据预填充磁贴的位置。
//第二种情况是在远程登录情况下，远程客户端可能希望
//使用用户名预填充磁贴，或者在某些情况下，完全填充磁贴并
//使用它登录而不显示任何用户界面。
//
//如果您希望看到SetSerialization的示例，请参阅SampleCredentialProvider
//样品或样品CreduicredentialProvider样品。[logonUI团队说，”“原始样本
//这是建立在没有设置序列的基础上的。当我们决定将其序列化
//很重要的一点是，在这个示例中，它最终是一个非常重要的集成工作
//它进入主样本。我们觉得尽快把这些样品给你比
//保存它们以完成集成SampleCredentialProvider的集合序列化更改的工作
//加入本样本。]
HRESULT CSampleProvider::SetSerialization(
    _In_ CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION const * /*pcpcs*/)
{
    return E_NOTIMPL;
}

// Called by LogonUI to give you a callback.  Providers often use the callback if they
// some event would cause them to need to change the set of tiles that they enumerated.
//由LogonUI打电话给你回电话。如果提供者经常使用回调
//某些事件将导致他们需要更改他们枚举的磁贴集。
HRESULT CSampleProvider::Advise(
    _In_ ICredentialProviderEvents * /*pcpe*/,
    _In_ UINT_PTR /*upAdviseContext*/)
{
    return E_NOTIMPL;
}

// Called by LogonUI when the ICredentialProviderEvents callback is no longer valid.
HRESULT CSampleProvider::UnAdvise()
{
    return E_NOTIMPL;
}

// Called by LogonUI to determine the number of fields in your tiles.  This
// does mean that all your tiles must have the same number of fields.
// This number must include both visible and invisible fields. If you want a tile
// to have different fields from the other tiles you enumerate for a given usage
// scenario you must include them all in this count and then hide/show them as desired
// using the field descriptors.
//由LogonUI调用以确定平铺中的字段数。这个
//也就是说你所有的平铺都必须有相同数量的字段。
//此数字必须包含可见字段和不可见字段。如果你想要瓷砖
//与为给定用法枚举的其他平铺具有不同的字段
//场景必须将它们全部包含在此计数中，然后根据需要隐藏/显示它们
//使用字段描述符。
HRESULT CSampleProvider::GetFieldDescriptorCount(
    _Out_ DWORD *pdwCount)
{
    *pdwCount = SFI_NUM_FIELDS;
    return S_OK;
}

// Gets the field descriptor for a particular field.
HRESULT CSampleProvider::GetFieldDescriptorAt(
    DWORD dwIndex,
    _Outptr_result_nullonfailure_ CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR **ppcpfd)
{
    HRESULT hr;
    *ppcpfd = nullptr;

    // Verify dwIndex is a valid field.
    if ((dwIndex < SFI_NUM_FIELDS) && ppcpfd)
    {
        hr = FieldDescriptorCoAllocCopy(s_rgCredProvFieldDescriptors[dwIndex], ppcpfd);
    }
    else
    {
        hr = E_INVALIDARG;
    }

    return hr;
}

// Sets pdwCount to the number of tiles that we wish to show at this time.
// Sets pdwDefault to the index of the tile which should be used as the default.
// The default tile is the tile which will be shown in the zoomed view by default. If
// more than one provider specifies a default the last used cred prov gets to pick
// the default. If *pbAutoLogonWithDefault is TRUE, LogonUI will immediately call
// GetSerialization on the credential you've specified as the default and will submit
// that credential for authentication without showing any further UI.
//将pdwCount设置为我们希望此时显示的平铺数。
//将pdwDefault设置为应用作默认值的磁贴的索引。
//默认平铺是默认情况下将显示在缩放视图中的平铺。如果
//多个提供程序指定最后使用的cred prov要选择的默认值
//默认值。如果*pbAutoLogonWithDefault为TRUE，LogonUI将立即调用
//已指定为默认凭据并将提交的凭据上的GetSerialization
//用于身份验证的凭据，而不显示任何进一步的用户界面。
HRESULT CSampleProvider::GetCredentialCount(
    _Out_ DWORD *pdwCount,
    _Out_ DWORD *pdwDefault,
    _Out_ BOOL *pbAutoLogonWithDefault)
{
    *pdwDefault = CREDENTIAL_PROVIDER_NO_DEFAULT;
    *pbAutoLogonWithDefault = FALSE;

    if (_fRecreateEnumeratedCredentials)
    {
        _fRecreateEnumeratedCredentials = false;
        _ReleaseEnumeratedCredentials();
        _CreateEnumeratedCredentials();
    }

    *pdwCount = 1;

    return S_OK;
}

// Returns the credential at the index specified by dwIndex. This function is called by logonUI to enumerate
// the tiles.
HRESULT CSampleProvider::GetCredentialAt(
    DWORD dwIndex,
    _Outptr_result_nullonfailure_ ICredentialProviderCredential **ppcpc)
{
    HRESULT hr = E_INVALIDARG;
    *ppcpc = nullptr;

    if ((dwIndex == 0) && ppcpc)
    {
        hr = _pCredential->QueryInterface(IID_PPV_ARGS(ppcpc));
    }
    return hr;
}

// This function will be called by LogonUI after SetUsageScenario succeeds.
// Sets the User Array with the list of users to be enumerated on the logon screen.
//此函数将在SetUsageScenario成功后由LogonUI调用。
//使用登录屏幕上要枚举的用户列表设置用户数组。
HRESULT CSampleProvider::SetUserArray(_In_ ICredentialProviderUserArray *users)
{
    if (_pCredProviderUserArray)
    {
        _pCredProviderUserArray->Release();
    }
    _pCredProviderUserArray = users;
    _pCredProviderUserArray->AddRef();
    return S_OK;
}

void CSampleProvider::_CreateEnumeratedCredentials()
{
    switch (_cpus)
    {
    case CPUS_LOGON:
    case CPUS_UNLOCK_WORKSTATION:
        {
            _EnumerateCredentials();
            break;
        }
    default:
        break;
    }
}

void CSampleProvider::_ReleaseEnumeratedCredentials()
{
    if (_pCredential != nullptr)
    {
        _pCredential->Release();
        _pCredential = nullptr;
    }
}

HRESULT CSampleProvider::_EnumerateCredentials()
{
    HRESULT hr = E_UNEXPECTED;
    if (_pCredProviderUserArray != nullptr)
    {
        DWORD dwUserCount;
        _pCredProviderUserArray->GetCount(&dwUserCount);
        if (dwUserCount > 0)
        {
            ICredentialProviderUser *pCredUser;
            hr = _pCredProviderUserArray->GetAt(0, &pCredUser);
            if (SUCCEEDED(hr))
            {
                _pCredential = new(std::nothrow) CSampleCredential();
                if (_pCredential != nullptr)
                {
                    hr = _pCredential->Initialize(_cpus, s_rgCredProvFieldDescriptors, s_rgFieldStatePairs, pCredUser);
                    if (FAILED(hr))
                    {
                        _pCredential->Release();
                        _pCredential = nullptr;
                    }
                }
                else
                {
                    hr = E_OUTOFMEMORY;
                }
                pCredUser->Release();
            }
        }
    }
    return hr;
}

// Boilerplate code to create our provider.
HRESULT CSample_CreateInstance(_In_ REFIID riid, _Outptr_ void **ppv)
{
    HRESULT hr;
    CSampleProvider *pProvider = new(std::nothrow) CSampleProvider();
    if (pProvider)
    {
        hr = pProvider->QueryInterface(riid, ppv);
        pProvider->Release();
    }
    else
    {
        hr = E_OUTOFMEMORY;
    }
    return hr;
}
