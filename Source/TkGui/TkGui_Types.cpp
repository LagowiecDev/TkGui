#include "TkGui/TkGui_Types.hpp"

namespace TkGui
{
	DrawData::DrawData()
		: Objects({})
	{

	}

	DrawData::DrawData(const Array<Object>& objects)
		: Objects(objects)
	{

	}

	DrawData::~DrawData()
	{

	}

	Transform::Transform()
		: Position({ 0,0,0 }), Size({0,0})
	{

	}

	Transform::Transform(Float32x4_t rect, float32_t index)
		: Position(rect.x - rect.z, rect.y - rect.w, index), Size(rect.x + rect.z, rect.y + rect.w)
	{

	}

	Transform::Transform(Float32x3_t position, Float32x2_t size)
		: Position(position), Size(size)
	{

	}

	Transform::Transform(Float32x2_t position, float32_t index, Float32x2_t size)
		: Position(position.x, position.y, index), Size(size)
	{

	}

	Transform::Transform(float32_t positionX, float32_t positionY, float32_t positionZ, float32_t sizeX, float32_t sizeY)
		: Position(positionX, positionY, positionZ), Size(sizeX, sizeY)
	{

	}

	Transform::~Transform()
	{

	}

	Object::Object()
		: Faces({}), Texture({})
	{

	}

	Object::Object(const Array<Face>& faces, Image texture)
		: Faces(faces), Texture(texture)
	{

	}

	Object::~Object()
	{

	}

	Face::Face()
		: Vertices({}), Indeces({})
	{

	}

	Face::Face(const Array<Vertex>& vertices, const Array<index_t>& indeces)
		: Vertices(vertices), Indeces(indeces)
	{
	
	}
}