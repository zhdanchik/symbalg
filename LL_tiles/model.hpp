#ifndef MODEL_HPP
#define MODEL_HPP
#include <aivlib/meshTD.hpp>
#include <aivlib/dekart.hpp>
#include <math.h>
using namespace aiv;
struct Base_cell {

};
typedef Base_cell* pcell;
struct cell1 : public Base_cell{

};
class Base_tile {
public:
 void start();

};
typedef Base_tile* ptile;
class Sec1_tale : public Base_tile{
public:
 void start();

};
#endif