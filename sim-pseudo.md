
# sim initiation

do we need more cars?
if yes:
    spawn them
    find empty space in all_vehicles
    assign routes to new cars

for each car:

    move car towards goal
    check for going-to-be collision

    if it is near a goal:
        goal.visits++;

        check if its final goal
        if yes:
            set car.init = 0
        else:
            set next goal to current goal