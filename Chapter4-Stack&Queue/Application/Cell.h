//
// Created by 杜府航 on 2019/5/12.
//
//迷宫格点类
#ifndef CHAPTER4_STACK_QUEUE_CELL_H
#define CHAPTER4_STACK_QUEUE_CELL_H

typedef enum { AVAILABLE, ROUTE, BACKTRACKED, WALL } Status;    //迷宫单元状态
//原始可用的，在当前路径上的、所有方向均尝试失败后回溯过的、不可用的（墙）

typedef enum { UNKNOW, EAST, SOUTH, WEST, NORTH, NO_WAY } ESWN; //单元的相对邻接方向
//未定、东、西、南、北、无路可通

inline ESWN nextEXWN (ESWN eswn) { return ESWN (eswn + 1); }    //依次转制下一邻接方向

struct Cell //迷宫格点
{
    //x坐标， y坐标，类型
    int x, y;
    Status status;
    ESWN incoming, outgoing;    //进入、走出方向
};

#define  LABY_MAX 24   //最大迷宫尺寸
Cell laby[LABY_MAX][LABY_MAX];  //迷宫

#endif //CHAPTER4_STACK_QUEUE_CELL_H
