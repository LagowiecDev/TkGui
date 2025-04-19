#include "TkGui/TkGui.hpp"
#include "TkGui/TkGui_Font.hpp"
#include "TkGui/TkGui_Image.hpp"

namespace TkGui
{
    TKGUI_API Image LoadImage(string_t path)
    {
        Image img;

        int width, height, channels;
        unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
        if (!data)
        {
            return img;
        }

        img.Width = width;
        img.Height = height;
        img.Channels = channels;
        img.Pixels.reserve(width * height);

        for (int i = 0; i < width * height; ++i)
        {
            float r = (channels > 0) ? data[i * channels + 0] / 255.0f : 0.0f;
            float g = (channels > 1) ? data[i * channels + 1] / 255.0f : 0.0f;
            float b = (channels > 2) ? data[i * channels + 2] / 255.0f : 0.0f;
            float a = (channels > 3) ? data[i * channels + 3] / 255.0f : 1.0f;

            img.Pixels.push_back({ r, g, b, a });
        }

        stbi_image_free(data);
        return img;
    }

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
                                Float32x2_t{ 1, 0 },
                                Float32x3_t{ background.Color.x, background.Color.y, background.Color.z }
                            },
                            Vertex
                            {
                                Float32x3_t{ transform.Position.x + (transform.Size.x / 2.0f), transform.Position.y - (transform.Size.y / 2.0f), transform.Position.z },
                                Float32x2_t{ 1, 1 },
                                Float32x3_t{ background.Color.x, background.Color.y, background.Color.z }
                            },
                            Vertex
                            {
                                Float32x3_t{ transform.Position.x - (transform.Size.x / 2.0f), transform.Position.y - (transform.Size.y / 2.0f), transform.Position.z },
                                Float32x2_t{ 0, 1 },
                                Float32x3_t{ background.Color.x, background.Color.y, background.Color.z }
                            },
                            Vertex
                            {
                                Float32x3_t{ transform.Position.x - (transform.Size.x / 2.0f), transform.Position.y + (transform.Size.y / 2.0f), transform.Position.z },
                                Float32x2_t{ 0, 0 },
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