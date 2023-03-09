#include <curses.h>
#include <stdlib.h>
#include <locale.h>
#include <ncurses.h>

static bool should_close = false;

void close_win() {
    should_close = true;
}

int main() {
    if (setlocale(LC_ALL, "") == NULL) {
        exit(1);
    }
    initscr();
    cbreak();
    noecho();
    start_color();

    while (!should_close) {
        clear();

        if (LINES < 10 || COLS < 60) {
            printw("Too small window");
        } else {
            printw("Can Change Color: %d\n", can_change_color());
            printw("Has colors: %d\n", has_colors());

            short pair = 2;
            init_pair(pair, COLOR_BLACK, COLOR_YELLOW);
            short fg, bg;
            pair_content(pair, &fg, &bg);
            printw("pair[id: %d]: %d %d\n", pair, fg, bg);

            short r, g, b;
            color_content(fg, &r, &g, &b);
            printw("fg: %.0lf %.0lf %.0lf\n", r * 0.255, g * 0.255, b * 0.255);
            color_content(bg, &r, &g, &b);
            printw("bg: %.0lf %.0lf %.0lf\n", r * 0.255, g * 0.255, b * 0.255);

            attrset(COLOR_PAIR(pair));
            printw("This should be printed in black with a red background!\n");
            attroff(COLOR_PAIR(2));
        }

        refresh();

        char input = getch();
        if (input == 'q')
            close_win();
    }

    endwin();
    return 0;
}
