#pragma once
#include <iostream>
#include "CharaBase.h"

class Player : public CharaBase {
public:
    Player() = default;

    // 情報の受け取り
    void Init(const EntityData& base, int level) override {
        entityData.id = base.id;
        entityData.name = base.name;
        entityData.hp = base.hp + level * 10;
        entityData.atk = base.atk + level * 2;
        entityData.def = base.def + level * 2;
    }
    // 更新処理
    void Update() override {
       
    }
    // 描画処理
    void Render() override {
        // ステータス表示
        RenderState();
    }
};
