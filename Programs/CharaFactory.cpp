#include "CharaFactory.h"

const EntityData CharacterFactory::PlayerBaseState[] = {
    {0,"勇者",100,50,10},
    {1,"魔術師",100,50,10},
    {2,"ナイトメア",100,50,10},
    {3,"マリオネスト",100,50,10},
    {4,"ウォーリアー",100,50,10},
};

const EntityData CharacterFactory::EnemyBaseState[] = {
    {0,"ゴブリン",100,50,10},
    {1,"スライム",100,50,10},
    {2,"ワイバーン",100,50,10},
    {3,"ガーゴイル",100,50,10},
    {4,"スケルトン",100,50,10},
};

const int CharacterFactory::PlayerTableSize = sizeof(PlayerBaseState) / sizeof(EntityData);
const int CharacterFactory::EnemyTableSize = sizeof(EnemyBaseState) / sizeof(EntityData);

PoolHandle<Player> CharacterFactory::CreatePlayer(int ID, int level) {
    if (ID < 0 || ID >= PlayerTableSize) {
        std::cerr << "Failure: CharacterFactory::CreatePlayer - invalid ID\n";
        return {};
    }

    auto player = playerPool.Acquire();
    player->Init(PlayerBaseState[ID], level);
    return player;
}

PoolHandle<Enemy> CharacterFactory::CreateEnemy(int ID, int level) {
    if (ID < 0 || ID >= EnemyTableSize) {
        std::cerr << "Failure: CharacterFactory::CreateEnemy - invalid ID\n";
        return {};
    }

    auto enemy = enemyPool.Acquire();
    enemy->Init(EnemyBaseState[ID], level);
    return enemy;
}
