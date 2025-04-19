#pragma once
#include "TkGui/TkGui_API.hpp"
#include "TkGui/Mathematics/TkVector.hpp"
#include "TkGui/Mathematics/TkColor.hpp"

namespace TkGui
{
	using letter = char;
	using letters = letter*;
	using text_t = const letters;
	using string_t = text_t;

	template<typename DataT>
	using Array = std::vector<DataT>;

	struct TKGUI_API Vertex
	{
	public:
		Vertex(Float32x3_t position, Float32x2_t uv, Float32x3_t color)
			: Position(position), UV(uv), Color(color)
		{ }
	public:
		Float32x3_t Position;
		Float32x2_t UV;
		Float32x3_t Color;
	};

	struct TKGUI_API Image
	{
	public:
		Image() : Width(0), Height(0), Channels(0), Pixels({}) {}
		Image(int32_t width, int32_t height, int32_t channels, const Array<Float32x4_t>& pixels) : Width(width), Height(height), Channels(channels), Pixels(pixels) {}
	public:
		int32_t Width;
		int32_t Height;
		int32_t Channels;
		Array<Float32x4_t> Pixels;
	};

	struct TKGUI_API Face
	{
	public:
		Face();
		Face(const Array<Vertex>& vertices, const Array<index_t>& indeces);
	public:
		Array<Vertex> Vertices;
		Array<index_t> Indeces;
	};

	struct TKGUI_API Object
	{
	public:
		Object();
		Object(const Array<Face>& faces, Image texture);
	public:
		~Object();
	public:
		Array<Face> Faces;
		Image Texture;
	};

	struct TKGUI_API DrawData
	{
	public:
		DrawData();
		DrawData(const Array<Object>& objects);
	public:
		~DrawData();
	public:
		Array<Object> Objects;
	};

	using TkGuiDrawData = DrawData;

	enum class Align : uint8_t
	{
		None	=	0b0000,
		Right	=	0b0001,
		Buttom	=	0b0010,
		Top		=	0b0100,
		Left	=	0b1000,
		Center	=	0b1111
	};

	/// <summary>
	/// Defines UI Object position
	/// </summary>
	struct TKGUI_API Transform
	{
	public:
		Transform();
		Transform(Float32x4_t rect, float32_t index);
		Transform(Float32x3_t position, Float32x2_t size);
		Transform(Float32x2_t position, float32_t index, Float32x2_t size);
		Transform(float32_t positionX, float32_t positionY, float32_t positionZ, float32_t sizeX, float32_t sizeY);
	public:
		~Transform();
	public:
		Float32x3_t Position;
		Float32x2_t Size;
	};

	// BackgroundSpecification, BackgroundProporties or BackgroundStyle
	/// <summary>
	/// 
	/// </summary>
	struct TKGUI_API BackgroundProperties
	{
	public:
		Float32x3_t Color;
		Image Image;
	};

	// Consider: TextSpecification, TextProporties or TextStyle
	/// <summary>
	/// 
	/// </summary>
	struct TKGUI_API TextProporties
	{
	public:
		text_t Text;
	};

	struct TKGUI_API ButtonProporties
	{
	public:
		bool CanClick;
	};
}