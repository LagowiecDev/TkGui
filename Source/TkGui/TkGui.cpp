#include "TkGui/TkGui.hpp"
#include "TkGui/TkGui_Font.hpp"
#include "TkGui/TkGui_Image.hpp"

namespace TkGui
{
    void Begin()
    {
        if (s_wasInitialized)
        {
            return;
        }

        s_wasInitialized = 1;
        s_drawData.Objects = {};
    }

    void Panel(Transform transform, BackgroundProperties background)
    {
        if (!s_wasInitialized)
        {
            return;
        }

        s_drawData.Objects.push_back(
            Object
            {
                Array<Face>
                {
                    Face
                    {
                        Array<Vertex>
                        {
                            Vertex
                            {
                                Float32x3_t{ transform.Position.x + (transform.Size.x / 2.0f), transform.Position.y + (transform.Size.y / 2.0f), transform.Position.z },
                                Float32x2_t{ 1, 1 },
                                Float32x3_t{ background.Color.x, background.Color.y, background.Color.z }
                            },
                            Vertex
                            {
                                Float32x3_t{ transform.Position.x + (transform.Size.x / 2.0f), transform.Position.y - (transform.Size.y / 2.0f), transform.Position.z },
                                Float32x2_t{ 1, 0 },
                                Float32x3_t{ background.Color.x, background.Color.y, background.Color.z }
                            },
                            Vertex
                            {
                                Float32x3_t{ transform.Position.x - (transform.Size.x / 2.0f), transform.Position.y - (transform.Size.y / 2.0f), transform.Position.z },
                                Float32x2_t{ 0, 0 },
                                Float32x3_t{ background.Color.x, background.Color.y, background.Color.z }
                            },
                            Vertex
                            {
                                Float32x3_t{ transform.Position.x - (transform.Size.x / 2.0f), transform.Position.y + (transform.Size.y / 2.0f), transform.Position.z },
                                Float32x2_t{ 0, 1 },
                                Float32x3_t{ background.Color.x, background.Color.y, background.Color.z }
                            }
                        },
                        Array<index_t>
                        {
                            0, 1, 2,
                            2, 3, 0
                        }
                    }
                },
                background.Image
            }
        );
    }

    void Text(Transform transform, TextProporties text)
    {
        return;
    }


    void Label(Transform transform, BackgroundProperties background, TextProporties text)
    {
        Panel(transform, background);
        Text(transform, text);
    }

    bool Button(Transform transform, BackgroundProperties background, TextProporties text, ButtonProporties button)
    {
        Panel(transform, background);
        Text(transform, text);
        return 0;
    }

    void End()
    {
        if (!s_wasInitialized)
        {
            return;
        }

        s_wasInitialized = 0;
    }


	TkGuiDrawData GetDrawData()
	{
		return s_drawData;
	}
}