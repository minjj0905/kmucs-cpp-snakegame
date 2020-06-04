#include <iostream>
#include <vector>

class Map {
public:
    /*map의 y축 길이*/
    int mapHeight;

    /*map의 x축 길이*/
    int mapWidth;

    int **map;

    /*map file의 경로*/
    std::string mapPath;

    /*생성자*/
    Map(int stage);
    /*맵 불러오기*/
    void loadMap();
    /*좌표로 값 불러오기*/
    int getMapValue(int y, int x);
    /*좌표로 값 설정하기*/
    void setMapValue(int y, int x, int value);
    /*값으로 좌표 불러오기*/
    std::vector<int> getMapPos(int value);
};