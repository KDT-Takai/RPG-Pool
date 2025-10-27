#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GameScene.h"
#include "Text.h"

Game::Game() {
    // ランダム？たしかこれ　うろ覚え
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    // フラグ
    isGameOver = false;
    // プレイヤー生成
    players.push_back(std::make_unique<PoolHandle<Player>>(CharacterFactory::Instance().CreatePlayer(0, 1)));
    players.push_back(std::make_unique<PoolHandle<Player>>(CharacterFactory::Instance().CreatePlayer(1, 1)));
    // エネミー生成
    enemies.push_back(std::make_unique<PoolHandle<Enemy>>(CharacterFactory::Instance().CreateEnemy(0, 2)));
    enemies.push_back(std::make_unique<PoolHandle<Enemy>>(CharacterFactory::Instance().CreateEnemy(3, 4)));

}

void Game::Init() {}

void Game::Update() {
    if (isGameOver)  return;// 無限ループ防ぐ
    Text::Instance().Line();
    // --- プレイヤーターン ---
    for (auto it = players.begin(); it != players.end(); ++it) {    // プレイヤーの数だけ
        if (enemies.empty()) break;

        PoolHandle<Player>& p = **it; // unique_ptrの中身にアクセス
        // 描画
        std::cout << p->GetData().name << " のターン。攻撃を選択してください : 0~" << enemies.size() - 1 << "): ";
        int choice;     // 誰を選択したかの表示
        std::cin >> choice;
        // 攻撃処理
        if (choice >= 0 && choice < (int)enemies.size()) {
            PoolHandle<Enemy>& targetEnemy = *enemies[choice];

            int dmg = p->GetData().atk - targetEnemy->GetData().def;
            if (dmg < 0) dmg = 0;

            targetEnemy->TakeDamage(dmg);
            std::cout << targetEnemy->GetData().name << " に " << dmg << " ダメージ！\n";

            if (targetEnemy->GetData().hp <= 0) {
                std::cout << targetEnemy->GetData().name << " は倒れた！\n";
                enemies.erase(enemies.begin() + choice);
            }
        }
    }
    // 確認
    if (enemies.empty()) {
        std::cout << "プレイヤーの勝利です！\n";
        isGameOver = true;
        return;
    }

    // --- 敵ターン ---
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        if (players.empty()) break;

        PoolHandle<Enemy>& e = **it;
        int targetIndex = std::rand() % players.size();
        PoolHandle<Player>& targetPlayer = *players[targetIndex];

        int dmg = e->GetData().atk - targetPlayer->GetData().def;
        if (dmg < 0) dmg = 0;

        targetPlayer->TakeDamage(dmg);
        std::cout << e->GetData().name << " が " << targetPlayer->GetData().name << " に " << dmg << " ダメージを与えた！\n";

        if (targetPlayer->GetData().hp <= 0) {
            std::cout << targetPlayer->GetData().name << " は倒れた！\n";
            players.erase(players.begin() + targetIndex);
        }
    }

    // 確認
    if (players.empty()) {
        std::cout << "敵の勝利です！\n";
        isGameOver = true;
        return;
    }

    // Update呼び出し
    for (auto& p : players) (**p).Update();
    for (auto& e : enemies) (**e).Update();
}

void Game::Render() {
    if (isGameOver)  return; // 無限ループ防ぐ
    Text::Instance().Line();
    std::cout << "プレイヤー\n";
    for (auto& p : players) (**p).Render();

    std::cout << "\n敵\n";
    for (auto& e : enemies) (**e).Render();
}