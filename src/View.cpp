#include <clocale>
#include "View.h"
#include <string>
#include <wchar.h>

View::View() {
    setlocale(LC_ALL, "");
    initscr();

    resize_term(WINDOW_HEIGHT, WINDOW_WIDTH);
    noecho();
    curs_set(0); 
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair('g', COLOR_GREEN, COLOR_BLACK);
    init_pair('r', COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_BLACK);
    
    bkgd(COLOR_PAIR(1));
}

void View::drawStartScreen(){
    mvprintw(10, 10, "게임을 시작하려면 아무키나 누르세요");
    refresh();
}

void View::drawGameOver(){
    clear();
    nodelay(stdscr, FALSE);
    mvprintw(10, 10, "Gameover...");
    getch();
}

void View::draw(Map map, Snake snake, std::vector<Item> item) {
    drawMainWindow();
    drawGameWindow(map, snake, item);
    drawSnake(snake);
    drawItem(item);
    drawScoreWindow(snake);
    drawBorder();
    update();
}

void View::drawMainWindow() {
    mvprintw(1, 3, "Preversion");
    mvprintw(2, 3, "Logo Space");
    mvprintw(3, 3, "margin");
    return;
}

void View::drawGameWindow(Map map, Snake snake, std::vector<Item> item) {
    gameWindow = newwin(25, 50, 5, 2);
    wbkgd(gameWindow, COLOR_PAIR(1));
    wattron(gameWindow, COLOR_PAIR(1));

     for(int i=0; i<map.mapHeight; i++) {
        for(int j=0; j<map.mapWidth; j++) {
            int pos = map.getMapValue(i, j);
            if(pos == 0) {
                wprintw(gameWindow, "  ");
            }
            else if(pos == 1 || pos == 2) {
                wprintw(gameWindow, " ");
                mvwprintw(gameWindow, i, 2*j, "■");
            }

        }
    }
}

void View::drawSnake(Snake snake) {
    std::vector<POSITION> snakepos = snake.getPosition();

    wattron(gameWindow, COLOR_PAIR(2));
    wchar_t head[] = L" ■";
    wchar_t body[] = L" □";

    //head
    wprintw(gameWindow, " ");
    mvwprintw(gameWindow, snakepos[0].y, 2*snakepos[0].x, "■");

    //body
    for(int i=1; i<snake.getLength(); i++) {
        POSITION pos = snakepos[i];
        wprintw(gameWindow, " ");
        mvwprintw(gameWindow, pos.y, 2*pos.x, "□");
    }
}

void View::drawItem(std::vector<Item> item) {
    for(int i=0; i<item.size(); i++) {
        POSITION itempos = item[i].getItemPos();
        if(item[i].isGrowItem()) {
            wattron(gameWindow, COLOR_PAIR('g'));
            mvwprintw(gameWindow, itempos.y, 2*itempos.x, "■");
        }else{
            wattron(gameWindow, COLOR_PAIR('r'));
            mvwprintw(gameWindow, itempos.y, 2*itempos.x, "■");
        }
    }
}

void View::drawScoreWindow(Snake snake) {
    return;
}

void View::drawBorder() {
    border(0, 0, 0, 0, 0, 0, 0, 0);
}

void View::update()  {
    refresh();
    wrefresh(gameWindow);
}
/* 테스트용 코드, mainlogic 간단한 버전이라고 보면 될 듯*/
// int main() {
//     Level lv;
//     lv.createMap();
//     Snake snake;
//     View test;
//     Map map = lv.getCurrentMap();
//     test.draw(map, snake);
//     getch();
//     delwin(test.gameWindow);
//     endwin();
// }
/* 테스트 끝 */