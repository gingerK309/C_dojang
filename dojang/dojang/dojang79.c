/*#include <stdio.h>
#pragma warning (disable:4996)
struct Point2D {
    int x, y;
};

struct Point2D movePoint(int offset)
{
   static struct Point2D p = {.x=10,.y=20};
  
   p.x += offset;
   p.y += offset;

   return p;
}

int main()
{
    int num1;
    struct Point2D p;

    scanf("%d", &num1);

    p = movePoint(num1);
    printf("%d %d\n", p.x, p.y);

    p = movePoint(num1);
    printf("%d %d\n", p.x, p.y);

    p = movePoint(num1);
    printf("%d %d\n", p.x, p.y);

    return 0;
}*/