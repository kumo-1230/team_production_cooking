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
#include "table.h"
#include "System/Audio.h"

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

	timer = 0;
	//�}�b�v���[�h
	{
		MapManager mapLoad;
		mapLoad.MapLoad(&mapLoad);
		mapLoad.AllMapSet(map);
	}

	spritePlus.reset(new Sprite("Data/Sprite/tipplus.png"));
	spriteMinus.reset(new Sprite("Data/Sprite/tipminus.png"));
	spriteNo.reset(new Sprite("Data/Sprite/notip.png"));
	spriteMiss.reset(new Sprite("Data/Sprite/missorder.png"));

	setUtensis = Audio::Instance().LoadAudioSource("Data/Sound/SetUtensils.wav");
	setUtensis->SetVolume(15);

	TileMapBank.resize(map.size());
	// �e�s���Ƃɗ���������inullptr�j
	for (size_t i = 0; i < map.size(); ++i)
	{
		TileMapBank[i].resize(map[i].size()); // �e�s�ɓ����񐔂��m��
		for (size_t j = 0; j < map[i].size(); ++j)
		{
			TileMapBank[i][j] = nullptr; // �����I��nullptr�ŏ�����
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
			case TILE_MODEL::TABLE:
				TileMapBank[i][j] = std::make_unique<TileBox>(p);
				tileMapBox.push_back(std::make_unique<Table>(p, 0,false,false));
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
	DirectX::XMFLOAT3 p = { x * 2.0f,0.0f,y * 2.0f };
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
		b = std::make_unique<Table>(p,0,false,false);
		//change = false;
		if (Long)
		{
			if (TileMapBank[nextY][nextX]->GetMode() != TILE_MODEL::BOX)
			{
				p = { nextX * 2.0f,0.0f,nextY * 2.0f };
				b2 = std::make_unique<Table>(p, 1, false, false);
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
			if (modeBank != TILE_MODEL::NONE && TileMode != TILE_MODEL::TABLE)
			{
				if (modeBank != TileMode && TileMode != TILE_MODEL::NONE && TileMode != TILE_MODEL::TABLE)
				{
					subtractionMoney -= ADD_MONEY[Lv];
				}
				subtractionMoney += ADD_MONEY[LvBank];
			}
		}
		else if (modeBank != TileMode || Lv != LvBank || Lv != LvBank2)
		{
			if (modeBank != TILE_MODEL::NONE && modeBank != TILE_MODEL::TABLE)
			{
				if (TileMode != TILE_MODEL::NONE && TileMode != TILE_MODEL::TABLE)
				{
					subtractionMoney -= ADD_MONEY[Lv];
				}
				subtractionMoney += ADD_MONEY[LvBank];
				change = false;
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
			if (modeBank != TILE_MODEL::NONE && modeBank != TILE_MODEL::TABLE)
			{
				if (modeBank != TileMode && TileMode != TILE_MODEL::NONE && TileMode != TILE_MODEL::TABLE ||
					LvBank != Lv && TileMode != TILE_MODEL::NONE && TileMode != TILE_MODEL::TABLE)
				{
					subtractionMoney -= ADD_MONEY[Lv];
				}
				else if (modeBank == TileMode && TileMode != TILE_MODEL::NONE && TileMode != TILE_MODEL::TABLE ||
					LvBank == Lv && TileMode != TILE_MODEL::NONE && TileMode != TILE_MODEL::TABLE)
				{
					subtractionMoney -= ADD_MONEY[Lv];
				}
				subtractionMoney += ADD_MONEY[LvBank];
			}
			else if(modeBank != TILE_MODEL::TABLE)
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
	timerCount += 1;
	if (build)
	{
		cursor->Update(elapsedTime, x, y);
		if (key->GetKeyDown('E'))
		{
			setUtensis->Play(false);
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
			setUtensis->Play(false);
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
			setUtensis->Play(false);
			Lv = 0;
		}
		if (key->GetKeyDown('2'))
		{
			setUtensis->Play(false);
			Lv = 1;
		}
		if (key->GetKeyDown('3'))
		{
			setUtensis->Play(false);
			Lv = 2;
		}

		if (key->GetKeyDown('R') && Lv != 0)
		{
			if (Long == false)
			{
				setUtensis->Play(false);
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
		if (TileMode == TILE_MODEL::NONE || TileMode == TILE_MODEL::TABLE)
		{
			Long = false;
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (x != oldX || y != oldY || oldTileMode != TileMode || oldLv != Lv)
			{
				setUtensis->Play(false);
				SetMapTip();
			}
		}
		if (PlayerPos != -1)
		{
			P->SetPosition(tileMapBox[PlayerPos]->GetPosition());
			PlayerPosBank = PlayerPos;
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
					//TODO �I�[�_�[�ǂ���̏��i���񋟂��ꂽ��
					if (Collision::IntersectBoxVsCylinder(
						tileMapUtensils[i]->GetPosition(),
						tileMapUtensils[i]->GetLength(),
						P->GetPosition(),
						P->GetRadius(),
						P->GetHeight()) &&
						P->getIng() != nullptr)
					{
						timer = 0;
						int removeIndex = -1;
						for (int i = 0; i < 4;i++)
						{
							if (P->getIng()->GetOmuType() == P->orderSlot[i])
							{
								removeIndex = i;
								break;
							}
						}
						if (removeIndex == -1)
						{
							TipRenderMiss = true;
							return;
						}
						if (P->orderTimer[removeIndex] <= 30)
						{
							TipRenderPlus = true;
							P->omu[P->orderSlot[removeIndex]-1].count++;
							P->omu[P->orderSlot[removeIndex]-1].charge += 1300;
							P->setScore(1300);
						}
						else if (P->orderTimer[removeIndex] >= 60)
						{
							TipRenderMinus = true;
							P->omu[P->orderSlot[removeIndex]-1].count++;
							P->omu[P->orderSlot[removeIndex]-1].charge += 700;
							P->setScore(700);
						}
						else
						{
							TipRenderNo = true;
							P->omu[P->orderSlot[removeIndex]-1].count++;
							P->omu[P->orderSlot[removeIndex]-1].charge += 1000;
							P->setScore(1000);
						}
						for (int i = removeIndex; i < 4 - 1; i++)
						{
							P->orderSlot[i] = P->orderSlot[i + 1];
							P->orderTimer[i] = P->orderTimer[i + 1];
						}
						P->orderSlot[3] = rand() % 3;
						F->RemoveFood(P->getIng());
						P->getDish()->setLv(1);
						P->getDish()->SetIsGrund(false);

						renderPosX = tileMapUtensils[i].get()->GetPosition().z;
						renderPosY = tileMapUtensils[i].get()->GetPosition().z;
						P->orderTimer[3] = 0;
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
					[[fallthrough]];
				case TILE_MODEL::TABLE:
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
								pos.y = 2;
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
					case TILE_MODEL::TOMATO:
						food = std::make_unique<Tomato>();
						break;
					case TILE_MODEL::RICE:
						food = std::make_unique<Rice>();
						break;
					case TILE_MODEL::ONION:
						food = std::make_unique<Onion>();
						break;
					case TILE_MODEL::EGG:
						food = std::make_unique<Egg>();
						break;
					case TILE_MODEL::PLAYER:
						continue;
						break;
					default:
						continue;
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
	floor->Render(rc, renderer);
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
	//�Ȃ񂩂̃|�W�V����������Ă���
	ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
	//�\���ꏊ
	ImGui::SetNextWindowPos(ImVec2(pos.x + 100, pos.y + 100), ImGuiCond_Once);
	//�傫��
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("TileMap", nullptr, ImGuiWindowFlags_None))
	{
		//�g�����X�t�H�[��
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
			// �e�s���܂Ƃ߂ĕҏW�ł���悤�ɂ���
			ImGui::Text("%.3f/ %.3f/ %.3f/ %.3f/",
				rc.view.m[i][0], rc.view.m[i][1], rc.view.m[i][2], rc.view.m[i][3]);
		}
		ImGui::Text("projection");
		for (int i = 0; i < 4; i++)
		{
			// �e�s���܂Ƃ߂ĕҏW�ł���悤�ɂ���
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
			tileMapUtensils[i]->GetMode() == TILE_MODEL::RETURN_DISH)
		{
			continue;
		}
		if (tileMapUtensils[i].get() != nullptr)
		{
			// �X�N���[���T�C�Y�擾
			float screenWidth = Graphics::Instance().GetScreenWidth();
			float screenHeight = Graphics::Instance().GetScreenHeight();

			DirectX::XMMATRIX View = DirectX::XMLoadFloat4x4(&rc.view);
			DirectX::XMMATRIX Projection = DirectX::XMLoadFloat4x4(&rc.projection);
			DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();

			//����̃��[���h���W
			DirectX::XMFLOAT3 spritPosition = tileMapUtensils[i]->GetPosition();
			spritPosition.y += 3.0f;

			//���[���h���W����X�N���[�����W�ɕϊ�
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

			//�X�N���[�����W
			DirectX::XMFLOAT2 screenPosition;
			DirectX::XMStoreFloat2(&screenPosition, ScreenPosition);

			if (tileMapUtensils[i].get()->GetMode() == TILE_MODEL::OFFER)
			{
				if (TipRenderPlus == true)
				{
					timer++;
					spritePlus->Render(rc, screenPosition.x - 200, screenPosition.y - timer* 0.5, 0, 360, 64, 0, 1, 1, 1, 1 - timer* 0.03f);
				}
				if (TipRenderMinus == true)
				{
					timer++;
					spritePlus->Render(rc, screenPosition.x - 200, screenPosition.y - timer * 0.5, 0, 360, 64, 0, 1, 1, 1, 1 - timer * 0.03f);
				}
				if (TipRenderNo == true)
				{
					timer++;
					spriteNo->Render(rc, screenPosition.x - 200, screenPosition.y - timer * 0.5, 0, 360, 64, 0, 1, 1, 1, 1 - timer * 0.03f);
				}
				if (TipRenderMiss == true)
				{
					timer++;
					spriteMiss->Render(rc, screenPosition.x - 200, screenPosition.y - timer * 0.5, 0, 360, 64, 0, 1, 1, 1, 1 - timer * 0.03f);
				}
				if (timer > 100)
				{
					TipRenderMinus = false;
					TipRenderPlus = false;
					TipRenderNo = false;
					TipRenderMiss = false;
				}
				return;
			}
			//�Q�[�W�`��
			const float grugeWidth = 30.0f;
			const float grugeHeight = 5.0f;

			//���`�⊮�֐�
			//v1�`v2�܂ł̒l��t���g���Čv�Z����
			auto lerp = [](float v1, float v2, float t) -> float
				{
					return (1.0f - t) * v1 + t * v2;
				};

			float sx = lerp(0, grugeWidth, (tileMapUtensils[i]->GetCookingTimer() / tileMapUtensils[i]->GetCookingTimerBank()));
			//float sx = grugeWidth * (tileMapUtensils[i]->GetCookingTimer() / tileMapUtensils[i]->GetCookingTimerBank());

			////�C�[�W���O�֐�
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
				if (timerCount % 10 == 0)
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
{

#ifdef DEBUG
		//�Ȃ񂩂̃|�W�V����������Ă���
		ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
		//�\���ꏊ
		ImGui::SetNextWindowPos(ImVec2(pos.x + 100, pos.y + 100), ImGuiCond_Once);
		//�傫��
		ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

		if (ImGui::Begin("TileMap", nullptr, ImGuiWindowFlags_None))
		{
			//�g�����X�t�H�[��
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
				// �e�s���܂Ƃ߂ĕҏW�ł���悤�ɂ���
				ImGui::Text("%.3f/ %.3f/ %.3f/ %.3f/",
					rc.view.m[i][0], rc.view.m[i][1], rc.view.m[i][2], rc.view.m[i][3]);
			}
		}
		ImGui::End();
#endif
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
					tileMapUtensils.push_back(std::make_unique<Table>(p, TileMapBank[i][j]->GetLv(), false, false));
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
				count = static_cast<int>(tileMapUtensils.size()) - 1;
				if (TileMapBank[i][j]->GetFriendOn())
				{
					tileMapUtensils[count]->SetFriendX(TileMapBank[i][j]->GetFriendX());
					tileMapUtensils[count]->SetFriendY(TileMapBank[i][j]->GetFriendY());
					tileMapUtensils[count]->SetFriendOn(TileMapBank[i][j]->GetFriendOn());
				}
				if (TileMapBank[i][j]->GetMode() != TILE_MODEL::NONE && TileMapBank[i][j]->GetMode() != TILE_MODEL::BOX && TileMapBank[i][j]->GetMode() != TILE_MODEL::TABLE)
				{
					tileMapUtensils[count]->SetMode(TileMapBank[i][j]->GetMode());
				}
			}
		}
	}
}

bool StageManager::BuildCheck()
{
	bool S = false,
		P = false,
		B = false,
		Si = false;

	for (int i = 0; i < TileMapBank.size(); i++)
	{
		for (int j = 0; j < TileMapBank[i].size(); j++)
		{
			switch (TileMapBank[i][j]->GetMode())
			{
			case TILE_MODEL::STOVE:
				S = true;
				break;
			case TILE_MODEL::SINK:
				Si = true;
				break;
			case TILE_MODEL::BOARD:
				B = true;
				break;
			case TILE_MODEL::POT:
				P = true;
				break;
			default:
				break;
			}
		}
	}
	return (S && P && B && Si);
}

void StageManager::CursorMode()
{
	//�J�[�\���ɍ��Ȃ�̊��I�΂�Ă��邩��\������
	switch (TileMode)
	{
	case TILE_MODEL::BOARD:
		break;
	case TILE_MODEL::TABLE:
		break;
	case TILE_MODEL::POT:
		break;
	case TILE_MODEL::STOVE:
		break;
	case TILE_MODEL::SINK:
		break;
	default:
		break;
	}
}
