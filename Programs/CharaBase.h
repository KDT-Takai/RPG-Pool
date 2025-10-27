#pragma once
#include <iostream>
#include "CharaData.h"	// EntityData Entityが持つ情報 名前,hpなど

class CharaBase {
protected:

	EntityData entityData;	// データ
	int level;				// レベル

public:

	CharaBase() = default;
	virtual ~CharaBase() = default;
	// 初期化処理
	virtual void Init(const EntityData& base, int level) = 0;
	// 更新処理
	virtual void Update() = 0;
	// 描画処理
	virtual void Render() = 0;

	bool IsDead() const { return entityData.hp <= 0; }
	// 情報アクセス
	const EntityData& GetData() { return entityData; }
	// レベル
	int GetLevel() { return level; }
	// HPのセッター
	void SetHP(int hp) { entityData.hp = hp; }
	// ステータス表示
	void RenderState() const {
		std::cout << "ID:" << entityData.id <<  "NAME:" << entityData.name << " HP:" << entityData.hp << " ATK:" << entityData.atk
			<< "DEF:" << entityData.def << std::endl;
	}
	// ダメージを受ける
	void TakeDamage(int dmg) {
		entityData.hp -= dmg;
		if (entityData.hp < 0) entityData.hp = 0;
	}
};