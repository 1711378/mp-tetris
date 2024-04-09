#ifndef PUNT_H
#define PUNT_H



class Punt
{
public:
	Punt() : m_x(0), m_y(0) {  };
	Punt(int x, int y) : m_x(x), m_y(y) {};
	~Punt() { };

	int getX() const { return m_x; };
	int getY() const { return m_y; };

	void setX(int x) { m_x = x; };
	void setY(int y) { m_y = y; };
	void incX() { m_x++; };
	void incY() { m_y++; };
	void decY() { m_y--; };
private:
	int m_x;
	int m_y;
};

#endif