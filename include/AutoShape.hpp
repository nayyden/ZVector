#ifndef AUTOSHAPE_HPP
#define AUTOSHAPE_HPP

#include "Shape.hpp"

class AutoShape : public Shape
{
public:
        AutoShape(double origin_x, double origin_y, int vertices = 300);
        void setNumDetails(int);
        int getNumDetails();
        std::string toString();

protected:
	void resize(double x, double y);

private:
        void addVertices();
        void recalculateVertices();

	int m_majorRadius;
	int m_minorRadius;
        int m_numberOfVertices;
};


#endif // AUTOSHAPE_HPP
