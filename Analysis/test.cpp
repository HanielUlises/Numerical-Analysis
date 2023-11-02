#include <iostream>
#include <graphics.h>
#include <conio.h>

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int data[] = {10, 30, 50, 20, 40};
    int n = sizeof(data) / sizeof(data[0]);

    int barWidth = 50;
    int maxHeight = getmaxy() - 50;

    int barSpacing = (getmaxx() - (n * barWidth)) / (n + 1);

    for (int i = 0; i < n; i++) {
        int barHeight = (data[i] * maxHeight) / 100;
        int x1 = (i + 1) * barSpacing + i * barWidth;
        int y1 = maxHeight - barHeight;
        int x2 = x1 + barWidth;
        int y2 = maxHeight;

        rectangle(x1, y1, x2, y2);
        floodfill((x1 + x2) / 2, (y1 + y2) / 2, WHITE);
    }

    getch();
    closegraph();

    return 0;
}