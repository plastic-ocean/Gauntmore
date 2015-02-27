//#pragma once
//#include "oxygine-framework.h"
//
//using namespace oxygine;
//using namespace std;
//
//class PathNode : public Object {
//
//public:
//    PathNode();
//    PathNode( Vector2, int, int );
//    PathNode( Vector2, int, int, PathNode );
//    ~PathNode();
//
//    const Vector2 getLocation();
//    const int getHeuristic();
//    const int getCost();
//    const int getTotal();
//    void setHeuristic(int);
//    void setCost(int);
//    void calculateTotal();
//    void setLocation(Vector2);
//    //    bool operator>(  PathNode& node );
//    PathNode getParent();
//    void setParent(PathNode);
//
//private:
//    Vector2 location;
//    int heuristic; //estimated cost from current to target
//    int cost; //current cost from start to target
//    int total; //cost + heuristic
//    PathNode *parent;//not Java, pointers are not universal
//
//};
