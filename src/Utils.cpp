#include "Tool.hpp"

void ZUtils::unProject(double in_x, double in_y, double *out_x, double *out_y)
{
        double pMatrix[16];
        double mvMatrix[16];
        int viewPort[4];
        glGetDoublev(GL_PROJECTION_MATRIX, pMatrix);
        glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
        glGetIntegerv(GL_VIEWPORT, viewPort);
        double Z;
        gluUnProject( in_x, viewPort[3] - in_y, 0, mvMatrix, pMatrix, viewPort, out_x, out_y, &Z);
}
