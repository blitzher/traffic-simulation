import pygame as pg #pylint: disable=no-member
import time

pg.init()
pg.font.init()

WHITE = (217, 217, 217)
BLACK = (55, 55, 55)
VEHIC = (100, 100, 200)

VEH_RAD = 10

def scale(v, a, b, c, d):
    inp_prog = (v - a) / (b - a)
    out_prog = inp_prog * (d - c) + c
    return out_prog
    

class Visual:

    def __init__(self, size=(400,400)):
        if (type(size) != tuple): 
            raise TypeError("size must be tuple")

        self.screen = pg.display.set_mode(size)
        self.size = size

        self.running = False

        self.going = False
        self.ui_font = pg.font.SysFont("Monaco", 32)

        self.frames = []

        # load all frames into list
        with open(".visuals", "r") as f:
            for c, line in enumerate(f.readlines()):
                coords = line.split(" ");
                frame = []
            
                if ((len(coords)-1) % 2 != 0): 
                    print(coords)
                    raise ValueError("Non even number (%d) of coordinates in line %d" % (len(coords), c))

                
                for i in range(len(coords) // 2):

                    x = scale(int(coords[i*2]), 0, 100, 0, size[0])
                    y = scale(int(coords[i*2+1]), 0, 100, 0, size[1])
                    veh = (x,y)
                    frame.append(veh)
                
                self.frames.append(frame)
        

    def draw_lanes(self):
        lane_width = 50

        horiz_center = self.size[0] / 2
        verti_center = self.size[1] / 2

        n_s_lane = pg.Rect(horiz_center-lane_width, 0, 2*lane_width, self.size[1])
        e_w_lane = pg.Rect(0, verti_center-lane_width, self.size[0], 2*lane_width)
        pg.draw.rect(self.screen, WHITE, (n_s_lane))
        pg.draw.rect(self.screen, WHITE, (e_w_lane))

    def draw_vehicles(self, frame_index):
        frame = self.frames[frame_index]
        
        for veh in frame:
            pg.draw.circle(self.screen, VEHIC, veh, VEH_RAD)

    def main(self):

        self.running = True
        i = 0

        while self.running and i < len(self.frames):
            self.screen.fill(BLACK)

            self.draw_lanes()
            self.draw_vehicles(i)
        
            frame_count = self.ui_font.render("frame %d" % (i+1), True, WHITE)
            self.screen.blit(frame_count, (0, 0))
            total_frames = self.ui_font.render(" of %d" % len(self.frames), True, WHITE)
            self.screen.blit(total_frames, (0, 40))

            for event in pg.event.get():
                if (event.type == pg.KEYDOWN):

                    self.handle_button_down(event.key)

            time.sleep(0.1)
            if (self.going):
                i += 1
            pg.display.flip()
        



    def handle_button_down(self, key):
        
        if (key == pg.K_ESCAPE or key == pg.K_q):
            self.running = False

        elif (key == pg.K_SPACE):
            self.going = not self.going

    
if __name__ == '__main__':
    v = Visual()
    v.main()
