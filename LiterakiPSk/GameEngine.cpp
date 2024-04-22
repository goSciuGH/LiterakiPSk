#include "GameEngine.h"
#include "Tile.h"
#include "Board.h"

#include <ctime>
#include <cstdlib>

GameEngine::GameEngine()
{
	mainWindow.create(sf::VideoMode(windowW, windowH), "SFML works!");
	view.reset(sf::FloatRect(0, 0, FULLRES_W, FULLRES_H));
	view.setCenter(FULLRES_W / 2.0, FULLRES_H / 2.0);
	mainWindow.setView(view);

	mainWindow.setVerticalSyncEnabled(false);	// ustawiæ na true, ¿eby w³¹czyæ VSync i zablokowaæ na ~60 FPS
	mainWindow.setKeyRepeatEnabled(false);		// false - event wciœniêcia tylko na pierwszej klatce; true - event wciœniêcia na ka¿dej klatce

	dictionary.engine = this;
	isDictionaryLoaded = false;
	bool tempValue = isDictionaryLoaded.load();
	dictionary.loadDictionary("dictionaries/en_US.txt", tempValue);

	Board* playboard = new Board(-1, sf::Vector2f(432.0f, 12.0f), "playboard");
	addObject(playboard);

	for (int i = 0; i < 7; i++)
	{
		onBoardTiles[i] = nullptr;
	}

	std::wifstream letterSet("letterSets/en_US.csv");

	if (!letterSet.is_open())
	{
		std::cerr << "Blad wczytywania zestawu liter" << std::endl;
	}

	std::wstring line;
	while (std::getline(letterSet, line))
	{
		std::wstringstream lineStream(line);
		wchar_t letter;
		unsigned int value, howMany;

		if (lineStream >> letter && lineStream.ignore() && lineStream >> value && lineStream.ignore() && lineStream >> howMany)
		{
			for (unsigned int i = 0; i < howMany; ++i)
			{
				blueprintBag.emplace_back(letter, value);
			}
		}
	}

	letterSet.close();
	for (const auto& entry : blueprintBag) {
		std::wcout << "Letter: " << entry.first << ", Points: " << entry.second << std::endl;
	}

	std::copy(blueprintBag.begin(), blueprintBag.end(), std::back_inserter(gameBag));
}

GameEngine::~GameEngine()
{
	for (auto obj : objectSet)
	{
		delete obj;
	}
}

void GameEngine::run()
{
	readInput();
	updateLogic();
	//updatePhysics();
	updateGraphics();
	//updateAudio();

	gameTime = gameClock.getElapsedTime();
	delta = gameTime - lastFrameTime;
	lastFrameTime = gameTime;
}

void GameEngine::addObject(GameObject* obj)
{
	objectSet.insert(obj);
}

void GameEngine::addTile(int player, int slot, Tile* obj)
{
	playerRackTiles[player][slot] = obj;
}

void GameEngine::readInput()
{
	while (mainWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			textures.clear();

			dictionary.waitForLoading();
			mainWindow.close();
		}

		if (gameState == 2)
		{
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				std::cout << "Click!\n";

				if (heldTile == nullptr)	//podnieœ kostkê
				{
					sf::Vector2i mousePosition = sf::Mouse::getPosition(mainWindow);
					mousePosition.x /= windowScale;
					mousePosition.y /= windowScale;

					for (int i = 0; i < 7; i++)
					{
						if (playerRackTiles[activePlayer][i] != nullptr)
						{
							sf::FloatRect spriteBounds = playerRackTiles[activePlayer][i]->sprites[0].getGlobalBounds();

							if (spriteBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
							{
								std::cout << "Sprite clicked!\t" << i << "\n";
								heldTile = playerRackTiles[activePlayer][i];
								for (auto& spr : heldTile->sprites)
								{
									spr.setScale(1.0f, 1.0f);
								}
								playerRackTiles[activePlayer][i] = nullptr;
								break;
							}
						}
					}
					for (int i = 0; i < 7; i++)
					{
						if (onBoardTiles[i] != nullptr)
						{
							sf::FloatRect spriteBounds = onBoardTiles[i]->sprites[0].getGlobalBounds();

							if (spriteBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
							{
								// The sprite is clicked
								std::cout << "Sprite clicked!\t" << i << "\n";
								heldTile = onBoardTiles[i];
								for (auto& spr : heldTile->sprites)
								{
									spr.setScale(1.0f, 1.0f);
								}
								onBoardTiles[i] = nullptr;
								break;
							}
						}
					}
				}
				else	// upuœæ kostkê
				{
					if ((heldTile->pos.x >= 418.0f && heldTile->pos.x < 1438.0f) && (heldTile->pos.y >= -2.0f && heldTile->pos.y < 1018.0f))
					{
						// min: 418, -2
						//0-0: 452, 32
						//1-0: 520, 32
						//14-14: 1404, 984
						// max: 1438, 1018

						std::cout << "[" << heldTile->pos.x << ", " << heldTile->pos.y << "]\t";
						sf::Vector2f tempPos = heldTile->pos - sf::Vector2f(418.0f, -2.0f);
						tempPos = tempPos - sf::Vector2f(std::fmod(tempPos.x, 68.0f), std::fmod(tempPos.y, 68.0f));
						tempPos = sf::Vector2f(round(tempPos.x / 68), round(tempPos.y / 68));

						heldTile->pos = sf::Vector2f(452.0f, 32.0f) + 68.0f * tempPos;

						for (auto& spr : heldTile->sprites)
						{
							spr.setPosition(heldTile->pos);
						}
						heldTile->letterVisual.setPosition(heldTile->pos + sf::Vector2f(32.0f, 32.0f));

						for (int i = 0; i < 7; i++)
						{
							if (onBoardTiles[i] == nullptr)
							{
								onBoardTiles[i] = heldTile;
								std::cout << "onBoardTiles[" << i << "] - " << onBoardTiles[i]->layer << std::endl;
								break;
							}
						}

						std::cout << "<" << tempPos.x << ", " << tempPos.y << ">" << std::endl;
					}
					else
					{
						for (auto& spr : heldTile->sprites)
						{
							spr.setScale(2.0f, 2.0f);
						}

						// 0: -16, 56
						// 6: -16, 896

						double tempX = activePlayer * 1824.0f - 16.0f;

						if (heldTile->pos.y < 24)
						{
							heldTile->rackPos = 0;
							if (playerRackTiles[activePlayer][0] != nullptr)
							{
								int i = 1;
								for (i; i < 7; i++)
								{
									if (playerRackTiles[activePlayer][i] == nullptr)
									{
										break;
									}
								}
								for (i; i > 0; i--)
								{
									playerRackTiles[activePlayer][i] = playerRackTiles[activePlayer][i - 1];
									playerRackTiles[activePlayer][i - 1] = nullptr;
								}
							}
							playerRackTiles[activePlayer][0] = heldTile;
						}
						else if (heldTile->pos.y >= 928)
						{
							heldTile->rackPos = 6;
							if (playerRackTiles[activePlayer][6] != nullptr)
							{
								int i = 5;
								for (i; i >= 0; i--)
								{
									if (playerRackTiles[activePlayer][i] == nullptr)
									{
										break;
									}
								}
								for (i; i < 6; i++)
								{
									playerRackTiles[activePlayer][i] = playerRackTiles[activePlayer][i + 1];
									playerRackTiles[activePlayer][i + 1] = nullptr;
								}
							}
							playerRackTiles[activePlayer][6] = heldTile;
						}
						else
						{
							double tempRackPos = heldTile->pos.y - 24.0f;
							double temptempPos = tempRackPos;
							tempRackPos -= std::fmod(tempRackPos, 140.0f);
							tempRackPos = round(tempRackPos / 140.0f);
							int tRP = tempRackPos;

							if (playerRackTiles[activePlayer][tRP] != nullptr)
							{
								if (std::fmod(temptempPos, 140.0f) < 70)	// chce isc ku gorze
								{
									int i = tempRackPos;
									for (i; i >= 0; i--)
									{
										if (playerRackTiles[activePlayer][i] == nullptr)
										{
											break;
										}
										if (i == 0)	// nie ma miejsca ku gorze, patrz w dol
										{
											i = tempRackPos;
											for (i; i < 7; i++)
											{
												if (playerRackTiles[activePlayer][i] == nullptr)
												{
													break;
												}
											}
											break;
										}
									}
									if (i < tempRackPos) // spychaj do gory
									{
										for (i; i < 6; i++)
										{
											playerRackTiles[activePlayer][i] = playerRackTiles[activePlayer][i + 1];
											playerRackTiles[activePlayer][i + 1] = nullptr;
										}
									}
									else
									{
										for (i; i > 0; i--)
										{
											playerRackTiles[activePlayer][i] = playerRackTiles[activePlayer][i - 1];
											playerRackTiles[activePlayer][i - 1] = nullptr;
										}
									}
								}
								else
								{
									int i = tempRackPos;
									for (i; i < 7; i++)
									{
										if (playerRackTiles[activePlayer][i] == nullptr)
										{
											break;
										}
										if (i == 6)	// nie ma miejsca w dol, patrz w gore
										{
											i = tempRackPos;
											for (i; i >= 0; i)
											{
												if (playerRackTiles[activePlayer][i] == nullptr)
												{
													break;
												}
											}
											break;
										}
									}
									if (i < tempRackPos) // spychaj do gory
									{
										for (i; i < 6; i++)
										{
											playerRackTiles[activePlayer][i] = playerRackTiles[activePlayer][i + 1];
											playerRackTiles[activePlayer][i + 1] = nullptr;
										}
									}
									else
									{
										for (i; i > 0; i--)
										{
											playerRackTiles[activePlayer][i] = playerRackTiles[activePlayer][i - 1];
											playerRackTiles[activePlayer][i - 1] = nullptr;
										}
									}
								}
							}
							playerRackTiles[activePlayer][tRP] = heldTile;
						}
					}

					heldTile = nullptr;
				}
			}
		}
	}
}

void GameEngine::updateLogic()
{
	if (heldTile != nullptr)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(mainWindow);
		mousePos.x /= windowScale;
		mousePos.y /= windowScale;
		heldTile->pos = sf::Vector2f(static_cast<float>(mousePos.x) - 48.0, static_cast<float>(mousePos.y) - 48.0);

		for (auto& spr : heldTile->sprites)
		{
			spr.setPosition(heldTile->pos);
		}
		heldTile->letterVisual.setPosition(heldTile->pos + sf::Vector2f(32.0f, 32.0f));
	}

}

void GameEngine::updatePhysics()
{
}

void GameEngine::giveTiles()
{
	for (int i = 0; i < 7; i++)
	{
		Tile* newTile = new Tile(300 + i, sf::Vector2f(-16.0f, 56.0 + 140.0f * i), "tileBase");
		newTile->rackPos = i;
		for (auto& spr : newTile->sprites)
		{
			spr.setScale(2.0f, 2.0f);
		}

		int bagSize = gameBag.size();
		int randLetter = rand() % bagSize;
		newTile->letterLogic = gameBag[randLetter];
		gameBag.erase(gameBag.begin() + randLetter);

		newTile->letterVisual.setFont(fonts["Lexend"]);
		newTile->letterVisual.setString(newTile->letterLogic.first);
		newTile->letterVisual.setCharacterSize(64);
		newTile->letterVisual.setFillColor(sf::Color::Black);
		newTile->letterVisual.setStyle(sf::Text::Bold);
		newTile->letterVisual.setPosition(newTile->pos + sf::Vector2f(32.0f, 32.0f));

		addObject(newTile);
		addTile(0, i, newTile);
	}

	for (int i = 0; i < 7; i++)
	{
		Tile* newTile = new Tile(300 + i, sf::Vector2f(1808.0f, 56.0 + 140.0f * i), "tileBase");
		newTile->rackPos = i;
		for (auto& spr : newTile->sprites)
		{
			spr.setScale(2.0f, 2.0f);
		}

		int bagSize = gameBag.size();
		int randLetter = rand() % bagSize;
		newTile->letterLogic = gameBag[randLetter];
		gameBag.erase(gameBag.begin() + randLetter);

		newTile->letterVisual.setFont(fonts["Lexend"]);
		newTile->letterVisual.setString(newTile->letterLogic.first);
		newTile->letterVisual.setCharacterSize(64);
		newTile->letterVisual.setFillColor(sf::Color::Black);
		newTile->letterVisual.setStyle(sf::Text::Bold);
		newTile->letterVisual.setPosition(newTile->pos + sf::Vector2f(32.0f, 32.0f));

		addObject(newTile);
		addTile(1, i, newTile);
	}
}

void GameEngine::updateGraphics()
{
	mainWindow.clear();

	if (isDictionaryLoaded && gameState == 0)
	{
		gameState = 1;
	}

	for (auto* obj : objectSet)
	{
		auto it = std::find(obj->myClasses.begin(), obj->myClasses.end(), "DrawableObject");
		if (it != obj->myClasses.end())
		{
			obj->updateSelf(mainWindow, delta);
			obj->drawSelf(mainWindow);
		}
		else
		{
		}
	}

	if (gameState == 2)
	{
		if (loadScr != nullptr)
		{
			unsigned long long targetID = loadScr->objID;

			auto it = std::find_if(objectSet.begin(), objectSet.end(), [targetID](GameObject* obj){ return obj->getID() == targetID; });
			if (it != objectSet.end())
			{
				delete* it;
				objectSet.erase(it);
				loadScr = nullptr;
			}
		}
	}

	mainWindow.display();
}

void GameEngine::updateAudio()
{
}
