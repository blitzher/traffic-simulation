import pygame as pg
import time
# pylint has problems detecting members of pygame, so disabling it
#pylint: disable=no-member
pg.init()
pg.font.init()

WHITE = (217, 217, 217)
BLACK = (55, 55, 55)

RED = (255, 0, 0)
GRN = (0, 255, 0)

VEHIC = (100, 100, 200)

VEH_RAD = ((18)**0.5)*4


def scale(v, a, b, c, d):
    inp_prog = (v - a) / (b - a)
    out_prog = inp_prog * (d - c) + c
    return out_prog

def scale_2d(v, a, b, c, d):
    return (scale(v[0],a,b,c,d), (scale(v[1],a,b,c,d)))

class Visual:
    def __init__(self, size=(800, 800), lights=True):
        if (type(size) != tuple):
            raise TypeError("size must be tuple")

        self.screen = pg.display.set_mode(size)
        self.size = size

        self.running = False

        self.going = False
        self.ui_font = pg.font.SysFont("Monaco", 32)
        self.lights = lights

        self.frames = []
        self.current_frame = 0

        # load all frames into list
        with open(".visuals", "r") as f:
            for c, line in enumerate(f.readlines()):
                coords = line.split(" ")
                frame = []

                if ((len(coords)-1) % 2 != 0):
                    print(coords)
                    raise ValueError(
                        "Non even number (%d) of coordinates in line %d" % (len(coords), c))

                for i in range(len(coords) // 2):

                    x = scale(int(coords[i*2]), 0, 100, 0, size[0])
                    y = scale(int(coords[i*2+1]), 0, 100, 0, size[1])
                    veh = (x, y)
                    frame.append(veh)

                self.frames.append(frame)

    def draw_lanes(self):
        lane_width = 100

        horiz_center = self.size[0] / 2
        verti_center = self.size[1] / 2


        n_s_lane = pg.Rect(horiz_center-lane_width, 0,
                           2*lane_width, self.size[1])
        e_w_lane = pg.Rect(0, verti_center-lane_width,
                           self.size[0], 2*lane_width)
        pg.draw.rect(self.screen, WHITE, (n_s_lane))
        pg.draw.rect(self.screen, WHITE, (e_w_lane))

    def draw_vehicles(self, frame_index):
        frame = self.frames[frame_index]

        if (self.lights):
            frame = frame[2:]

        for veh in frame:
            pg.draw.circle(self.screen, VEHIC, veh, VEH_RAD)

    def draw_lights(self, frame_index):

        north_south = self.frames[frame_index][0][0]
        ns_clr = GRN if north_south else RED
        east_west = self.frames[frame_index][1][0]
        ew_clr = GRN if east_west else RED

        pg.draw.circle(self.screen, ns_clr,
                                        (scale(35.0,0,100,0,self.size[0]),
                                         scale(32.5,0,100,0,self.size[1])), VEH_RAD )
        pg.draw.circle(self.screen, ns_clr ,
                                        (scale(65.0,0,100,0,self.size[0]),
                                         scale(67.5,0,100,0,self.size[1])), VEH_RAD )

        pg.draw.circle(self.screen, ew_clr ,
                                        (scale(67.5,0,100,0,self.size[0]),
                                         scale(35.0,0,100,0,self.size[1])), VEH_RAD )
        pg.draw.circle(self.screen, ew_clr ,
                                        (scale(32.5,0,100,0,self.size[0]),
                                         scale(65.0,0,100,0,self.size[1])), VEH_RAD )


    def main(self):

        self.running = True

        while self.running:
            self.screen.fill(BLACK)

            for event in pg.event.get():
                if (event.type == pg.KEYDOWN):
                    self.handle_button_down(event.key)
                if (event.type == pg.KEYUP):
                    self.handle_button_up(event.key)

            if (self.going):
                self.current_frame += 1
            if (self.current_frame >= len(self.frames)):
                self.going = False
                self.current_frame = len(self.frames) - 1

            self.draw_lanes()
            self.draw_vehicles(self.current_frame)
            
            if (self.lights):
                self.draw_lights(self.current_frame)

            frame_count = self.ui_font.render(
                "frame %d" % (self.current_frame+1), True, WHITE)
            self.screen.blit(frame_count, (0, 0))
            total_frames = self.ui_font.render(
                " of %d" % len(self.frames), True, WHITE)
            self.screen.blit(total_frames, (0, 40))

            time.sleep(0.07)

            pg.display.flip()

    def handle_button_down(self, key):

        if (key == pg.K_ESCAPE or key == pg.K_q):
            self.running = False

        elif (key == pg.K_SPACE):
            self.going = not self.going

        elif (key == pg.K_r):
            self.current_frame = 0
            self.going = False

        elif (key == pg.K_UP):
            self.current_frame = min(len(self.frames)-1, self.current_frame + 10)
            self.going = False

        elif (key == pg.K_DOWN and self.current_frame > 0):
            self.current_frame = max(0, self.current_frame - 10)
            self.going = False

        elif (key == pg.K_RIGHT and self.current_frame < len(self.frames)):
            self.current_frame += 1
            self.going = False
        elif (key == pg.K_LEFT and self.current_frame > 0):
            self.current_frame -= 1
            self.going = False

    def handle_button_up(self, key):
        pass


if __name__ == '__main__':
    v = Visual(lights=False)
    v.main()
