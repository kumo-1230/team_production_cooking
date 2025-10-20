#pragma once

#include <Windows.h>
#include <vector>

class KeyInput
{
private:
    struct KeyBank
    {
        int keyCode;
        bool nowKey = false;
        bool prevKey = false;
    };

    std::vector<KeyBank> keyBanks;

    KeyBank* findKeyBank(int keyCode)
    {
        for (auto& key : keyBanks)
        {
            if (key.keyCode == keyCode)
                return &key;
        }
        return nullptr;
    }

public:

    KeyInput() {}
    ~KeyInput() {}

public:
    bool GetKeyDown(int keyCode)
    {
        // ���ɓo�^����Ă���L�[���T��
        KeyBank* key = findKeyBank(keyCode);

        if (!key)
        {
            // �Ȃ���Βǉ�
            keyBanks.push_back({ keyCode });
            key = &keyBanks.back();
        }

        // ���݂̏�Ԃ��X�V
        key->nowKey = (GetAsyncKeyState(keyCode) & 0x8000) != 0;

        //�O��̃L�[�Ɣ�r���ē�����Ԃ��ǂ����m�F����
        bool r = (key->nowKey && !key->prevKey);

        // �O��̏�Ԃ��X�V
        key->prevKey = key->nowKey;

        return r;
    }

    bool GetKey(int keyCode)
    {
        return (GetAsyncKeyState(keyCode) & 0x8000) != 0;
    }
};