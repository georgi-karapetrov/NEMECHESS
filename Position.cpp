#include "Position.h"

using std::istream;
using std::ostream;

Position::Position(const int x, const int y)
    : m_x( x ),
      m_y( y )
{
}

Position::Position(const Position& other)
{
    copy( other );
}

Position::~Position()
{
 //   cout << "~Position()\n";
}

Position& Position::operator=( const Position& other )
{
    if ( this != &other )
    {
        copy( other );
    }
    return *this;
}

Position Position::operator+( const Position& rhs )
{
    return Position( this->x() + rhs.x(), this->y() + rhs.y() );
}

istream& operator>>( istream& is, Position& position )
{
    int x, y;

    is >> x;
    is >> y;

    position.setX( x );
    position.setY( y );

    return is;
}

ostream& operator<<( ostream& os, const Position& position )
{
    os << position.x() << ", " << position.y();

    return os;
}

bool Position::operator==( const Position& rhs) const
{
    return this->x() == rhs.x() && this->y() == rhs.y();
}

bool Position::operator!=( const Position& rhs ) const
{
    return !( *this == rhs );
}

void Position::setX( const int x)
{
    m_x = x;
}

int Position::x() const
{
    return m_x;
}

void Position::setY( const int y )
{
    m_y = y;
}

int Position::y() const
{
    return m_y;
}

void Position::copy( const Position& other )
{
    if ( *this != other )
    {
        m_x = other.m_x;
        m_y = other.m_y;
    }
}
