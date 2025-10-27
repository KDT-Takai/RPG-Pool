#pragma once
#include <vector>
#include "ScreenBase.h"
#include "CharaFactory.h"

class Game : public ScreenBase {
private:
    bool isGameOver;    // 無限ループ防ぐ

    // Vectorのunique_ptrで持つ
    std::vector<std::unique_ptr<PoolHandle<Player>>> players;
    std::vector<std::unique_ptr<PoolHandle<Enemy>>> enemies;

public:
    Game();
    ~Game() = default;
    // Init実装は必要かなと思って一応入れてるだけ
    void Init() override;
    // 更新処理
    void Update() override;
    // 描画処理
    void Render() override;
};