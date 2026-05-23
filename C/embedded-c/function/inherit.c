#include <stdio.h>
#include <string.h>

struct shape {
    int width;
    int height;
    void (*setWidth)(struct shape *s, int w);
    void (*setHeight)(struct shape *s, int h);
};

void setWidth(struct shape *s, int w)
{
    s->width = w;
}

void setHeight(struct shape *s, int h)
{
    s->height = h;
}

struct rectangle {
    struct shape s;
    int (*getArea)(struct shape *s);
};

int getArea(struct shape *s)
{
    return (s->width * s->height);
}

int main(void)
{
    struct rectangle rect = {
        .s.setWidth = setWidth,
        .s.setHeight = setHeight,
        .getArea = getArea,
    };

    rect.s.setWidth(&rect.s, 5);
    rect.s.setHeight(&rect.s, 7);

    printf("Total Area: %d \n", rect.getArea(&rect.s));
    return 0;
}
