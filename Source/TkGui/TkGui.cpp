#include "TkGui/TkGui.hpp"
#include "TkGui/TkGui_Font.hpp"
#include "TkGui/TkGui_Image.hpp"

namespace TkGui
{
    stbtt_bakedchar cdata[96];

    void Begin()
    {
        if (s_wasInitialized)
        {
            return;
        }

        s_wasInitialized = 1;
        s_drawData.Objects = { };
    }

    void Panel(Transform transform, BackgroundProperties background)
    {
        if (!s_wasInitialized)
        {
            return;
        }

        Object drawData;
        drawData.Faces.push_back(
            Face{ }
        );
    }

    void Text(Transform transform, TextProporties text)
    {
        float32_t x = transform.Position.x;
        float32_t y = transform.Position.y;

        letters tttt = text.Text;

        while (*tttt)
        {
            if (*tttt >= 32 && *tttt < 128)
            {
                stbtt_bakedchar* b = &cdata[*tttt - 32];

                float32_t x0 = x + b->xoff;
                float32_t y0 = y - b->yoff;
                float32_t x1 = x0 + (b->x1 - b->x0);
                float32_t y1 = y0 + (b->y1 - b->y0);

                float32_t s0 = b->x0 / 512.0f;
                float32_t t0 = b->y0 / 512.0f;
                float32_t s1 = b->x1 / 512.0f;
                float32_t t1 = b->y1 / 512.0f;

                x += b->xadvance;
            }
            ++tttt;
        }
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