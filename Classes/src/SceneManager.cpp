#include "SceneManager.h"

SceneManager::SceneManager() {}

SceneManager::SceneManager(sf::RenderWindow& window)
{
	MenuScene * menuScene = new MenuScene(window);
	m_scenes.push_back(menuScene);

	DungeonScene * dungeonScene = new DungeonScene(window);
	m_scenes.push_back(dungeonScene);

	m_currScene = menuScene;

	std::cout << "Current scene is " << m_currScene->GetName() << std::endl << std::endl;
}

SceneManager::~SceneManager()
{
	m_currScene = nullptr;
	for (int i = 0; i < m_scenes.size(); i++)
	{
		delete m_scenes.at(i);
		m_scenes.at(i) = nullptr;
	}
}

void SceneManager::Update(sf::Time dt)
{
	m_currScene->Update(dt);
}

void SceneManager::Render(sf::RenderWindow & window)
{
	m_currScene->Render(window);
}

void SceneManager::HandleInput()
{
	m_currScene->HandleInput();

	if (m_currScene->SwitchingScene().first == true)
		SwitchScene(m_currScene->SwitchingScene().second);
}

void SceneManager::SwitchScene(std::string scene)
{
	std::cout << "Switching scene from " << m_currScene->GetName() << " to " << scene << std::endl;
	bool found = false;
	Scene* nextScene = nullptr;

	for (int i = 0; i < m_scenes.size() && !found; i++)
	{
		if (m_scenes.at(i)->GetName() == scene)
		{
			found = true;
			nextScene = m_scenes.at(i);

			if (m_currScene != nullptr)
				m_currScene->Stop();

			if (nextScene->IsAlive() == false)
				nextScene->Start();

			m_currScene = nextScene;
			m_currScene->Start();
			std::cout << "Current scene is " << m_currScene->GetName() << std::endl << std::endl;
		}
	}
	
	if (!found) { std::cout << "Scene not found" << std::endl; }
}
