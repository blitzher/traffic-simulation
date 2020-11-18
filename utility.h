typedef unsigned int uint;
typedef unsigned short ushort;

#define MAX_GOALS 10;

typedef struct Point
{
    uint x;
    uint y;
    uint wait_points;
    uint visits;
} Point;

typedef struct Car
{
    Point position;
    Point *goals;
    ushort goal_index;
    double speed;
    double desired_speed;
    double reaction_time;

} Car;

/* calculate the euclidean distance between two points */
double u_distance(Point, Point);

/* calculate the euclidean distance squared between two points */
double u_distance_sqr(Point, Point);

/* generate a new point with default values set */
Point u_new_point(uint, uint);
/* generate a new car with default values set */
Car u_new_car(Point, Point *);

/* helper function for printing a point */
void u_print_point(Point);
/* helper function for printing a car */
void u_print_car(Car);