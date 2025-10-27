#pragma once
#include "CharaBase.h"
#include "Player.h"
#include "Enemy.h"
#include "ObjectPool.h"
#include <iostream>
#include "Singleton.h"

// ファクトリー シングルトンでする
class CharacterFactory : public Singleton<CharacterFactory> {
    // firend classで持つ
    friend class Singleton<CharacterFactory>;
private:
    // objectPoolでプレイヤーとエネミーの確保
    ObjectPool<Player> playerPool;
    ObjectPool<Enemy> enemyPool;

public:

    static const EntityData PlayerBaseState[];
    static const EntityData EnemyBaseState[];
    static const int PlayerTableSize;
    static const int EnemyTableSize;

    // コンストラクタでサイズをあらかじめ決める
    CharacterFactory()
        : playerPool(8), enemyPool(8) {}

    // 生成
    PoolHandle<Player> CreatePlayer(int ID, int level);
    PoolHandle<Enemy>  CreateEnemy(int ID, int level);
};
