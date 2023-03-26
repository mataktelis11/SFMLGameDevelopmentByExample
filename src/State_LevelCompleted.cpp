#include "State_LevelCompleted.h"
#include "StateManager.h"

State_LevelCompleted::State_LevelCompleted(StateManager* l_stateManager)
    : BaseState(l_stateManager){}

State_LevelCompleted::~State_LevelCompleted(){}

void State_LevelCompleted::OnCreate(){

	m_bufferSuccessSound.loadFromFile(Utils::GetResourceDirectory() + "SoundEffects/chipquest.wav");
	m_SuccessSound.setBuffer(m_bufferSuccessSound);
	m_SuccessSound.setVolume(50.0f);

	m_font.loadFromFile(Utils::GetResourceDirectory() + "media/Fonts/arial.ttf");
	m_text.setFont(m_font);
	m_text.setString(sf::String("MAIN MENU:"));
	m_text.setCharacterSize(20);

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	m_text.setPosition(400,100);
	
	m_buttonSize = sf::Vector2f(300.0f,32.0f);
	m_buttonPos = sf::Vector2f(400,200);
	m_buttonPadding = 4; // 4px.

	std::string str[2];
	str[0] = "Play Next Level";
	str[1] = "Exit to Main Menu";

	for(int i = 1; i < 2; ++i){
		sf::Vector2f buttonPosition(
			m_buttonPos.x,m_buttonPos.y + 
			(i * (m_buttonSize.y + m_buttonPadding)));
		m_rects[i].setSize(m_buttonSize);
		m_rects[i].setFillColor(sf::Color::Red);

		m_rects[i].setOrigin(
			m_buttonSize.x / 2.0f, m_buttonSize.y / 2.0f);
		m_rects[i].setPosition(buttonPosition);

		m_labels[i].setFont(m_font);
		m_labels[i].setString(sf::String(str[i]));
		m_labels[i].setCharacterSize(20);

		sf::FloatRect rect = m_labels[i].getLocalBounds();
		m_labels[i].setOrigin(
			rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);

		m_labels[i].setPosition(buttonPosition);
	}

	EventManager* evMgr = m_stateMgr->
		GetContext()->m_eventManager;
	
	evMgr->AddCallback(StateType::LevelCompleted, "Mouse_Left", &State_LevelCompleted::MouseClick, this);
}

void State_LevelCompleted::OnDestroy(){
	EventManager* evMgr = m_stateMgr->
		GetContext()->m_eventManager;

	evMgr->RemoveCallback(StateType::LevelCompleted, "Mouse_Left");
}


void State_LevelCompleted::MouseClick(EventDetails* l_details){
	SharedContext* context = m_stateMgr->GetContext();
	sf::Vector2i mousePos = l_details->m_mouse;

	float halfX = m_buttonSize.x / 2.0f;
	float halfY = m_buttonSize.y / 2.0f;
	for(int i = 0; i < 2; ++i){
		if(mousePos.x>=m_rects[i].getPosition().x - halfX &&
			mousePos.x<=m_rects[i].getPosition().x + halfX &&
			mousePos.y>=m_rects[i].getPosition().y - halfY &&
			mousePos.y<=m_rects[i].getPosition().y + halfY)
		{
			if(i == 0){
				std::cout<<"next map"<<std::endl;
			} else if(i == 1){
				m_stateMgr->SwitchTo(StateType::MainMenu);
			}
		}
	}
}

void State_LevelCompleted::Draw(){
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();
	window->draw(m_text);
	for(int i = 0; i < 2; ++i){
		window->draw(m_rects[i]);
		window->draw(m_labels[i]);
	}
}


void State_LevelCompleted::Activate(){
	m_SuccessSound.play();
}

void State_LevelCompleted::Deactivate(){}
void State_LevelCompleted::Update(const sf::Time& l_time){}