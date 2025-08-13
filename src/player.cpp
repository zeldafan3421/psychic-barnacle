#include "player.h"

Player::Player() : m_Controller(), m_Base(), m_Graphics(), m_CommandData()
{
    m_Controller.bindCommand(KEY_A, m_CommandData.allocate<PlayerMoveCommand>(&m_Base, PlayerMoveCommand::LEFT));
    m_Controller.bindCommand(KEY_D, m_CommandData.allocate<PlayerMoveCommand>(&m_Base, PlayerMoveCommand::RIGHT));
    m_Controller.bindCommand(KEY_W, m_CommandData.allocate<PlayerMoveCommand>(&m_Base, PlayerMoveCommand::UP));
    m_Controller.bindCommand(KEY_S, m_CommandData.allocate<PlayerMoveCommand>(&m_Base, PlayerMoveCommand::DOWN));
}

void Player::update()
{
    m_Controller.handleInput();
    m_Base.update();
}

void Player::draw() const
{
    m_Graphics.draw(m_Base.getPosition());
}

Player::operator Entity()
{
    return m_Base;
}
