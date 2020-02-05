#include <Light.h>


Light::Light(glm::vec3 pos, glm::vec3 col, glm::vec3 am_col, float shin)
{
	position = pos;
	color = col;
	ambient_color = am_col;
	shininess = shin;
}