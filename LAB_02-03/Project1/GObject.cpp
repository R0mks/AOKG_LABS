#include "GObject.h"
GObject::GObject() { 
	setPosition(0, 0, 0);
	setAngle(0);
	setColor(1.0f, 1.0f, 1.0f);
	setSize(1.0f);
}
GObject::GObject(GLfloat *pos, GLfloat ang, GLfloat *color, GLfloat size) {
	setPosition(pos[0],pos[1],pos[2]);
	setAngle(ang);
	setColor(color[0], color[1], color[2]);
	setSize(size);
}
void GObject::setPosition(GLfloat x, GLfloat y, GLfloat z) {
	position.x = x;
	position.y = y;
	position.z = z;
}
void GObject::setAngle(GLfloat degreeValue) {
	angle = degreeValue;
}
void GObject::setColor(GLfloat R, GLfloat G, GLfloat B) {
	R = R > 1 ? 1 : R < 0 ? 0 : R;
	G = G > 1 ? 1 : G < 0 ? 0 : G;
	B = B > 1 ? 1 : B < 0 ? 0 : B;
	color.R = R;
	color.G = G;
	color.B = B;
}
void GObject::setSize(GLfloat value = 1.0) {
	size = value <= 0 ? 1.0f : value;
}
void GObject::draw(void) {
	glPushMatrix();
	glColor3f(color.R, color.G, color.B);
	glTranslatef(position.x, position.y, position.z);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glutWireTeapot(size);
	glPopMatrix();
}
std::ostream& operator<<(std::ostream& out, const GObject object) {
	out << object.position.x << object.position.y << object.position.z << ", "
		<< object.angle << ", " << object.color.R << object.color.G << object.color.B << ", "
		<< object.size;
	return out;
};