#include "player.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsScene>
#include "enemy.h"
Player::Player(Enemy * enemy) : m_enemy(enemy)
{
    setRect(0, 0, 100, 100);
    setGravity(1);
    //make rect focusable so we can use keyboard events
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(30);
}

void Player::setGravity(int value)
{
    m_gravity = value;
}

int Player::gravity()
{
    return m_gravity;
}

Player::~Player()
{

}

void Player::move()
{
    if(gravity() == 1)
    {
        if(y() + rect().height() < scene()->height()) {
            setPos(x(), y() + 10);
        } else {
            // gameover
        }
    }
    else
    {
        if(y() > 0) {
            setPos(x(), y() - 10);
        } else {
            // gameover
        }

    }
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space) {
        setGravity(!gravity());
        QTimer::singleShot(500, m_enemy, SLOT(spaceEvent()));
    }


}
