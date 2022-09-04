#include <stdio.h>

typedef struct
{
    int x;
    int y;
}
location;

int main(void)
{
    location node;
    node.x = 1;
    node.y = 2;

    printf("(%i, %i)\n", node.x, node.y);
    printf("(%p, %p)\n", &node.x, &node.y);
    printf("%p\n", &node);

}