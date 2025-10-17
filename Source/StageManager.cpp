#include "StageManager.h"
#include "MapTip/map_manager.h"
#include "Floor.h"
#include "Stove.h"
#include "Pot.h"
#include "Cursor.h"
#include "TileNone.h"
#include "Submission.h"
#include <imgui.h>
#include "Sink.h"
#include "CreateDishBox.h"
#include "Board.h"
#include "Collision.h"
#include "Player.h"

#include "TileBox.h"
#include "BaconBox.h"
#include "EggBox.h"
#include "Onion.h"
#include "Rice.h"
#include "Tomato.h"
#include "Sauce.h"
#include "PlayerSpawn.h"

#define DEBUG

StageManager::StageManager()
{
	Initialize();
}

StageManager::~StageManager()
{
}

void StageManager::Initialize()
{
	floor = std::make_unique<Floor>();
	std::vector<std::vector<int>> map;

	//マップロード
	{
		MapManager mapLoad;
		mapLoad.MapLoad(&mapLoad);
		mapLoad.AllMapSet(map);
	}

	TileMapBank.resize(map.size());
	// 各行ごとに列を初期化（nullptr）
	for (size_t i = 0; i < map.size(); ++i)
	{
		TileMapBank[i].resize(map[i].size()); // 各行に同じ列数を確保
		for (size_t j = 0; j < map[i].size(); ++j)
		{
			TileMapBank[i][j] = nullptr; // 明示的にnullptrで初期化
		}
	}
	for (int i = 0; i < TileMapBank.size(); i++)
	{
		for (int j = 0; j < TileMapBank[i].size();j++)
		{
			DirectX::XMFLOAT3 p = { j * 2.0f,0.0f,i * 2.0f };

			switch (map[i][j])
			{
			case TILE_MODEL::NONE:
				TileMapBank[i][j] = std::make_unique<TileNone>(p);
				break;
			case TILE_MODEL::EGG:
				TileMapBank[i][j] = std::make_unique<TileBox>(p);
				tileMapBox.push_back(std::make_unique<EggBox>(p, map[i][j]));
				break;
			case TILE_MODEL::OFFER:
				TileMapBank[i][j] = std::make_unique<Submission>(p,1);
				break;
			case TILE_MODEL::RETURN_DISH:
				TileMapBank[i][j] = std::make_unique<CreateDishBox>(p,1);
				break;
			case TILE_MODEL::ONION:
				TileMapBank[i][j] = std::make_unique<TileBox>(p);
				tileMapBox.push_back(std::make_unique<OnionBox>(p, map[i][j]));
				break;
			case TILE_MODEL::RICE:
				TileMapBank[i][j] = std::make_unique<TileBox>(p);
				tileMapBox.push_back(std::make_unique<RiceBox>(p, map[i][j]));
				break;
			case TILE_MODEL::TOMATO:
				TileMapBank[i][j] = std::make_unique<TileBox>(p);
				tileMapBox.push_back(std::make_unique<TomatoBox>(p, map[i][j]));
				break;
			case TILE_MODEL::KETCHUP:
				TileMapBank[i][j] = std::make_unique<KetuchupBox>(p, map[i][j]);
				break;
			case TILE_MODEL::DEMI:
				TileMapBank[i][j] = std::make_unique<DemiBox>(p, map[i][j]);
				break;
			case TILE_MODEL::WHITE:
				TileMapBank[i][j] = std::make_unique<WhiteBox>(p, map[i][j]);
				break;
			case TILE_MODEL::PLAYER:
				TileMapBank[i][j] = std::make_unique<TileBox>(p);
				tileMapBox.push_back(std::make_unique<PlayerSpown>(p, map[i][j]));
				PlayerPos = tileMapBox.size() - 1;
				break;
			default:
				TileMapBank[i][j] = std::make_unique<TileNone>(p);
				break;
			}
			if (map[i][j] == TILE_MODEL::OFFER ||
				map[i][j] == TILE_MODEL::RETURN_DISH ||
				map[i][j] == TILE_MODEL::KETCHUP ||
				map[i][j] == TILE_MODEL::DEMI ||
				map[i][j] == TILE_MODEL::WHITE)
			{
				TileMapBank[i][j]->SetMode(map[i][j]);
			}
			else if (map[i][j] != TILE_MODEL::NONE)
			{
				int b = TILE_MODEL::BOX;
				TileMapBank[i][j]->SetMode(b);
			}
			else
			{
				int b = TILE_MODEL::NONE;
				TileMapBank[i][j]->SetMode(b);
			}
		}
	}
	DirectX::XMFLOAT3 p = { 0,0.0f,0.0f };
	cursor = std::make_unique<Cursor>(p);
	key = std::make_unique<KeyInput>();
	sprite = std::make_unique<Sprite>("Data/Sprite/ge-zi.png");
	spriteWarning = std::make_unique<Sprite>("Data/Sprite/Warning.png");

}

void StageManager::SetMapTip()
{
	std::unique_ptr<Utensils> b;
	std::unique_ptr<Utensils> b2;
	{
		DirectX::XMFLOAT3 pos{};
		b2 = std::make_unique<TileNone>(pos);
		b2->SetMode(TILE_MODEL::NONE);
	}
	bool nextBild = true;
	bool change = true;

	oldX = x;
	oldY = y;
	oldTileMode = TileMode;
	oldLv = Lv;

	int modeBank = TileMapBank[y][x]->GetMode();
	int LvBank = TileMapBank[y][x]->GetLv();
	int LvBank2 = TileMapBank[nextY][nextX]->GetLv();

	DirectX::XMFLOAT3 p = { x * 2.0f,0.0f,y * 2.0f };

	if (modeBank == TILE_MODEL::BOX)
	{
		return;
	}
	if (modeBank == TILE_MODEL::NONE && TileMode == TILE_MODEL::NONE)
	{
		return;
	}
	switch (TileMode)
	{
	case TILE_MODEL::NONE:
		b = std::make_unique<TileNone>(p);
		Lv = TileMapBank[y][x]->GetLv();
		break;
	case TILE_MODEL::BOARD:
		b = std::make_unique<Board>(p, Lv, Long, false);
		if (Long)
		{
			if (TileMapBank[nextY][nextX]->GetMode() != TILE_MODEL::BOX)
			{
				p = { nextX * 2.0f,0.0f,nextY * 2.0f };
				b2 = std::make_unique<Board>(p, Lv,Long,true);
				b->SetFriendOn(Long);
				b->SetFriendX(nextX);
				b->SetFriendY(nextY);

				b2->SetFriendOn(Long);
				b2->SetFriendX(x);
				b2->SetFriendY(y);
			}
			else
			{
				nextBild = false;
			}
		}
		break;
	case TILE_MODEL::POT:
		b = std::make_unique<Pot>(p, Lv, Long, false);
		if (Long)
		{
			if (TileMapBank[nextY][nextX]->GetMode() != TILE_MODEL::BOX)
			{
				p = { nextX * 2.0f,0.0f,nextY * 2.0f };
				b2 = std::make_unique<Pot>(p, Lv, Long, true);
				b->SetFriendOn(Long);
				b->SetFriendX(nextX);
				b->SetFriendY(nextY);

				b2->SetFriendOn(Long);
				b2->SetFriendX(x);
				b2->SetFriendY(y);
			}
			else
			{
				nextBild = false;
			}
		}
		break;
	case TILE_MODEL::SINK:
		b = (std::make_unique<Sink>(p, Lv, false));
		p = { nextX * 2.0f,0.0f,nextY * 2.0f };
		if (Long)
		{
			if (TileMapBank[nextY][nextX]->GetMode() != TILE_MODEL::BOX)
			{
				p = { nextX * 2.0f,0.0f,nextY * 2.0f };
				b2 = (std::make_unique<Sink>(p, Lv, true));
				b->SetFriendOn(Long);
				b->SetFriendX(nextX);
				b->SetFriendY(nextY);

				b2->SetFriendOn(Long);
				b2->SetFriendX(x);
				b2->SetFriendY(y);
			}
			else
			{
				nextBild = false;
			}
		}
		break;
	case TILE_MODEL::STOVE:
		b = std::make_unique<Stove>(p, Lv, Long, false);
		if (Long)
		{
			if (TileMapBank[nextY][nextX]->GetMode() != TILE_MODEL::BOX)
			{
				p = { nextX * 2.0f,0.0f,nextY * 2.0f };
				b2 = std::make_unique<Stove>(p, Lv, Long, true);
				b->SetFriendOn(Long);
				b->SetFriendX(nextX);
				b->SetFriendY(nextY);

				b2->SetFriendOn(Long);
				b2->SetFriendX(x);
				b2->SetFriendY(y);
			}
			else
			{
				nextBild = false;
			}
		}
		break;
	case TILE_MODEL::TABLE:
		b = std::make_unique<TileNone>(p);
		if (Long)
		{
			if (TileMapBank[nextY][nextX]->GetMode() != TILE_MODEL::BOX)
			{
				p = { nextX * 2.0f,0.0f,nextY * 2.0f };
				b2 = std::make_unique<TileNone>(p);
				b->SetFriendOn(Long);
				b->SetFriendX(nextX);
				b->SetFriendY(nextY);

				b2->SetFriendOn(Long);
				b2->SetFriendX(x);
				b2->SetFriendY(y);
			}
			else
			{
				nextBild = false;
			}
		}
		break;
	default:
		b = std::make_unique<TileNone>(p);
		break;
	}
	b->SetMode(TileMode);
	if (Long)b2->SetMode(TileMode);
	if (LvBank >= 1 || LvBank2 >= 1 || b->GetMode() == TILE_MODEL::SINK || b2->GetMode() == TILE_MODEL::SINK || modeBank == TILE_MODEL::SINK)
	{
		int jage = 0;
		if (TileMapBank[y][x]->GetFriendOn())
		{
			int nx = TileMapBank[y][x]->GetFriendX();
			int ny = TileMapBank[y][x]->GetFriendY();
			DirectX::XMFLOAT3 np = { nx * 2.0f,0.0f,ny * 2.0f };
			TileMapBank[ny][nx] = std::make_unique<TileNone>(np);
			change = false;
			jage++;
		}
		if (TileMapBank[nextY][nextX]->GetFriendOn())
		{
			int nx = TileMapBank[nextY][nextX]->GetFriendX();
			int ny = TileMapBank[nextY][nextX]->GetFriendY();
			DirectX::XMFLOAT3 np = { nx * 2.0f,0.0f,ny * 2.0f };
			TileMapBank[ny][nx] = std::make_unique<TileNone>(np);
			change = false;
			jage++;
		}
		if (jage == 2)
		{
			if (modeBank != TILE_MODEL::NONE)
			{
				if (modeBank != TileMode && TileMode != TILE_MODEL::NONE)
				{
					subtractionMoney -= ADD_MONEY[Lv];
				}
				subtractionMoney += ADD_MONEY[LvBank];
			}
		}
		else if (modeBank != TileMode || Lv != LvBank || Lv != LvBank2)
		{
			if (modeBank != TILE_MODEL::NONE)
			{
				if (TileMode != TILE_MODEL::NONE)
				{
					subtractionMoney -= ADD_MONEY[Lv];
				}
				subtractionMoney += ADD_MONEY[LvBank];
			}

		}
	}
	if (nextBild == false)
	{
		TileMapBank[y][x] = std::make_unique<TileNone>(p);
		return;
	}
	if (change)
	{
		{
			if (modeBank != TILE_MODEL::NONE)
			{
				if (modeBank != TileMode && TileMode != TILE_MODEL::NONE || LvBank != Lv && TileMode != TILE_MODEL::NONE)
				{
					subtractionMoney -= ADD_MONEY[Lv];
				}
				else if (modeBank == TileMode && TileMode != TILE_MODEL::NONE || LvBank == Lv && TileMode != TILE_MODEL::NONE)
				{
					subtractionMoney -= ADD_MONEY[Lv];
				}
				subtractionMoney += ADD_MONEY[LvBank];
			}
			else
			{
				subtractionMoney -= ADD_MONEY[Lv];
			}
		}
	}

	TileMapBank[y][x] = nullptr;
	TileMapBank[y][x] = std::move(b);
	TileMapBank[y][x]->SetMode(TileMode);
	if (Long)
	{
		TileMapBank[nextY][nextX] = std::move(b2);
		TileMapBank[nextY][nextX]->SetMode(TileMode);

		TileMapBank[y][x]->SetFriendOn(true);
		TileMapBank[y][x]->SetFriendX(nextX);
		TileMapBank[y][x]->SetFriendY(nextY);

		TileMapBank[nextY][nextX]->SetFriendOn(true);
		TileMapBank[nextY][nextX]->SetFriendX(x);
		TileMapBank[nextY][nextX]->SetFriendY(y);
	}
}

void StageManager::Update(float elapsedTime, DishManager* DM, Player* P,FoodManager* F)
{
	timer += 1;
	if (build)
	{
		cursor->Update(elapsedTime, x, y);
		if (key->GetKeyDown('E'))
		{
			if (TileMode == 0)
			{
				TileMode = TILE_MODEL::BOARD;
			}
			else
			{
				TileMode++;
			}
			if (TileMode > TILE_MODEL::TABLE)
			{
				TileMode = 0;
			}
		}
		if (key->GetKeyDown('Q'))
		{
			if (TileMode == TILE_MODEL::BOARD)
			{
				TileMode = 0;
			}
			else
			{
				TileMode--;
			}
			if (TileMode < 0)
			{
				TileMode = TILE_MODEL::TABLE;
			}
		}
		if (key->GetKeyDown('1'))
		{
			Lv = 0;
		}
		if (key->GetKeyDown('2'))
		{
			Lv = 1;
		}
		if (key->GetKeyDown('3'))
		{
			Lv = 2;
		}

		if (key->GetKeyDown('R') && Lv != 0)
		{
			if (Long == false)
			{
				Long = true;
			}
			else
			{
				Long = false;

			}
		}
		if (Long == true)
		{
			nextX = x + 1;
			nextY = y;
		}
		else
		{
			nextX = 0;
			nextY = 0;
		}

		if (Lv == 0)
		{
			Long = false;
		}

		if (TileMode == TILE_MODEL::SINK)
		{
			Long = true;
			if (Lv == 2) Lv = 1;
		}
		if (TileMode == TILE_MODEL::NONE)
		{
			Long = false;
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (x != oldX || y != oldY || oldTileMode != TileMode || oldLv != Lv)
			{
				SetMapTip();
			}
		}
		if (PlayerPos != -1)
		{
			P->SetPosition(tileMapBox[PlayerPos]->GetPosition());
			PlayerPos = -1;
		}
	}
	else
	{
		for (int i = 0; i < tileMapUtensils.size(); i++)
		{
			if (tileMapUtensils[i]->GetLv() == 0 &&
				GetAsyncKeyState('E') & 0x8000 ||
				tileMapUtensils[i]->GetLv() == 1 ||
				tileMapUtensils[i]->GetLv() == 2)
			{
				int a = tileMapUtensils[i]->GetMode();
				switch (a)
				{
				case TILE_MODEL::SINK:
					if (tileMapUtensils[i]->GetRight())
					{
						tileMapUtensils[i]->Update(elapsedTime, DM,P);
					}
					break;
				case TILE_MODEL::RETURN_DISH:
					tileMapUtensils[i]->Update(elapsedTime, DM,P);
					break;
				case TILE_MODEL::OFFER:
					//TODO オーダーどうりの商品が提供されたら
					if (Collision::IntersectBoxVsCylinder(
						tileMapUtensils[i]->GetPosition(),
						tileMapUtensils[i]->GetLength(),
						P->GetPosition(),
						P->GetRadius(),
						P->GetHeight()) &&
						P->getIng() != nullptr)
					{
						F->RemoveFood(P->getIng());
						P->getDish()->setLv(1);
						P->setScore(1000);
						P->getDish()->SetIsGrund(false);
						P->getDish()->setOndishFood(nullptr);
						//DM->getDish()->setOndishFood(nullptr);
						P->SetFood(nullptr);
						P->SetDish(nullptr);

					}
					break;
				case TILE_MODEL::STOVE:
					[[fallthrough]];
				case TILE_MODEL::POT:
					[[fallthrough]];
				case TILE_MODEL::BOARD:
					[[fallthrough]];
				case TILE_MODEL::KETCHUP:
					[[fallthrough]];
				case TILE_MODEL::DEMI:
					[[fallthrough]];
				case TILE_MODEL::WHITE:
					if (Collision::IntersectBoxVsCylinder(
						tileMapUtensils[i]->GetPosition(),
						tileMapUtensils[i]->GetLength(),
						P->GetPosition(),
						P->GetRadius(),
						P->GetHeight()) && 
						tileMapUtensils[i]->SetFood(P->getIng()))
					{
						P->getIng()->SetUtensils(true);
						for (int j = 0; j < F->GetFoodCount(); j++)
						{
							if (F->GetFood(j) == P->getIng())
							{
								P->SetFood(nullptr);
								DirectX::XMFLOAT3 pos{tileMapUtensils[i]->GetPosition()};
								pos.y = -1;
								F->GetFood(j)->setPosition(pos);
							}
						}
					}
					tileMapUtensils[i]->Update(elapsedTime, F,P);
					break;
				}
			}
		}
		if (key->GetKeyDown('E'))
		{
			for (int i = 0; i < tileMapBox.size(); i++)
			{
				if (tileMapBox[i]->GetLv() == 0 &&
					Collision::IntersectBoxVsCylinder(
						tileMapBox[i]->GetPosition(),
						tileMapBox[i]->GetLength(),
						P->GetPosition(),
						P->GetRadius(),
						P->GetHeight()) ||
					tileMapBox[i]->GetLv() == 1 ||
					tileMapBox[i]->GetLv() == 2)
				{
					std::unique_ptr<Ingredients> food;
					switch (tileMapBox[i]->GetMode())
					{
					case TILE_MODEL::RICE:
						food = std::make_unique<Rice>();
						break;
					case TILE_MODEL::ONION:
						food = std::make_unique<Onion>();
						break;
					case TILE_MODEL::EGG:
						food = std::make_unique<Egg>();
						break;
					//case TILE_MODEL::TOMATO:
					//	food = std::make_unique<Tomato>();
					//	break;
					case TILE_MODEL::PLAYER:
						continue;
						break;
					default:
						break;
					}
					P->SetFood(food.get());
					F->SetFood(std::move(food));
				}
			}
		}
	}
}

void StageManager::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	//floor->Render(rc, renderer);
	if (build)
	{
		cursor->Render(rc, renderer);

		for (int i = 0; i < TileMapBank.size(); i++)
		{
			for (int j = 0; j < TileMapBank[i].size(); j++)
			{
				if (TileMapBank[i][j].get() != nullptr)
				{
					TileMapBank[i][j]->Render(rc, renderer);
				}
			}
		}
		for (auto& a : tileMapBox)
		{
			a->Render(rc,renderer);
		}
	}
	else
	{
		for (const auto& m : tileMapBox)
		{
			if (m->GetMode() == TILE_MODEL::PLAYER)
			{
				continue;
			}
			m->Render(rc, renderer);
		}
		for (const auto& m : tileMapUtensils)
		{
			m->Render(rc, renderer);
		}
	}
#ifdef DEBUG
	//なんかのポジションを取ってくる
	ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
	//表示場所
	ImGui::SetNextWindowPos(ImVec2(pos.x + 100, pos.y + 100), ImGuiCond_Once);
	//大きさ
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("TileMap", nullptr, ImGuiWindowFlags_None))
	{
		//トランスフォーム
		//if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::InputInt("money", &subtractionMoney);
			ImGui::InputInt("Lv", &Lv);
			ImGui::InputInt("Mode", &TileMode);
			ImGui::Checkbox("Long", &Long);

		}
	}
	ImGui::End();

	if (ImGui::Begin("camera", nullptr, ImGuiWindowFlags_None))
	{
		ImGui::Text("view");
		for (int i = 0; i < 4; i++)
		{
			// 各行をまとめて編集できるようにする
			ImGui::Text("%.3f/ %.3f/ %.3f/ %.3f/",
				rc.view.m[i][0], rc.view.m[i][1], rc.view.m[i][2], rc.view.m[i][3]);
		}
		ImGui::Text("projection");
		for (int i = 0; i < 4; i++)
		{
			// 各行をまとめて編集できるようにする
			ImGui::Text("%.3f/ %.3f/ %.3f/ %.3f/",
				rc.projection.m[i][0], rc.projection.m[i][1], rc.projection.m[i][2], rc.projection.m[i][3]);
		}
	}
	ImGui::End();

#endif // DEBUG


}

void StageManager::Render2D(const RenderContext& rc)
{
	for (int i = 0; i < tileMapUtensils.size(); i++)
	{
		if (tileMapUtensils[i]->GetMode() == TILE_MODEL::SINK && tileMapUtensils[i]->GetRight() == false ||
			tileMapUtensils[i]->GetMode() == TILE_MODEL::RETURN_DISH ||
			tileMapUtensils[i]->GetMode() == TILE_MODEL::OFFER)
		{
			continue;
		}
		if (tileMapUtensils[i].get() != nullptr)
		{
			// スクリーンサイズ取得
			float screenWidth = Graphics::Instance().GetScreenWidth();
			float screenHeight = Graphics::Instance().GetScreenHeight();

			DirectX::XMMATRIX View = DirectX::XMLoadFloat4x4(&rc.view);
			DirectX::XMMATRIX Projection = DirectX::XMLoadFloat4x4(&rc.projection);
			DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();

			//頭上のワールド座標
			DirectX::XMFLOAT3 spritPosition = tileMapUtensils[i]->GetPosition();
			spritPosition.y += 3.0f;

			//ワールド座標からスクリーン座標に変換
			DirectX::XMVECTOR ScreenPosition, WorldPosition;
			WorldPosition = DirectX::XMLoadFloat3(&spritPosition);

			ScreenPosition = DirectX::XMVector3Project(
				WorldPosition,
				0.0f, 0.0f,
				screenWidth, screenHeight,
				0.0f, 1.0f,
				Projection,
				View,
				World
			);

			//スクリーン座標
			DirectX::XMFLOAT2 screenPosition;
			DirectX::XMStoreFloat2(&screenPosition, ScreenPosition);

			//ゲージ描画
			const float grugeWidth = 30.0f;
			const float grugeHeight = 5.0f;

			//線形補完関数
			//v1～v2までの値をtを使って計算する
			auto lerp = [](float v1, float v2, float t) -> float
				{
					return (1.0f - t) * v1 + t * v2;
				};

			float sx = lerp(0, grugeWidth, (tileMapUtensils[i]->GetCookingTimer() / tileMapUtensils[i]->GetCookingTimerBank()));
			//float sx = grugeWidth * (tileMapUtensils[i]->GetCookingTimer() / tileMapUtensils[i]->GetCookingTimerBank());

			////イージング関数
			//auto easeOutBounce = [](float x) -> float
			//	{
			//		return x < 0.5 ? 4 * x * x * x : 1 - std::pow(-2 * x + 2, 3) / 2;
			//	};

			sprite->Render(rc,
				screenPosition.x - grugeWidth / 2, screenPosition.y,
				0.0f,
				sx, grugeHeight,
				0.0f,
				1.0f, 1.0f, 1.0f, 1.0f);
			if (tileMapUtensils[i]->GetWarningTime() > 0)
			{
				if (timer % 10 == 0)
				{
					A = !A;
				}
				spriteWarning->Render(rc,
					screenPosition.x - 100 / 2, screenPosition.y,
					0.0f,
					100, 100,
					0.0f,
					1.0f, 1.0f, 1.0f, static_cast<float>(A));
			}
		}
	}
}

void StageManager::RenderDebugPrimitive(const RenderContext& rc, ShapeRenderer* renderer)
{
	for (const auto& m : tileMapBox)
	{
		m->RenderDebugPrimitive(rc, renderer);
	}
}

void StageManager::BuildingMap()
{
	tileMapUtensils.clear();
	int count = 0;
	for (int i = 0; i < TileMapBank.size(); i++)
	{
		for (int j = 0; j < TileMapBank[i].size(); j++)
		{
			DirectX::XMFLOAT3 p = { j * 2.0f,0.0f,i * 2.0f };
			if (TileMapBank[i][j] != nullptr)
			{
				switch (TileMapBank[i][j]->GetMode())
				{
				case TILE_MODEL::NONE:
					continue;
				case TILE_MODEL::BOARD:
					tileMapUtensils.push_back(std::make_unique<Board>(p, TileMapBank[i][j]->GetLv(), TileMapBank[i][j]->GetFriendOn(), TileMapBank[i][j]->GetRight()));
					break;
				case TILE_MODEL::POT:
					tileMapUtensils.push_back(std::make_unique<Pot>(p, TileMapBank[i][j]->GetLv(), TileMapBank[i][j]->GetFriendOn(), TileMapBank[i][j]->GetRight()));
					break;
				case TILE_MODEL::SINK:
					tileMapUtensils.push_back(std::make_unique<Sink>(p, TileMapBank[i][j]->GetLv(),TileMapBank[i][j]->GetRight()));
					break;
				case TILE_MODEL::STOVE:
					tileMapUtensils.push_back(std::make_unique<Stove>(p, TileMapBank[i][j]->GetLv(), TileMapBank[i][j]->GetFriendOn(), TileMapBank[i][j]->GetRight()));
					break;
				case TILE_MODEL::TABLE:
					//tileMapUtensils.push_back(std::make_unique<Stove>(p, TileMapBank[i][j]->GetLv()));
					break;
				case TILE_MODEL::OFFER:
					tileMapUtensils.push_back(std::make_unique<Submission>(p, TileMapBank[i][j]->GetLv()));
					break;
				case TILE_MODEL::RETURN_DISH:
					tileMapUtensils.push_back(std::make_unique<CreateDishBox>(p, TileMapBank[i][j]->GetLv()));
					break;
				case TILE_MODEL::KETCHUP:
					tileMapUtensils.push_back(std::make_unique<KetuchupBox>(p, TileMapBank[i][j]->GetMode()));
					break;
				case TILE_MODEL::DEMI:
					tileMapUtensils.push_back(std::make_unique<DemiBox>(p, TileMapBank[i][j]->GetMode()));
					break;
				case TILE_MODEL::WHITE:
					tileMapUtensils.push_back(std::make_unique<WhiteBox>(p, TileMapBank[i][j]->GetMode()));
					break;
				//case TILE_MODEL::BACON:
				//	tileMapBox.push_back(std::make_unique<BaconBox>(p));
				//	break;
				//case TILE_MODEL::STOVE:
				//	tileMapUtensils.push_back(std::make_unique<Stove>(p, TileMapBank[i][j]->GetLv()));
				//	break;
				}
				if (TileMapBank[i][j]->GetFriendOn())
				{
					tileMapUtensils[count]->SetFriendX(TileMapBank[i][j]->GetFriendX());
					tileMapUtensils[count]->SetFriendY(TileMapBank[i][j]->GetFriendY());
					tileMapUtensils[count]->SetFriendOn(TileMapBank[i][j]->GetFriendOn());
				}
				if (TileMapBank[i][j]->GetMode() != TILE_MODEL::NONE && TileMapBank[i][j]->GetMode() != TILE_MODEL::BOX)
				{
					tileMapUtensils[count]->SetMode(TileMapBank[i][j]->GetMode());
					count++;
				}
			}
		}
	}
}
