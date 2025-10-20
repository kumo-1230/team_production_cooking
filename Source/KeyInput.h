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
        // 既に登録されているキーか探す
        KeyBank* key = findKeyBank(keyCode);

        if (!key)
        {
            // なければ追加
            keyBanks.push_back({ keyCode });
            key = &keyBanks.back();
        }

        // 現在の状態を更新
        key->nowKey = (GetAsyncKeyState(keyCode) & 0x8000) != 0;

        //前回のキーと比較して同じ状態かどうか確認する
        bool r = (key->nowKey && !key->prevKey);

        // 前回の状態を更新
        key->prevKey = key->nowKey;

        return r;
    }

    bool GetKey(int keyCode)
    {
        return (GetAsyncKeyState(keyCode) & 0x8000) != 0;
    }
};